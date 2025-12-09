# Data type 
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
- Struct padding: compiler cấp phát bộ nhớ tự động padding nếu bộ nhớ lẻ  
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

