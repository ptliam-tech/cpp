#include <iostream>
#include <string>

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