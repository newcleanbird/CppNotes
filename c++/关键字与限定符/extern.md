# extern
是C/C++语言中表明函数和全局变量作用范围（可见性）的关键字，该关键字告诉编译器，其声明的函数和变量可以在本模块或其它模块中使用。

## 全局变量(外部变量)：
1. 定义
我们知道，程序的编译单位是源程序文件，一个源文件可以包含一个或若干个函数。在函数内定义的变量是局部变量，而在函数之外定义的变量则称为外部变量，外部变量也就是我们所讲的全局变量。

2. 作用域(全局作用域)
全局变量可以为本文件中的其他函数所共用，它的==有效范围为从“定义变量的位置开始”到“本源文件结束”==。

3. 生命周期
全局变量的生命周期从程序启动时开始，直到程序结束。这意味着全局变量在程序的整个执行过程中一直占用内存，且初始化通常在main函数执行之前完成。

4. 链接属性
   - 内部链接（静态存储期）：默认情况下，如果全局变量只在一个源文件中定义，它具有内部链接，这意味着它只对那个文件可见。即便在其他文件中使用extern声明，也无法访问它。
   - 外部链接：要使全局变量在多个文件之间共享，需要在其中一个文件中定义，并在其他文件中使用extern声明。这样定义的全局变量具有外部链接，可以在程序的任何部分被访问。

5. 优点
   - 数据共享：全局变量允许不同函数和文件之间共享数据，简化了跨函数或模块的数据传递。
   - 简单直接：对于简单的程序或快速原型开发，全局变量提供了一种直接的数据访问方式，减少了参数传递的复杂性。

## 使用extern的目的
- 跨文件共享：extern 关键字的主要目的是让一个文件能够访问在另一个文件中定义的全局变量或函数。这对于分割代码到不同的文件中，同时又需要在这些文件间共享数据或函数调用至关重要。

- 声明而非定义：在编程中，定义一个变量或函数意味着为其分配存储空间或生成代码，而声明则告知编译器该变量或函数的类型、返回类型、参数列表等信息，但不分配存储空间或生成代码。extern 用于变量或函数的声明，表明其定义在别处。

## 用法
### 变量
1. 声明：在需要访问一个外部定义的全局变量的文件中，使用 extern 进行声明。
```cpp
extern int globalVar; // 告诉编译器globalVar在其他地方定义
```
注意，对于全局变量的 extern 声明，不包含初始化器。初始化应在定义时进行。

2. 定义：全局变量的实际定义（包含初始化）通常在某个 .cpp 文件中完成。
```cpp
int globalVar = 42; // 实际定义和初始化
```

### 函数
1. 函数声明：同样，如果一个函数在另一个文件中定义，可以在需要调用该函数的文件中使用 extern 声明该函数，尽管在实践中通常省略 extern，因为函数声明默认就是外部链接的。
```cpp
extern int add(int a, int b); // 或者直接写成 int add(int a, int b);
```

2. 函数定义：函数的定义包含了函数体，通常在 .cpp 文件中。
```cpp
int add(int a, int b) {
    return a + b;
}
```

### 注意事项
- 链接：extern 声明的变量或函数必须在最终链接阶段找到对应的定义，否则会出现链接错误。
- 静态变量与局部变量：extern 不能用于声明静态变量（static）或局部变量，因为它们的作用域限制在定义它们的文件或函数内部。
- 类型匹配：extern 声明必须与实际定义的类型完全匹配，包括返回类型和参数列表（对于函数）。
- 跨编译单元共享：使用 extern 可以帮助实现跨编译单元（.cpp 文件）的变量或函数共享，但过度使用全局变量可能损害代码的模块化和可维护性。
- 本文件中向前**使用extern向前声明**，加不不加extern没有区别。
- 注意：建议只使用extern声明变量，不定义变量。
  - ISO C++标准C++不允许结合 extern 和初始化器来“定义”变量。
  - 但VS2022测试是可以的，可能比较宽松。


## extern "C"
extern "C" 是C++中的一种链接约定（linkage specification），用于解决C++和C语言之间或C++不同编译单元之间的链接兼容性问题。

