# lambda 表达式
lambda 表达式，又被称为 lambda 函数或者 lambda 匿名函数。

## lambda匿名函数的定义:
```cpp
[capture list] (parameter list) -> return type
{
   function body;
};
```
其中：
- capture-list（捕获列表）: 定义了lambda函数体中可以访问的外部变量的方式。可以是按值捕获（=, 默认）、按引用捕获（&）、或明确指定哪些变量按值或按引用捕获（[x, &y]）。
- parameters（参数列表）: 和普通函数一样，定义了lambda接收的参数。
- return-type（返回类型）: 可选，自C++14起可以直接省略，编译器会根据函数体自动推导返回类型。如果显式指定，需使用->后跟类型。
- function-body（函数体）: 包含了lambda表达式执行的具体代码。

## 示例
1. 简单Lambda（无参数，无返回值）
```cpp
[]{ std::cout << "Hello, World!\n"; }()
```

2. 带参数Lambda（有一个整型参数，无返回值）
```cpp
[](int x){ std::cout << "The value is: " << x << '\n'; }(42);
```

3. 有返回类型Lambda
```cpp
auto add = [](int a, int b) -> int { return a + b; };
std::cout << add(2, 3) << '\n';  // 输出5
```

4. 捕获外部变量（按值捕获x，按引用捕获y）
```cpp
int x = 10, y = 20;
auto lambda = [=, &y]{ return x + y++; };
std::cout << lambda() << '\n';  // 输出30
std::cout << lambda() << '\n';  // 输出31，因为y是按引用捕获的
```

## sort使用lambda自定义排序

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int arr[4] = {4, 2, 3, 1};
    //对 a 数组中的元素进行升序排序
    sort(arr, arr+4, [=](int x, int y) -> bool{ return x < y; } );
    for(int n : arr){
        cout << n << " ";
    }
    return 0;
}
```




