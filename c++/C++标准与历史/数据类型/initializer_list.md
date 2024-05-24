# initializer_list
initializer_list是一个标准库类型，是一个代表数组的轻量级包装器，用于存储同一类型的常量对象的列表。主要用于方便地初始化聚合类型（如数组、向量）和在构造函数中接受不定数量的同类型参数。支持作为函数参数或类成员初始化列表使用，用于传递一个初始化元素列表。

## 定义与包含头文件

initializer_list 是一个模板类，定义在<initializer_list>头文件中。其声明如下：
```cpp
template <typename E>
class initializer_list {
public:
    const E* begin() const noexcept;
    const E* end() const noexcept;
    size_t size() const noexcept;

private:
    const E* _M_array;
    size_t _M_len;
};
```
这里，E 是元素的类型。initializer_list 实例包含两个私有成员：一个指向元素数组的指针 _M_array 和一个表示元素数量的大小 _M_len。提供了三个公有成员函数：begin() 返回指向第一个元素的指针，end() 返回指向最后一个元素之后位置的指针，size() 返回元素的数量。

## 特点
- 不可变性：initializer_list中的元素是常量，一旦创建就不能修改。
- 轻量级：它并不是一个完整的容器，而是一个简单的双向指针（指向元素的开始和结束）加上元素数量，没有分配额外的内存来存储元素。
- 临时性：它通常用于临时目的，比如构造函数的参数传递，一旦构造函数完成，initializer_list 对象通常就会被销毁。
- 隐式构造：当使用花括号 {} 初始化一个能够接受initializer_list 的对象时，编译器会自动创建一个initializer_list 对象。
- 兼容性：它可以和容器的构造函数以及接受范围的算法很好地协同工作，提高了代码的简洁性和可读性。

## 用法：

1. std::initializer_list 类型对象是一个访问 const T 类型对象数组的轻量代理对象。
2. std::initializer_list 对象在这些时候自动构造：
   - 用花括号初始化器列表列表初始化一个对象，其中对应构造函数接受一个std::initializer_list 参数
   - 以花括号初始化器列表为赋值的右运算数，或函数调用参数，而对应的赋值运算符/函数接受 std::initializer_list 参数
   - 绑定花括号初始化器列表到 auto ，包括在范围 for 循环中
3. initializer_list 可由一对指针或指针与其长度实现。复制一个 std::initializer_list 不会复制其底层对象。
4. 底层数组不保证在原始 initializer_list 对象的生存期结束后继续存在。 std::initializer_list 的存储是未指定的（即它可以是自动、临时或静态只读内存，依赖场合）。 (C++14 前)
5. 底层数组是 const T[N] 类型的临时数组，其中每个元素都从原始初始化器列表的对应元素复制初始化（除非窄化转换非法）。底层数组的生存期与任何其他临时对象相同，除了从数组初始化 initializer_list 对象会延长数组的生存期，恰如绑定引用到临时量（有例外，例如对于初始化非静态类成员）。底层数组可以分配在只读内存。 (C++14 起)
6. 若声明了 std::initializer_list 的显式或偏特化则程序为病式。

### 成员类型：

| 成员类型        | 定义       |
| --------------- | ---------- |
| value_type      | T          |
| reference       | const T&   |
| const_reference | const T&   |
| size_type       | std_size_t |
| iterator        | const T*   |
| const_iterator  | const T*   |

### 成员函数

- 构造函数
  - initializer_list() noexcept;
  - constexpr initializer_list() noexcept;

```cpp
#include <iostream>
#include <initializer_list>
int main(){
    std::initializer_list<int> empty_list;
    std::cout << "empty_list.size(): " << empty_list.size() << '\n';

    // 用列表初始化创建初始化器列表
    std::initializer_list<int> digits {1, 2, 3, 4, 5};
    std::cout << "digits.size(): " << digits.size() << '\n';

    // auto 的特殊规则表示‘ fraction ’拥有类型
    // type std::initializer_list<double>
    auto fractions = {3.14159, 2.71828};
    std::cout << "fractions.size(): " << fractions.size() << '\n';
}
```

