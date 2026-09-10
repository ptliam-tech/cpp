# Inheritance  

```cpp  
class Animal {
public:
    std::string name;
    int age;
    
    void eat() {
        std::cout << name << " is eating ..." << std::endl;
    }

    void sleep() {
        std::cout << name << " is sleeping ..." << std::endl;S
    }
};

class Dog : public Animal {
pubic:
    void bark() {
        std::cout << name << " says: Woof! Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void meow() {
        std::cout << name << " says: Meow! Meow!" << std::endl;
    }
};
```  

**Real world**  

```cpp  
class Employee {
protected:
    string name;
    int empId;
    double baseSalary;

public:
    Employee(string n, int id, double salary) : name(n), empId(id), baseSalary(salary) {

    }

    void display() {
        cout << "Name: " << name << ", ID: " << empId;
        cout << ", Salary: ₹" << baseSalary << endl;
    }

    double getSalary() {
        return baseSalary;
    }
};

class Manager : public Employee {
private:
    double bonus;
    int teamSize;

public:
    Manager(string n, int id, double salary, double b, int team)
        : Employee(n, id, salary), bonus(b), teamSize(team) {

    }

    void displayManager() {
        display();
        cout << "Bonus: ₹" << bonus << ", Team size: " << teamSize << endl;
    }

    double getTotalSalary() {
        return getSalary() + bonus; // Using inherited method
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;

public:
    Developer(string n, int id, double salary, string lang, int project) 
        : Employee(n, id, salary), programmingLanguage(lang), projectsCompleted(project) {

    }

    void displayDeveloper() {
        display();
        cout << "Language: " << programmingLanguage;
        cout << ", Projects: " << projectscompleted << endl;
    }

    void code() {
        cout << name << " is coding in " << programmingLanguage << endl;
    }
};
```  

## Type of inheritance

**Single inheritance**  
```cpp  
class Animal {
protected:
    string name;
public:
    explicit Animal(string n) : name(n) {
        cout << "Animal constructor!" << endl;
    }

    void eat() {
        cout << name << " is eating " << endl;
    }
};

class Dog : public Animal {
private:
    string breed;
public:
    Dog(string n, string b) : Animal(n), breed(b) {
        cout << "Dog constructor: " << breed << endl;
    }

    void bark() {
        cout << name << " (" << breed << ") says: Woof!" << endl;
    }
};
```  

**Multiple inheritance**  
```cpp  
class Flyer {
public: 
    void fly() {
        cout << "I can fly!" << endl;
    }
};

class Swimmer {
public:
    void swim() {
        cout << "I can swim!" << endl;
    }
};

class Duck : public Flyer, public Swimmer {
public:
    void quack() {
        cout << "Quack! Quack!" << endl;
    }
};
```  
**Multilevel inheritance**  
Grandparent -> Parent -> Child  

**Hierarchical inheritance**   
One base class → Multiple derived classes  

**Hybrid inheritance**  
```cpp  
class Device {
protected:
    string brand;

public:
    Device(string b) : brand(b) {
        cout << "Device: " << brand << endl;
    }

    void powerOn() {
        cout << brand << " device powered on" << endl;
    }
};

class Phone : public Device {
protected:
    string phoneNumber;

public:
    Phone(string b, string num) : Device(b), phoneNumber(num) {
        cout << "Phone: " << phoneNumber << endl; 
    }

    void call() {
        cout << "Calling from " << phoneNumber << endl;
    }
};

class Camera {
protected:
    int megapixels;

public:
    Camera(int mp) : megapixels(mp) {
        cout << "Camera: " << mp << "MP" << endl;
    }

    void takePhoto() {
        cout << "Taking photo with " << megapixels << "MP camera" << endl;
    }
};

class Smartphone : public Phone, public Camera {
private:
    string model;

public:
    Smartphone(string b, string num, int mp, string m)
        : Phone(b, num), Camera(mp), model(m) {
        
        cout << "Smartphone: " << model << endl;
    }

    void showFeatures() {
        cout << "\n" << model << " Features:" << endl;
        powerOn();      // From device (through Phone)
        call();         // From Phone  
        takePhoto();    // From Camera  
    }
};
```  
### Problem of multiple inheritance  

