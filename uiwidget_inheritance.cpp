#include <iostream>
#include <vector> 
#include <string> 

class UIWidget {
public:
    virtual void draw() const = 0; // All widgets must be drawable  
    virtual ~UIWidget() = default;
};

class Button : public UIWidget {
private:
    std::string m_lable;
public:
    Button(const std::string& lable) : m_lable(lable) {
        
    }

    void draw() const override {
        std::cout << "Drawing a Button: [" << m_lable << "]" << std::endl;
    }
};

class TextField : public UIWidget {
private:
    std::string m_text;
public:
    TextField(const std::string& text = "") : m_text(text) {}

    void draw() const override {
        std::cout << "Drawing a TextField: |" << m_text << "|" << std::endl;
    }
};

void render(const std::vector<UIWidget*>& widgets) {
    std::cout << "\n---SCREEN REFRESH ---" << std::endl;
    for(const auto* widget : widgets) {
        widget->draw();
    }
    std::cout << "---------------------" << std::endl;
}

int main() {
    Button ok_button("OK");
    TextField name_field("Enter name");

    std::vector<UIWidget*> widget_list = {&ok_button, &name_field};

    render(widget_list);

    return 0;
}