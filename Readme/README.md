# C++  
## String  
- Cộng 2 string như toán tử, ví dụ: "Lâm " + "Phạm" = "Lâm Phạm" 
- append = cộng str : str1.append(" " + str2)
- to_string("tham số"): chuyển về kiểu string 
- length() -> độ dài của chuỗi
- empty() -> trả về 0 là chuỗi có ký tự , 1 là chuỗi trống
- getline(cin, biến) -> nhập chuỗi lấy cả ký tự cuối xuống dòng
Lưu ý: cin khi nhập chuỗi không nhận ký tự cách
## Class, object
**Class** 1 kiểu dữ liệu người dùng tự định nghĩa -> là bản thiết kế của object.  
**Class** gồm có thuộc tính và phương thức. Phương thức của class có 2 kiểu khai báo: khái báo trong class và ngoài class.  
Khi định nghĩa class sẽ không cấp bộ nhớ -> khởi tạo object mới cung cấp bộ nhớ.  
Khi khai báo 1 class ta cần chú ý:  
- Khai báo private: đối với các properties khi ta muốn đảm bảo an toàn dữ liệu, không muốn ngoài class được sử dụng  
- Khai báo public: đối với các method, được gọi và sử dũng bên ngoài class  
- Khai báo protected : Đối với các thành viên mà ta muốn nó được phép truy cập thông qua các lớp con kế thừa từ lớp gốc  

Khi khai báo 1 class các thành phần của nó sẽ luôn mặc định là private (không thể truy cập từ bên ngoài class thông qua object)  
```  
#include <iostream>  //thư viên C++
using namespace std; // cú pháp cho phép những hàm tiêu chuẩn như cout, cin 
class Person{
  //giới hạn quyền truy cập bên ngoài class
  private:
    string name;
    int age;
  public:
    void setName(string _name){
        name = _name;
    }
    void setAge(int _age){
        age = _age;
    }
    string getName(){
        return name;
    }
    int getAge(){
        return age;
    }
};
int main(){
    Person person1; //tạo ra 1 object từ class 
    //truy cập gián tiếp các property trong qua method 
    person1.setName("Pham Cao duy");
    person1.setAge(17);
    //in ra thong tin
    cout << "name: " << person1.getName << endl;
    cout << "age: " << person1.getAge << endl;
    return 0;
}
```  
**Object** là 1 thực thể được khởi tạo từ 1 class -> khởi tạo giá trị cho thuộc tính và hoạt động của các phương thức.  
**Static object** tạo object trong class sử dung biến static hoặc con trỏ để khai báo.  
## Constructor & Destructor
- Constructor: Hàm khởi tạo khi khởi tạo 1 object từ class thì hàm này sẽ được gọi, hàm khởi tạo trùng tên với class và không có kiểu trả về. Có thể có nhiều constructor  
    - Default constructor: không có tham số truyền vào
    - constructor: có tham số truyền vào
- Destructor: Hàm hủy khi kết thúc chương trình thì hàm sẽ được gọi, có tên trùng với class thêm dấu ~ vào đầu và không có kiểu trả về. Chỉ có 1 descontructor  
    - Giải phóng các properties
    - Giải phóng các constructor theo cơ chế LIFO
```  
class car {
    car(){} // Hàm tạo default
    car(string type, string color){
        this.type = type;
        this.color = color;
    } // Hàm tạo 
    ~car() {} //Hàm hủy
public:
    string color;
    string type;
}
```  
```
class Person{
  private:
    string name;
    int age;
  public:
    Person(string _name , int _age){
        name = _name;
        age = _age;
    }
    ~Person(){
          cout << "constructor:  " << name << " has been released" << endl;
    }
};
int main(){
    Person person1("Pham Cao Duy ",24);
    Person person2("Dinh Anh Tuan ",29);
    Person person3("Trinh Le Hoang ",29);
}
```  
- kết quả của chương trình trên  
    ```  
    constructor: Trinh Le Hoang has been released
    constructor: Dinh Anh Tuan has been released
    constructor: Pham Cao Duy has been released
    ```  