```cpp  
class GrandParent {
protected:
    int value;

public:
    GrandParent() : value(100) {
        cout << "GrantParent constructor, value = " << value << endl;
    }

    void display() {
        cout << "GrandParent value: " << value << endl;
    }
};

class Parent1 : public GrandParent {
public:
    Parent1() {
        cout << "Parent1 constructor" << endl;
    }
};

class Parent2: public GrandParent {
public:
    Parent2() {
        cout << "Parent2 constructor" << endl;
    }
};

class Child : public Parent1, public Parent2 {
public:
    Child() {
        cout << "Child constructor" << endl;
    }

    void showProblem() {
        // value = 200; // Mơ hồ không xác định! Giá trị value nào của GrandParent ? Parent1 hay Parent2 ?
        // display();   // ERROR: AMBIGUOUS!

        // Must specify which path (chỉ rõ path nào)
        Parent1::value = 200;
        Parent2::value = 300;

        Parent1::display();
        Parent2::display();
    }
}
```  
### Solution virtual inheritance  

```cpp  
class GrandParentV {
protected:
    int value;
    
public:
    GrandParentV() : value(100) {
        cout << "GrandParentV constructor, value = " << value << endl;
    }
    
    void display() {
        cout << "GrandParentV value: " << value << endl;
    }
};

class Parent1V : virtual public GrandParentV {  // virtual inheritance
public:
    Parent1V() {
        cout << "Parent1V constructor" << endl;
    }
};

class Parent2V : virtual public GrandParentV {  // virtual inheritance
public:
    Parent2V() {
        cout << "Parent2V constructor" << endl;
    }
};

class ChildV : public Parent1V, public Parent2V {
public:
    ChildV() {
        cout << "ChildV constructor" << endl;
    }
    
    void showSolution() {
        // NO AMBIGUITY! Only ONE GrandParentV exists
        value = 500;  // ✅ OK!
        display();    // ✅ OK!
        
        cout << "Virtual inheritance - only one GrandParentV!" << endl;
    }
};
```  

## Access control  

- public inheritance (IS - A)  
- protected inheritance (rare)  
- private inheritance (HAS - A alternative)  
- Private members: NEVER accessible in derived class  
- Public inheritance: Public→Public, Protected→Protected  
- Protected inheritance: Public→Protected, Protected→Protected  
- Private inheritance: Public→Private, Protected→Private  

**When to use each type**  
- Public inheritance (99% of cases)  
    - Use when: IS - A Relationship  
    - Example: Đog IS - A Animal, Car IS - A Vehicle  
    - Result: Derived class can be used as Base class  
- Protected inheritance (Rare < 1%)  
    - Use when: want to hide implementation from outside but allow further derivation  
    - Example: Internal framwork classes  
    - Result: Base interface hidden from users  
- Private inheritance (Alternative to composition)  
    - Use when: HAS - A relationship with need for base access  
    - Example: Stack HAS - A Vector (implementation detail)  
    - Result: Complete hiding of base class interface  
    - Better Alternative: Use composittion (member object)  

## Constructor & Destructor order  

- Constructor:   
    - Base -> Derived  
    - Multiple inheritance: Left -> Right base class -> derived class  
    - The member declared first is initialized first  
- Destructor: REVERRSE of constructor  
- Golden rule: if a class is meant to be inherited, ALWAYS make destructor virtual  
```cpp  
class Shape_NoVirtual {
public:
    Shape_NoVirtual() {
        cout << "Shape Constructor" << endl;
    }

    ~Shape_NoVirtual() {
        cout << "Shape Destructor" << endl;
    }
};

class Circle_NoVirtual : public Shape_NoVirtual {
private: 
    int* data;
public:
    Circle_NoVirtual() {
        data = new int[100];
        cout << "Circle Constructor (allocated memory)" << endl;
    }

    ~Circle_NoVirtual() {
        delete[] data;
        cout << "Circle Destructor (freed memory)" << endl;
    }
};

class Shape_WithVirtual {
public:
    Shape_WithVirtual() {
        cout << "Shape Constructor" << endl;
    }

    virtual ~Shape_WithVirtual() {
        cout << "Shape Destructor" << endl;
    }
};

class Circle_WithVirtual : public Shape_WithVirtual {
private:
    int* data;
public:
    Circle_WithVirtual() {
        data = new int[100];
        cout << "Circle constructor (allocated memory)" << endl;
    }

    ~Circle_WithVirtual() {
        delete[] data;
        cout << "Circle destructor (freed memory)" << endl;
    }
};

int main() {
    Shape_NoVirtual* shape = new Circle_NoVirtual();
    delete shape; // MEMORY LEAK: Only shape destructor called!

    Shape_WithVirtual* shape = new Circle_WithVirtual();
    delete shape; // Both destructors called! No leak! 
}
```  
