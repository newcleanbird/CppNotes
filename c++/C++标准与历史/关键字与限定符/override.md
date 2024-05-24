# override
在C++中，override关键字是一个继承控制修饰符，它用于显式地指示一个成员函数旨在覆盖（或重写）基类中的虚函数。override的引入增强了代码的清晰度和类型安全，帮助开发者避免因函数签名不匹配导致的无意覆盖错误。

## 目的
- 明确意图：通过在派生类的成员函数声明后加上override，编译器能够验证该函数是否确实覆盖了基类中的虚函数。这使得代码意图更加清晰，易于理解和维护。

- 编译时检查：如果函数签名与基类中的虚函数不完全匹配（包括函数名称、参数类型、数量和顺序，以及const/volatile限定符），编译器将生成错误，防止意外的函数定义。

## 使用场景
虚函数覆盖：当派生类想要提供基类虚函数的不同实现时，可以在派生类的函数声明后添加override关键字。

## 语法
```cpp
class Base {
public:
    virtual void someFunction() const;
};

class Derived : public Base {
public:
    void someFunction() const override; // 明确表示此函数覆盖了Base类中的someFunction()
};
```

## 注意事项
- 必须匹配：使用override的函数必须精确匹配基类中的虚函数签名，除了函数返回类型可以不同（C++14开始允许协变返回类型）。

- 非虚函数：override不能用于非虚函数，因为非虚函数不能被覆盖。

- 默认情况下非final：即使基类中的函数标记为final，在派生类中错误地使用override也不会被编译器捕获，因为final阻止了覆盖，编译器根本不会检查override标签。

- C++11引入：override关键字是在C++11标准中引入的，因此确保你的编译器支持C++11或更高版本。

## 示例
```cpp
#include <iostream>

class Animal {
public:
    virtual void speak() const {
        std::cout << "Some generic animal sound." << std::endl;
    }
};

class Dog : public Animal {
public:
    void speak() const override { // 正确覆盖Animal的speak函数
        std::cout << "Woof!" << std::endl;
    }
};

int main() {
    Dog dog;
    dog.speak(); // 输出 "Woof!"
    return 0;
}
```




