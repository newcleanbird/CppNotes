# addressof

## std::addressof简介
获取对象的实际地址，尤其是取地址符被重载时想获取真实地址使用。
std::addressof的作用是获取一个对象的实际地址，即使这个对象的&操作符已被重载。它接受一个参数，该参数为要获得地址的那个对象的引用。下面通过一个极其简单的例子了解一下std::addressof的使用方法
```cpp
#include <iostream>
#include <string>
#include <functional>

class Test
{
public:
    int* operator&()
    {
        return &b;
    }

    int* a_addr()
    {
        return &a;
    }

    int* b_addr()
    {
        return &b;
    }

private:
    int a;
    int b;
};

int main(int argc, char* argv[])
{
    Test t;
    std::cout << "&t.a:" << t.a_addr() << std::endl;
    std::cout << "&t.b:" << t.b_addr() << std::endl;
    std::cout << "&t:" << &t << std::endl;
    std::cout << "addressof(t):" << std::addressof(t) << std::endl;
}
```
上面的代码输出结果为：
```cpp
&t.a:0x7ffefcb48eb0
&t.b:0x7ffefcb48eb4
&t:0x7ffefcb48eb4
addressof(t):0x7ffefcb48eb0
```
在这里正常来说使用&t应该取到的是t.a的地址值才对，但是由于我们重载了&运算符，所以这里取到了t.b的地址值，但是如果使用了std::addressof，就可以取到正确的值了。

## std::addressof源码解析
std::addressof位于libstdc++-v3\include\bits\move.h中
```cpp
template<typename _Tp>
inline _Tp* __addressof(_Tp& __r) _GLIBCXX_NOEXCEPT
{
    return reinterpret_cast<_Tp*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
}

template<typename _Tp>
inline _Tp* addressof(_Tp& __r) noexcept
{ return std::__addressof(__r); }
```
从代码中可以看出``std::addressof``里面调用了``std::__addressof``，所以真正起作用的是``std::__addressof``。``__addressof``的处理过程可以分为以下四步：

1. 将``__r``由类型``_Tp&``强制转换为``const volatile char&``，这样做有两个作用：一是防止后面使用``&``操作符获取地址时触发原类型(即``_Tp``)的重载操作(``operator&``)，就像上面那个例子那样；二是``reinterpret_cast``操作符总是可以合法的在原类型的基础上加``const``或``volatile``, 但是如果_Tp原来就带有``const``或``volatile``的话, 通过``reinterpret_cast``去掉是不允许的, 因此需要加上``const volatile``来避免编译器报错, 也就是此时不用再管``_Tp``是否本来就带有``const``或``volatile``属性了。
2. 将前面转换得到的结果强制转换为``char&``类型，此时如果转换成其它类型有可能会触发强制地址对齐的操作，这样的话真实地址就有可能会被改变了，最终造成程序错误。需要注意的是这个转换过程使用的是const_cast，可以顺便将前面留下的const和volatile属性给去掉了。
3. 使用``&``符号将前面的结果的地址给取出来（此时已经不会触发重载了）
4. 最后一步使用``reinterpret_cast``将前面获取到的地址转换回``_Tp*``类型，并且此时也会保留``_Tp``的``const``或``volatile``属性（如果有的话）

## 总结
本文通过一个简单的例子和源码介绍了C++11新引入的模板函数std::addressof，内容虽然比较简单，但是考虑到std::addressof在标准库中使用频率是比较高的，所以我们还是应该掌握其原理和用法。
最后需要注意的一点就是``std::addressof``并不保证转换的正确性和合理性，这个是需要程序员自己把控的，虽然标准库使用``std::addressof``的频率比较高，但是我们平时在编程中还是得谨慎一点使用它。