### 背景
要说清楚 extern "C" 是怎么一回事，还得先说说C++函数重载的那些事。C++有函数重载，而C语言是没有函数重载的。函数重载是指两个或多个函数之间函数名相同，参数列表不同，参数列表不同可以是参数的个数不同，或者是参数的个数相同但参数类型不同，需要注意的是如果函数名相同，参数列表完全相同但返回值类型不同是不能构成函数重载的。C++有函数重载是因为当生成obj中间文件/目标文件的时候，C++编译器把原函数名与参数信息结合，产生了一个独特的内部名字，比如有两个函数 void foo(int x) 和 void foo(void) ,最终产生的内部名字就是 _foo_int 和 _foo_void （实际产生的内部名字的命名规则应该不是这样的，这里我们并不关心它的命名规则是怎样的，只需要体会这个意思就可以了），通过这样编译器就能区分 void foo(int x) 和 void foo(void)这两个函数了。但是在C语言里面，并不会产生这样的内部名字，如果C语言里面有两个函数 void foo(int x) 和void foo(void)，那么当生成obj中间文件/目标文件的时候，产生的名字就是 _foo 和 _foo 这样两个名字相同，C编译器就不能将两个函数区分开了，所以C语言里面也就没了函数重载。

正是由于C++编译器 和 C编译器对函数名处理方式的不同，当我们的 C++ 程序调用 C 程序或者 C 程序调用 C++程序时就会存在问题。 有了问题那当然就得解决，于是就有了 extern "C" 的出现。

所以说到底 extern "C" 的作用是用来**解决名字匹配问题**，实现 C 与 C++ 的混合编程。

### 目的
1. C语言兼容性：C++支持面向对象编程特性，如函数重载、类、模板等，这导致C++的函数名和变量名在编译后会经过名称修饰（name mangling），以便支持这些特性。而C语言没有这些特性，其编译后的符号名是直接的。使用 extern "C" 可以指示C++编译器按照C语言的规则来处理函数和变量名，避免名称修饰，从而使得C++编写的函数和变量能被C代码正确识别和调用。

2. 跨编译器兼容性：即便在纯C++项目中，不同编译器对C++特性支持的程度和名称修饰的规则可能不同。使用 extern "C" 可以确保编译单元间的链接兼容性，尤其是当项目需要跨平台或使用不同编译器编译不同部分时。

### 基本用法
#### 函数声明与定义
```cpp
// 在C++中声明一个C语言风格的函数
extern "C" {
    void myFunction(int arg);
}

// 或者直接在函数前使用
extern "C" void myFunction(int arg);

// 实际定义该函数（通常在cpp文件中）
void myFunction(int arg) {
    // 函数体
}
```
通过 extern "C"，C++编译器会按照C语言的规则来处理函数名，不进行名称修饰（name mangling），使得C代码可以正确识别并调用这些函数。

#### 头文件中的使用
为了同时兼容C和C++，通常在头文件中使用条件编译指令来包裹 extern "C" 块：
```cpp
#ifdef __cplusplus
extern "C" {
#endif

void myFunction(int arg);

#ifdef __cplusplus
}
#endif
```
这样，当被C++编译器处理时，extern "C" 生效；而C编译器会忽略 __cplusplus 宏定义及其内容，直接看到未修饰的函数声明。

### 应用场景
1. C++库提供C接口：当你的库是用C++编写，但需要被C语言编写的程序调用时，使用 extern "C" 可以确保导出的接口函数名称不变，便于C代码链接。

2. 链接C语言库：如果你的C++程序需要调用C语言编写的库，库的头文件中可能已经使用了 extern "C" 来声明函数，你直接包含这些头文件即可。

3. 跨编译器互操作：在某些情况下，即便是在纯C++项目中，使用 extern "C" 也可以帮助解决不同编译器间的链接兼容性问题。


### 注意事项
- 不适用于C++特性的函数：extern "C" 不能应用于C++特有的函数特性，如模板函数、成员函数、重载函数等，因为这些特性在C语言中不存在。

- 变量声明：虽然不常见，extern "C" 也可以用于变量声明，确保变量的链接方式符合C语言规范，但通常这更多用于与C兼容的场景。

- 位置：extern "C" 块通常放在头文件中，这样无论该头文件被C++还是C代码包含时，都能正确处理。

- 条件编译：通常使用 #ifdef __cplusplus 来检查是否在C++编译器中，这样头文件可以同时被C和C++代码安全地使用。

- 作用范围：extern "C" 只影响其后的声明，直到遇到花括号结束或下一个 extern "C++"（或文件结束），因此它可以用来控制链接规范的局部作用域。

### C和C++互相调用
我们既然知道extern "C"是实现的类C和C++的混合编程。下面我们就分别介绍如何在C++中调用C的代码、C中调用C++的代码。首先要明白C和C++互相调用，你得知道它们之间的编译和连接差异，及如何利用extern "C"来实现相互调用。