## Inline function  
- Từ khóa inline được dùng để thông báo đển compiler biết được là nội dung bên trong hàm sẽ được thay thế trực tiếp thay vì xử lý như cách thông thường mỗi khi 1 hàm được gọi đó là địa chỉ của nó sẽ phải được lưu vào trong main stack pointer trước sau đó mói nhảy đến nội dung trong hàm để thực  

Ưu điểm và nhược điểm:  
- Thích hợp cho những hàm được gọi nhiều lần
- Tối ưu hóa những hàm có logic đơn giản (tính toán, các method getter/setter trong class)
- Không thích hợp cho những hàm xử lý phức tạp (chứa vòng lặp, điều kiện)
- Không hỗ trợ xử lý đệ quy
- Dễ dàng bảo trì mã nguồn  

So sánh với macro:  
- Kiểm tra kiểu dữ liệu: inline function kiểm tra tham số tại thời điểm biên dịch, còn macro thì không
- Inline function không gây lỗi biên dịch khó hiểu: Macro có thể gây ra lỗi khó debug
- Inline function hỗ trợ debug tốt hơn: được hiển thị trong stack trace,còn macro thì không  
```  
// Macro
#define SQUARE(x) ((x) * (x))

//inline
inline int square(int x) { return x * x; }

int main(){

    int result = SQUARE(1 + 2); // Lỗi: ((1 + 2) * (1 + 2)) = 1 + 4 + 4 = 9

    int result = square(1 + 2); // Kết quả chính xác: 9

}
```  
## Function overloading  
Đây là định nghĩa liên quan đến nạp chồng hàm, được sử dụng khi ta muốn định nghĩa nhiều hàm cùng tên có cách xử lý giống nhau nhưng khác nhau về:
- Số lương tham số
- Kiểu dữ liệu trả về
- Kiểu dữ liệu tham số  

Không thể nạp chồng khi:
- Chỉ khác nhau mỗi kiểu trả về
- Giống kiểu tham số và số lượng tham số truyền vào truyền
- Không thể nạp chồng hàm static   

Function overloading xảy ra tại thời điểm compile time 
```  
class tinh_toan{
    public:
    /*Overloading method*/
        int tong(int a, int b){ 
            return a + b;
        }
        double tong(double a, double b){
            return a + b;
        }
        int tong(double a, double b, double c, double d){
            return (int)a + b + c+ d;
        }
};
int main(){
    tinh_toan tinh;
    cout << "tong 2 so integer: << tinh.tong(12, 14) << endl;
    cout << "tong 2 so double: << tinh.tong(12.12, 14.42) << endl;
    cout << "tong 4 so double: << tinh.tong(9.23, 14.12, 17.21, 89.23) << endl; 
    return 0;
}
```  
## Operator overloading  
**Định nghĩa:** Cơ chế cho phép ta định nghĩa lại các toán tử cơ bản như +,-,*,/ thành các kiểu đặc biệt để thao tác được trên các kiểu dữ liệu không phải nguyên thủy ví dụ như struct hay class   

**Ứng dụng:** Khi ta cần trực quan và đơn giản hóa trong việc đọc hiểu code ví dụ thay vì viết v3 = v1.add(V2) ta có thể viết v3 = v1 + v2, thông quan việc định nghĩa lại toán tử + để trình biên dịch có thể hiểu được    

**Cú pháp:**  
```  
<return type> operator symbol (param){
    //logic toán 
}
```  
- operator: từ khóa để nạp chồng toán tử
- symbol: toán tử muốn nạp chồng, phải là nằm trong phạm vi các toán tử nguyên thủy như +,-*,/  

