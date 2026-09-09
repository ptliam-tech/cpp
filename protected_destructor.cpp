#include <iostream>
#include <memory>
#include <string>

class IConnection {
public:
    virtual void send(const std::string& data) = 0;
    virtual bool isConnected() const = 0;

protected:
    // non-virtual + protected: client không delete được qua IConnection*
    ~IConnection() = default;
};

class TcpConnection : public IConnection {
public:
    TcpConnection() {
        std::cout << "TCP connection created!\n";
    }

    // public + virtual: xóa qua TcpConnection* (hoặc lớp con của nó) là hợp lệ
    ~TcpConnection() {
        std::cout << "TCP connection destroyed!\n";
    }

    void send(const std::string& data) override {
        std::cout << "Send: " << data << std::endl;
    }

    bool isConnected() const override {
        return true;
    }
};

// ---------------------------------------------------------------------
// Factory: trả về ownership rõ ràng bằng smart pointer.
// Không cần friend, không cần hàm destroyConnection() thủ công.
// ---------------------------------------------------------------------
class ConnectionManager {
public:
    // Cách 1: trả về kiểu cụ thể -> unique_ptr<TcpConnection> hủy bằng
    // destructor public của TcpConnection.
    std::unique_ptr<TcpConnection> createTcp() {
        return std::make_unique<TcpConnection>();
    }

    // Cách 2: handle đa hình bằng shared_ptr. Compile được DÙ destructor
    // của IConnection là protected, vì shared_ptr "nhớ" deleter gắn với
    // kiểu TcpConnection ngay lúc make_shared.
    std::shared_ptr<IConnection> openConnection() {
        return std::make_shared<TcpConnection>();
    }
};

int main() {
    ConnectionManager manager;

    // --- Dùng qua interface, ownership do smart pointer giữ ---
    std::shared_ptr<IConnection> conn = manager.openConnection();
    conn->send("Hello");
    std::cout << "connected? " << std::boolalpha << conn->isConnected() << '\n';
    // Hết scope: shared_ptr gọi ~TcpConnection() (đúng kiểu) -> an toàn.

    // IConnection* raw = manager.openConnection().get();
    // delete raw;                                  // ❌ ~IConnection() protected
    // std::unique_ptr<IConnection> u =             // ❌ default_delete cần
    //     std::make_unique<TcpConnection>();       //    gọi ~IConnection()
    // IConnection local;                           // ❌ abstract + dtor protected

    return 0;
}
