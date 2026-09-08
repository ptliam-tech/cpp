#include<iostream>

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

/*use ponter to check*/
// Car* createCar(int speed) {
//     if(speed < 0) {
//         return nullptr;
//     }
//     return new Car(speed);
// }
Car createCar(int speed) {
    if(speed < 0) {
        throw std::invalid_argument("Speed cannot be negative");
    }
    return Car(speed);
}


int main() {
    // Car* car1 = createCar(-10);
    // Car* car2 = createCar(100);
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