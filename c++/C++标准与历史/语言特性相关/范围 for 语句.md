# 范围 for 语句
```cpp
for (declaration : range) {
    // 循环体
}
```
参数的含义：
- declaration: 定义一个变量，该变量在每次循环迭代中都会被赋予范围中的下一个元素的值。类型通常由编译器根据range推导得出。
- range: 任何支持迭代（begin和end函数）的对象，如标准库容器（vector、list、map等）、数组、字符串或者任何实现了迭代器接口的自定义类型。

## 示例
1. 遍历标准库容器
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    for (auto num : numbers) {
        std::cout << num << ' ';
    }
    // 输出: 1 2 3 4 5
}
```

2. 遍历数组
```cpp
#include <iostream>

int main() {
    int arr[] = {10, 20, 30, 40, 50};

    for (int val : arr) {
        std::cout << val << ' ';
    }
    // 输出: 10 20 30 40 50
}
```

3. 遍历字符串
```cpp
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello";

    for (char ch : str) {
        std::cout << ch << ' ';
    }
    // 输出: H e l l o
}
```

4. 遍历map
```cpp
#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> mapExample = {{"apple", 1}, {"banana", 2}, {"cherry", 3}};

    for (const auto& pair : mapExample) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
    // 输出:
    // apple: 1
    // banana: 2
    // cherry: 3
}
```

范围for语句不仅简化了代码，减少了潜在的错误（如迭代器的误用），还提高了代码的可读性和维护性。

