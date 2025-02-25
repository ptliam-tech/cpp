#include<iostream>
#include<string>

using namespace std;

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