# C++ Access Modifiers & Access Control
## Quyền mặc định  
- Struct: public by default  
- Class: private by default  

## Access vs Visibility  

- **Visibility**: Preprocessing + early compilation -> Can compilier see the name ?  
- **Access**: Compilation -> Can you see this member ?  

## Friend Mechanism

- **Important**: Freind không phải từ khóa chỉ định quyền truy cập  
- Friend là 1 cơ chế cấp phát quyền truy cập riêng biệt  

```cpp  
class Box {
private:
    int secret = 42;

    friend void printSecret(const Box& b);
    friend class BoxPrinter;
};

void printsecret(const Box& b) {
    cout << "Secret: " << b.secret << endl; // được truy cập
}

class BoxPrinter {
public:
    void printBox(Box& b) {
        cout << "Secret: " << b.secret << endl;
    } 
}
```  

## When to use friend  
- Operator overloading (`operator<<`, `operator+`)  
```cpp
class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n) , age(a) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Name: " << p.name
       << ", Age: " << p.age;

    return os;
}

int main() {
    Person p("Lam", 25);

    std::cout << p << std::endl;

    return 0;
}
```  
- 2 class có mối quan hệ chặt chẽ như iterator và container: container cung cấp data và điểm bắt đầu, kết thúc. Iterator cung cấp cách duyệt và truy cập phần tử để lấy data.  
- Hàm factory cần truy cập private constructors  
```cpp
class Car {
private:
    int speed;

    Car(int s) {
        this-> speed = s;
    }

    //friend Car* createCar(int speed);
    friend Car createCar(int speed);
public:
    void print() const {
        std::cout << "Speed: " << speed << '\n';
    }
}; 
Car createCar(int speed) {
    if(speed < 0) {
        throw std::invalid_argument("Speed cannot be negative");
    }
    return Car(speed);
}

int main() {
    try {
        Car car1 = createCar(-10);
        car1.print();
    } catch (const std::invalid_argument& e) {
        std::cout << "Car1 can't create! " << e.what() << std::endl;
    }
    try {
        Car car2 = createCar(100);
        car2.print();
    } catch (const std::invalid_argument& e) {
        std::cout << "Car2 can't create! " << e.what() << std::endl;
    }
    
    return 0;
}
```  


