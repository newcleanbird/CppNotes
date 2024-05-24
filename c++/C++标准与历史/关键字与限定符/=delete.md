# 禁止继承或重写 = delete
从C++11开始，delete还可以用于类的定义中，以禁止特定的构造函数、析构函数、复制构造函数、赋值运算符或者普通成员函数的实例化或继承。这通常称为“删除定义”或“删除函数”。

## 功能
### 禁止特定成员函数
``= delete``可以直接用于类的成员函数声明之后，表明该函数被明确禁止定义或调用。这通常用于：
- 删除拷贝构造函数和赋值操作符：防止类的实例被复制。
- 禁用不希望使用的构造函数或其他成员函数：确保类只能通过特定方式使用或初始化。

语法示例
```cpp
class Immutable {
public:
    Immutable(const std::string& data) : mData(data) {} // 允许的构造函数
    Immutable(const Immutable&) = delete;            // 禁止拷贝构造
    Immutable& operator=(const Immutable&) = delete;  // 禁止赋值运算符

private:
    std::string mData;
};
```

### 阻止类的继承
要阻止一个类被其他类继承，可以在类声明的开始处使用= delete，但这不是直接通过= delete语法完成的，而是通过将类声明为final来实现。这是因为= delete主要用于成员函数，而阻止继承是类级别的特性。

语法示例
```cpp
class FinalClass final {
    // 类定义...
};
```

### 删除编译器自动生成的函数
C++编译器会自动为类生成一些特殊成员函数，如默认构造函数、拷贝构造函数、赋值运算符和析构函数，如果未显式定义。= delete可以用来指示编译器不要生成这些默认的函数。

例子:
```cpp
class NonDefaultConstructible {
public:
    NonDefaultConstructible(int value) : mValue(value) {} // 自定义构造函数
    NonDefaultConstructible() = delete;                  // 禁止默认构造函数

private:
    int mValue;
};
```


## 优点
- 增加安全性：通过禁止不安全或不希望的操作，减少错误和资源管理问题。
- 设计清晰：明确表达类的设计意图，增强代码的可读性和维护性。
- 编译时检查：= delete的使用会在编译时产生错误，而不是运行时，有助于早期发现问题。

## 注意事项
- 当使用= delete时，务必确保该操作确实不应在程序中发生，因为一旦定义，任何尝试使用该函数的代码都将无法编译通过。
- 对于禁止继承，使用final关键字而不是= delete。
- 即使函数被= delete，它仍然需要声明，这意味着它可以被用作模板参数或友元函数的重载解析的一部分。



