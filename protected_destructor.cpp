#include <iostream>
#include <string>

class IConnection {
public:
    virtual void send(const std::string& data) = 0;
    virtual bool isConnected() const = 0;
protected:
    virtual ~IConnection() = default;
    friend class ConnectionManager;
};

class TcpConnection : public IConnection {
public:
    TcpConnection() {
        std::cout << "TCP connection created!\n";
    }

    ~TcpConnection() override {
        std::cout << "TCP connection destroyed!\n";
    }

    void send(const std::string& data) override {
        std::cout << "Send: " << data << std::endl;
    }

    bool isConnected() const override {
        return true;
    }
};

class ConnectionManager {
public:
    IConnection* createConnection() {
        return new TcpConnection();
    }

    void destroyConnection(IConnection* connection) {
        delete connection; // Được vì là hàm bạn
    }
};

int main() {

    ConnectionManager manager;

    IConnection* connection = manager.createConnection();

    connection->send("Hello");

    //delete connection; // Error

    manager.destroyConnection(connection);

    return 0;
}