#### C++的编译和连接
C++是一个面向对象语言（虽不是纯粹的面向对象语言），它支持函数的重载，重载这个特性给我们带来了很大的便利。为了支持函数重载的这个特性，C++编译器实际上将下面这些重载函数：
```cpp
void print(int i);
void print(char c);
void print(float f);
void print(char* s);
```
编译为：
```cpp
_print_int
_print_char
_print_float
_pirnt_string
```
这样的函数名，来唯一标识每个函数，这就是C++中的名字修饰，也有很多优势，可以确保类型安全连接。注：不同的编译器实现可能不一样，但是都是利用这种机制。所以当连接是调用print(3)时，它会去查找 _print_int(3)这样的函数。下面说个题外话，正是因为这点，重载被认为不是多态，多态是运行时动态绑定（“一种接口多种实现”），如果硬要认为重载是多态，它顶多是编译时“多态”。

C++中的变量，编译也类似，如全局变量可能编译g_xx，类变量编译为c_xx等。连接是也是按照这种机制去查找相应的变量。

#### C的编译和连接
C语言中并没有重载和类这些特性，故并不像C++那样print(int i)，会被编译为_print_int，而是直接编译为_print等。因此如果直接在C++中调用C的函数会失败，因为连接是调用C中的 print(3)时，它会去找_print_int(3)。因此extern "C"的作用就体现出来了。

#### C++中调用C的代码
假设一个C的头文件cHeader.h中包含一个函数print(int i)，为了在C++中能够调用它，必须要加上extern关键字（原因在extern关键字那节已经介绍）。它的代码如下：
```c
#ifndef C_HEADER
#define C_HEADER

extern void print(int i);

#endif
```

相对应的实现文件为cHeader.c的代码为：
```c
#include <stdio.h>
#include "cHeader.h"

void print(int i)
{
	printf("cHeader %d\n",i);
}
```

现在C++的代码文件C++.cpp中引用C中的print(int i)函数：
```cpp
extern "C"{
#include "cHeader.h"
}

int main(int argc,char** argv)
{
    print(3);
    return 0;
}
```

```s
linux执行上述文件的命令为：

首先执行gcc -c cHeader.c，会产生cHeader.o；

然后执行g++ -o C++ C++.cpp cHeader.o
```