**Ví dụ:** Nạp chồng toán tử + để cộng 2 phân số  
```  
class Phanso{
    private:
        int mauso;
        int tuso;
    public:
    //khởi tạo giá trị mặc định ban đầu 
        Phanso(int mauso = 0, int tuso = 0){
            this->mauso = mauso;
            this->tuso = tuso;
        }
        Phanso operator + (Phanso other){
            Phanso ketqua;
            ketqua.mauso = this->mauso * other.tuso + this->tuso * other.mauso;
            ketqua.tuso = this->tuso * other.tuso;   
            return ketqua;
        }  
        void display(Phanso a, Phanso b, Phanso ketqua){
            cout << a.mauso << "/" << a.tuso << " + " << b.mauso << "/" << b.tuso << " = " << ketqua.mauso << "/" << ketqua.tuso << endl;
        }
};

int main(){
   Phanso ps1(12, 42);
   Phanso ps2(14, 11);
   Phanso ps3 = ps1 + ps2;
   ps3.display(ps1, ps2, ps3);
   return 0;   
}
```  
## Static & virtual 
### Static
- các method và property được sử dụng bằng cách gọi trực tiếp thông qua tên class kết hợp với toán tử phạm vi ::
- Static property chỉ được cấp phát địa chỉ để sử dụng khi ta gán giá trị bên ngoài class (lúc này ta mới sử dụng được property này)
- Chỉ có các static method mới được phép truy cập đến static property  
- Static property là thể hiện của class có thể truy cập qua "class"::"var"  

Ví dụ: Ta sẽ dùng static property để lưu giá trị đếm, và truy cập nó thông qua static method.  
```  
class Person{
  private:
    string name;
    int age;
    static int total; //chỉ có thể truy cập thông qua static method
  public:
    Person(string _name , int _age){
        name = _name;
        age = _age;
        total += 1; //đếm só lượng object mỗi lần khởi tạo 
    }
    static void print_total(){
        cout << "total of objects: << total << endl;
    }
};
int Person :: total = 0 //cấp phát địa chỉ và khởi tạo giá trị lưu ở data segment
int main(){
    Person person1("Duy Pham",30);
    Person person2("Hoang Le",38);
    Person person3("Tuan Dinh",22);
    Person :: print_total();
}
```  
    - Kết quả in ra ta được total of objects: 3  
Ứng dụng: Khi ta cần chia sẻ cấu hình cài đặt giống nhau giữa các ngoại vi trong 1 hệ thống nhúng. Ví dụ như cài đặt thông số baudrate giống nhau cho nhiều bộ UART  
```  
#include <iostream>

class UART {
private:
    static int baudRate; // Shared property for baud rate
    int instanceId;      // Each UART has a unique ID

public:
    UART(int id) : instanceId(id) {}

    // Static method to set baud rate
    static void setBaudRate(int rate) {
        baudRate = rate;
    }

    // Static method to get baud rate
    static int getBaudRate() {
        return baudRate;
    }

    // Non-static method to display UART details
    void displayDetails() {
        std::cout << "UART Instance ID: " << instanceId
                  << ", Baud Rate: " << baudRate << std::endl;
    }
};

// Define static member outside the class
int UART::baudRate = 9600; // Default baud rate

int main() {
    UART uart1(1); // UART instance 1
    UART uart2(2); // UART instance 2

    // Set shared baud rate using static method
    UART::setBaudRate(115200);

    // Each instance will use the same baud rate
    uart1.displayDetails();
    uart2.displayDetails();

    // Retrieve shared baud rate
    std::cout << "Shared Baud Rate: " << UART::getBaudRate() << std::endl;

    return 0;
}
```  
### Virtual function (Hàm ảo)
- Khi 1 hàm được định nghĩa là virtual nó có thể được ghi đè (override) trong class con, để cung cấp cách triển khai cụ thể
- Khi gọi 1 hàm ảo thông qua 1 con trỏ/tham chiếu đến các lớp con. Hàm ảo tương ứng sẽ được gọi ra dựa trên object mà nó trỏ tới, chứ không dựa vào kiểu dữ liệu mà nó được định nghĩa
- Nếu lớp con không cung cấp cách triển khai cụ thể thì nội dung trong hàm ảo được định nghĩa ở class gốc sẽ được dùng nếu ta gọi  
```  
class Instrument
{
public:
    virtual void makesound(){
        cout << "make sound " << endl;
    }
};
class Piano : public Instrument
{
    void makesound()
    {
        cout << "playing the piano" << endl;
    }
};
class guitar : public Instrument
{
    void makesound()
    {
        cout << "playing the guitar" << endl;
    }
};
class Ukelele : public Instrument
{
    void makesound()
    {
        cout << "playing the Ukelele" << endl;
    }
};
int main(){
    Instrument* p[3];
    //trỏ đến các lớp con
    p[0] = new Piano(); 
    p[1] = new Guitar(); 
    p[2] = new Ukelele(); 
    for(int i = 0 ; i < 3 ;i++){
        p[i]->makesound(); //in ra hàm ảo tương ứng với từng lớp con
    }
}
```  
### Pure virtual function (Hàm ảo thuần túy)  
- Lúc này hàm ảo mà ta định nghĩa sẽ được gán giá trị bằng 0, và bắt buộc lớp con kế thừa phải cung cấp cách triển khai cụ thể
- Khi 1 class chứa ít nhất 1 pure virtual function nó sẽ trở thành abstract class, nghĩa là ta sẽ không thể tạo ra 1 object từ class này  
```  
class Instrument
{
public:
    virtual void makesound() = 0; 
};
int main(){
    Instrument myInstrument; //wrong 
    return 0;
}
```    
## Các tính chất trong OOP
### Encapulation (Đóng gói)
- Đây là khả năng đóng gói những dữ liệu quan trọng ảnh hưởng bao gồm cả thuộc tính và phương thức trong 1 class
- Được thiết lập thông qua public, private, protected
- Cung cấp các API trung gian để thao tác như getter, setter  