- size ：返回initializer_list中元素数目
- begin：返回指向首元素的指针
- end：返回指向末尾元素后一位置的指针

### 非成员函数

| 成员类型                                  | 定义                      |
| ----------------------------------------- | ------------------------- |
| std::begin(std::initializer_list) (C++11) | 特化 std::begin           |
| std::end(std::initializer_list)(C++11)    | 定义于头文件	特化std::end |
| rbegin(std::initializer_list) (C++14)     | 特化std::rbegin           |
| rend(std::initializer_list)(C++14)        | 特化std::rend             |

```cpp
#include <iostream>
#include <vector>
#include <initializer_list>

template <class T>
struct S {
    std::vector<T> v;
    S(std::initializer_list<T> l) : v(l) {
         std::cout << "constructed with a " << l.size() << "-element list\n";
    }
    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }
    std::pair<const T*, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // 在 return 语句中复制列表初始化
                                   // 这不使用 std::initializer_list
    }
};

template <typename T>
void templated_fn(T) {}

int main(){
    S<int> s = {1, 2, 3, 4, 5}; // 复制初始化
    s.append({6, 7, 8});      // 函数调用中的列表初始化

    std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";

    for (auto n : s.v)
        std::cout << n << ' ';
    std::cout << '\n';
    std::cout << "Range-for over brace-init-list: \n";

    for (int x : {-1, -2, -3}) // auto 的规则令此带范围 for 工作
        std::cout << x << ' ';
    std::cout << '\n';

    auto al = {10, 11, 12};   // auto 的特殊规则

    std::cout << "The list bound to auto has size() = " << al.size() << '\n';

//    templated_fn({1, 2, 3}); // 编译错误！“ {1, 2, 3} ”不是表达式，
                             // 它无类型，故 T 无法推导
    templated_fn<std::initializer_list<int>>({1, 2, 3}); // OK
    templated_fn<std::vector<int>>({1, 2, 3});           // 也 OK
}
```

## 使用场景
1. 构造函数参数：当定义类时，可以通过接受initializer_list 参数来允许列表初始化。
```cpp
class MyClass {
public:
    MyClass(std::initializer_list<int> list) : data(list) {}
private:
    std::vector<int> data;
};

MyClass obj {1, 2, 3, 4}; // 使用initializer_list进行初始化
```

2. 函数参数：可以接受不定数量的同类型参数，使函数调用更加灵活。
```cpp
void printIntegers(std::initializer_list<int> list) {
    for (int i : list) {
        std::cout << i << " ";
    }
}

printIntegers({1, 2, 3}); // 输出: 1 2 3
```

3. 配合其他容器：可以直接用于初始化标准库中的容器，如std::vector、std::array等。
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
```

## 示例
1. 初始化容器
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5}; // 使用initializer_list初始化vector
```

2. 函数参数
```cpp
void printElements(std::initializer_list<int> elems) {
    for (auto elem : elems) {
        std::cout << elem << " ";
    }
}

printElements({10, 20, 30}); // 调用函数时使用initializer_list
```

## 优缺点
- 优点：
  - 简洁性：提供了一种简洁的语法来初始化数据结构，提高了代码的清晰度和可读性。
简化了构造函数和函数的参数传递过程。
  - 灵活性：可以在编译时确定元素数量，适用于多种数据类型的初始化。支持泛型编程，增加了代码的灵活性。

- 缺点：
  - 不可变性：由于元素是常量，初始化后无法修改，这限制了它的应用场景。
  - 性能考量：对于大型数据集，复制整个列表可能会成为性能瓶颈，尤其是在频繁调用接受initializer_list的函数时。

## 注意事项
- 当initializer_list作为函数参数时，它会被拷贝给函数，即使在函数内部不修改列表，拷贝也可能涉及大量数据。
- 对于大型数据初始化，考虑直接使用迭代器或区间等其他方式，以避免不必要的拷贝。