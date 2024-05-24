# typedef
C++中的`typedef`关键字用于为已存在的数据类型创建一个新的名字，也被称为类型别名。它并不创造新的数据类型，只是提供了一个额外的、可能更易读或更有意义的名字来引用原始类型。`typedef`的使用增强了代码的可读性和可维护性，尤其是在处理复杂类型声明时。

## 基本语法
```cpp
typedef existing_type new_type_name;
```
- existing_type 是已存在的数据类型，可以是基本类型、结构体、联合体、指针类型、引用类型等。
- new_type_name 是你为existing_type提供的新名称，即类型别名。

## 作用
1. 定义一种类型的别名
- 注意typedef并不是简单的宏替换

2. 定义struct结构体别名

3. 用typedef来定义与平台无关的类型。

4. 为复杂的声明定义一个简单的别名

## typedef和#define的区别
typedef是一种类型别名，而#define只是宏定义。二者并不总是可以互换的。
```cpp
typedef char *pStr1;
#define pStr2 char *;
pStr1 s1, s2;
pStr2 s3, s4;
```
其中s1, s2, s3是char*类型，而s4是char类型。

## 例子
1. 基本类型别名
```cpp
typedef int Integer; // 创建Integer作为int的别名
Integer num = 10; // 现在可以使用Integer代替int
```

2. 复杂类型简化
```cpp
typedef int (*FuncPtr)(int, double); // 定义一个函数指针类型
FuncPtr myFunction; // myFunction是一个指向接受int和double参数并返回int的函数的指针
```

3. 结构体和类的别名
```cpp
struct Point {
    int x, y;
};

typedef Point Coord; // Coord作为Point的别名
Coord p; // 等同于Point p;
```

## C C++的使用差异
1. C使用typedef struct 可以定义结构体别名，以后忽略struct，直接使用别名。

2. C++即使没有使用typedef，你也可以在声明结构体变量时省略struct关键字直接使用结构体名称。这一特性是从C++的早期版本就开始支持的，旨在提高代码的可读性和简化语法。

## C++11的using关键字
从C++11开始，using关键字提供了另一种创建类型别名的方法，其语法更接近于变量声明，有时被认为更直观：
```cpp
using Integer = int;
using Coord = Point;
```

## 优点
可读性：通过给复杂类型命名，使得代码更易于理解。
维护性：更改类型时，只需在一个地方修改，提高了代码的维护效率。
移植性：可以用来隐藏平台相关的类型，提升代码的跨平台能力。

## 注意事项
- typedef不改变类型的基本性质，只是提供了另一种访问方式。
- 使用typedef时，建议选择有意义的名称，以提高代码的自解释性。
- typedef定义是全局的，但可以限制在命名空间或类内以减少污染全局命名空间。

## 有趣的代码
```cpp
typedef char* pStr;
const char* p1 = "hello";
const pStr p2 = "hello";
p1++;//正常
p2++;//报错
```
- p1和p2都是常量指针，意思是指针指向的内容不能修改，而指针是可以修改的。

那为什么p1++正常，而p2++报错呢?
对于p1++，当我们对指针 `p1` 使用 `p1`++ 操作时，这意味着指针 `p1` 的值（即内存地址）将增加。由于 `p1` 是一个字符指针（char *），`p1++` 将使指针 `p1` 移动到下一个字符的地址。因为常量指针不能修改指向的对象的值，但指针本身的值是可变的。
而`p2`是我们定义的别名，而不是系统固有类型，编译器在编译时，会认为`p2`是常量，不可修改，
所以`p2++`会报错。