**==在C++.cpp文件中可以不用包含函数声明的文件，即“extern "C"{#include"cHeader.h"}”，而直接改用extern "C" void print(int i)的形式。==**

>C++.cpp是如何找到C中的print函数，并调用的呢？
那是因为我们首先通过gcc -c cHeader.c 这个命令，产生了一个cHeader.c的目标文件。然后我们通过执行g++ -o C++ C++.cpp cHeader.o这个命令，该命令中指明了要链接的目标文件：cHeader.o,所以C++.cpp中只需要说明哪些函数（比如该题中的void print(int i)）需要以C的形式调用，然后去其目标文件中找该函数即可。注：“.o文件”为目标文件，类似于windows下的obj文件。

#### C中调用C++的代码
现在换成在C中调用C++的代码，这与在C++中调用C的代码有所不同。如下在cppHeader.h头文件中定义了下面的代码：
```cpp
#ifndef CPP_HEADER
#define CPP_HEADER
extern "C" void print(int i);

#endif
```

相应的实现文件cppHeader.cpp文件中代码如下：
```cpp
#include "cppHeader.h"
#include <iostream>
using namespace std;

void print(int i)
{
    cout<<"cppHeader "<<i<<endl;
}
```

在C的代码文件c.c中调用print函数：
```c
extern void print(int i);
int main(int argc,char** argv)
{
    print(3);
    return 0;
}
```

注意在C的代码文件中直接#include "cppHeader.h"头文件，编译出错,原因为：当以头文件的形式包含cppHeader.h时，会将cppHeader.h的内容展开，而cppHeader.h中包含“extern "C"”关键字，而c语言中没有这种用法，所以会出现编译错误。而且如果不加extern int print(int i)编译也会出错。

1. 首先执行命令：g++ cppHeader.cpp -fpic -shared -g -o cppHeader.so
该命令是将cppHeader.cpp编译成动态连接库，其中编译参数的解释如下：
-shared 该选项指定生成动态连接库（让连接器生成T类型的导出符号表，有时候也生成弱连接W类型的导出符号），不用该标志外部程序无法连接。相当于一个可执行文件
-fPIC：表示编译为位置独立的代码，不用此选项的话编译后的代码是位置相关的所以动态载入时是通过代码拷贝的方式来满足不同进程的需要，而不能达到真正代码段共享的目的。
-g：为调试

2. 然后再执行命令：gcc c.c cppHeader.so -o cmain
该命令是编译c.c文件，同时链接cppHeader.so文件，然后产生cmain的可执行文件。

3. 最后执行命令：./cmain 来执行该可执行程序

#### C和C++混合调用特别之处函数指针
当我们C和C++混合编程时，有时候会用一种语言定义函数指针，而在应用中将函数指针指向另一中语言定义的函数。如果C和C++共享同一中编译和连接、函 数调用机制，这样做是可以的。然而，这样的通用机制，通常不然假定它存在，因此我们必须小心地确保函数以期望的方式调用。

而且当指定一个函数指针的编译和连接方式时，函数的所有类型，包括函数名、函数引入的变量也按照指定的方式编译和连接。如下例：
```cpp
typedef int (*FT) (const void* ,const void*);//style of C++

extern "C"{
    typedef int (*CFT) (const void*,const void*);//style of C
    void qsort(void* p,size_t n,size_t sz,CFT cmp);//style of C
}

void isort(void* p,size_t n,size_t sz,FT cmp);//style of C++
void xsort(void* p,size_t n,size_t sz,CFT cmp);//style of C
 
//style of C
extern "C" void ysort(void* p,size_t n,size_t sz,FT cmp);
 
int compare(const void*,const void*);//style of C++
extern "C" ccomp(const void*,const void*);//style of C
 
void f(char* v,int sz)
{
    //error,as qsort is style of C
    //but compare is style of C++
    qsort(v,sz,1,&compare);
    qsort(v,sz,1,&ccomp);//ok
    
    isort(v,sz,1,&compare);//ok
    //error,as isort is style of C++
    //but ccomp is style of C
    isort(v,sz,1,&ccopm);
}
```
注意：typedef int (*FT) (const void* ,const void*)，表示定义了一个函数指针的别名FT，这种函数指针指向的函数有这样的特征：返回值为int型、有两个参数，参数类型可以为任意类型的指针（因为为void*）。

最典型的函数指针的别名的例子是，信号处理函数signal，它的定义如下：
```cpp
typedef void (*HANDLER)(int);
HANDLER signal(int ,HANDLER);
```
上面的代码定义了信函处理函数signal，它的返回值类型为HANDLER，有两个参数分别为int、HANDLER。 这样避免了要这样定义signal函数：
```cpp
void (*signal (int ,void(*)(int) ))(int)
```

比较之后可以明显的体会到typedef的好处。    

### 5.extern 和 static：
#### (1)static
被static修饰的全局变量和函数只能在本模块(本文件)中使用。
>static 表示静态的变量，分配内存的时候，存储在静态区，不存储在栈上面。
#### (2)extern
被extern声明的变量(全局变量)，扩大了使用范围，在声位到本文件结尾都可以使用。
>extern 表明该变量在别的地方已经定义过了，在这里要使用那个变量。

#### (3)extren和static的区别
1. 水火不容(不能同时修饰)
extern和static不能同时修饰一个变量；
2. 声明+定义
static修饰的全局变量声明与定义同时进行，也就是说当你在头文件中使用static声明了全局变量后，它也同时被定义了；
3. 作用域的改变
static修饰全局变量的作用域由全局作用域->文件作用域。作用域只能是本身的编译单元，也就是说它的“全局”只对本编译单元有效，其他编译单元则看不到它。
extern修饰全局变量没有改变其作用域(都是全局作用域)，但扩大了它的使用范围。

- static作用范围是内部连接的关系这和extern有点相反。
- static成员变量和对象本身是分开存储的。extern也是分开存储的，但是extern可以被其他的对象用extern引用，而static不可以，只允许对象本身用它。

### 6.extern和const(重要)
C++中const修饰的全局常量具有跟static相同的特性，即它们只能作用于本编译模块中，且static修饰的是全局变量。
但是const可以与extern连用来声明该常量可以作用于其他编译模块中,如``externconst char g_str[];``
然后在原文件中别忘了定义:``const char g_str[] = "123456";``
所以当const单独使用时它就与static相同，而当与extern一起合作的时候，它的特性就跟extern的一样了！
所以对const我没有什么可以过多的描述，我只是想提醒你：
``const char* g_str = "123456" ``与 ``const char g_str[] ="123465"``是不同的，
前面那个const修饰的是char* 而不是g_str,它的g_str并不是常量，它被看做是一个定义了的全局变量（可以被其他编译单元使用）
所以如果你像让char* g_str遵守const的全局常量的规则，最好这么定义const char* const g_str="123456"。(底层+顶层)
*/