Lợi ích: Giúp ngăn chăn truy cập trực tiếp từ bên ngoài vào những dữ liệu quan trọng giảm nguy cơ lỗi và bảo mật  
Ví dụ:   
```  
class SinhVien {
private:
    string rank;
    float dtb;
public:
    float dtoan;
    float dvan;
    string name;
    SinhVien(string name, float dtoan, dvan) {
        this->name = name;
        this->dtoan = dtoan;
        this->dvan = dvan;
    }
    ~SinhVien() {
    }
    float tinhDTB() {
        dtb = (dtoan + dvan)/2;
        return dtb;
    }
    string xepHang() {
        if(dtb >= 8) {
            rank = "Gioi";
        } else if(dtb >= 6.5) {
            rank = "Kha";
        } else if(dtb >= 5) {
            rank = "Trung binh";
        } else {
            rank = "Yeu";
        }
        return rank;
    }
};

int main() {
    SinhVien sv1("Lam", 6, 6);
    cout << "Diem trung binh: " << sv1.tinhDTB() << endl;
    cout << "Loai: " << sv1.xepHang() << endl;
}
```  
### Inheritance (Kế thừa)
- Đây là khả năng tái sử dụng lại các phương thức và thuộc tính từ class gốc từ các class con kế thừa từ nó, giúp ta tối ưu và rút gọn chương trình  

Lợi ích: Cho phép tái sự dụng mã nguồn, giúp giảm thời gian và công sức viết lại code, dễ dàng mở rộng các tính năng mới bằng cách kế thừa, cung cấp 1 tính nhất quán khi các lớp con phải tuân thủ theo cấu trúc và hành vi của lớp gốc  

Ví dụ:  
```  
class person {
protected:
    int tuoi;
    string name;
public:
    person(string name, int tuoi) {
        this->name = name;
        this->tuoi = tuoi;
    }
    ~person() {}
    void printInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << tuoi << endl;
    }
};
    
class hocsinh : public person {
private:
    string lop;
public:
    hocsinh(string name, int tuoi, string lop) : person(name, tuoi) {
        this->lop = lop;
    }
    void printInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << tuoi << endl;
        cout << "Class: " << lop << endl;
    }
};
    
int main() {
    hocsinh hs("Lam", 10, "10A2");
    hs.printInfo();
}
```  

