#include<iostream>
#include<string>

using namespace std;

class SinhVien {
private:
    string rank;
    float dtb;
public:
    float dtoan;
    float dvan;
    string name;
    SinhVien(string name, float dtoan, float dvan) {
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
    SinhVien sv1("Lam", 6.5, 6.5);
    cout << "Diem trung binh: " << sv1.tinhDTB() << endl;
    cout << "Loai: " << sv1.xepHang() << endl;
}