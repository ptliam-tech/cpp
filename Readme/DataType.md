# General
## Segment
- Text segment: Chứa các chỉ lệnh ngôn ngữ máy (machine-language) -> Read-only  
- Initialized data segment: Chứa các biến global và static đã khởi tạo tường minh (flash)-> Read, write  
- Uninitialized data segment: Chứa các biến global và static không được khởi tạo tường minh hoặc khởi tạo với giá trị bằng 0 (bss -> ram) -> Read, write  
- Stack&Heap segment : Chia sẻ cùng phân vùng nhớ -> Read, write  
    - Stack: biến cục bộ  
    - Heap: Cấp phát động  

- Để check có thể build với -Wl,--Map=main.map  
- Tránh stack overflow trong chip embedded  -> việc khai báo biến trong hàm cần đảm bảo bộ nhớ của ram, đệ quy

## Struct  
- Struct padding: compiler cấp phát bộ nhớ tự động padding 
```  
typedef struct {
    int a;
    float b;
    char c;
} test_t // bộ nhớ là 12 byte 
```  
- Tránh padding bằng chỉ thị cho compiler không padding  
```  
#pragma pack(1)
typedef struct {
    int a;
    float b;
    char c;
} test_t // bộ nhớ là 12 byte  
#pragma pack() // bộ nhớ là 9 byte
```  
## Variables
- Cấp phát biến cần để ý độ lớn của biến tránh trường hợp sử dụng biến không đúng  
```  
Ví dụ:  
unsigned int y = 0;
for(y = 0; y < 300; y++) {
    printf(...) 
} // loop trong vòng lặp vì y không thể lớn hơn 300  
```  
## Static 
- Tăng vòng đời của biến
- Biến cục bộ: Chỉ cần cấp phát 1 lần tồn tại mãi khi chương trình kết thúc -> lưu trong bss không phải trong stack nữa
- Giới hạn phạm vi hoạt động của biến và hàm ... chỉ trong file khai báo  
## Extern  
- Cho phép 1 file khác sử dụng hàm hoặc biến global đã được khai báo không phải là static trong 1 file khác  
## Volatile  
- Tránh tối ưu của compiler: khi sử dụng 1 biến ở 2 luồng khác nhau thì compiler có thể bỏ qua sự thay đổi của biến đó  
## Register  
- Lưu biến trên thanh ghi tăng tốc độ truy cập  
- Khi khai báo 1 biến thì không lưu trong ram nữa  
- Không áp dụng cho global  

