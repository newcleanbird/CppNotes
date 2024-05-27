/*
实现一个标准的类
*/

#include <iostream>
#include <string>
#include <utility> // 用于std::move和std::swap

class ExampleClass {
public:
    // 默认构造函数
    ExampleClass() : data_(0), name_("Default") {
        std::cout << "Default constructor called." << std::endl;
    }

    // 构造函数
    explicit ExampleClass(int data, const std::string& name = "") 
        : data_(data), name_(name) {
        std::cout << "Constructor with parameters called." << std::endl;
    }

    // 析构函数
    ~ExampleClass() {
        std::cout << "Destructor called." << std::endl;
    }

    // 拷贝构造函数
    ExampleClass(const ExampleClass& other) 
        : data_(other.data_), name_(other.name_) {
        std::cout << "Copy constructor called." << std::endl;
    }

    // 拷贝赋值运算符
    ExampleClass& operator=(const ExampleClass& other) {
        if (this != &other) {
            data_ = other.data_;
            name_ = other.name_;
        }
        std::cout << "Copy assignment operator called." << std::endl;
        return *this;
    }

    // 移动构造函数
    ExampleClass(ExampleClass&& other) noexcept
        : data_(other.data_), name_(std::move(other.name_)) {
        other.data_ = 0;
        other.name_.clear();
        std::cout << "Move constructor called." << std::endl;
    }

    // 移动赋值运算符
    ExampleClass& operator=(ExampleClass&& other) noexcept {
        if (this != &other) {
            data_ = other.data_;
            name_ = std::move(other.name_);
            other.data_ = 0;
            other.name_.clear();
        }
        std::cout << "Move assignment operator called." << std::endl;
        return *this;
    }

    // 地址操作符
    ExampleClass* operator&() {
        return this;
    }

    // 常量取地址操作符
    const ExampleClass* operator&() const {
        return this;
    }

private:
    int data_;
    std::string name_;
};

int main() {
    ExampleClass obj1(42, "Object1");
    ExampleClass obj2(obj1); // 拷贝构造
    ExampleClass obj3(100);
    obj3 = obj1; // 拷贝赋值

    ExampleClass obj4(std::move(obj3)); // 移动构造
    obj4 = std::move(obj2); // 移动赋值

    // 显示使用地址操作符
    std::cout << "Address of obj4: " << &obj4 << std::endl;
    std::cout << "Const address of obj4: " << (&obj4) << std::endl;

    return 0;
}