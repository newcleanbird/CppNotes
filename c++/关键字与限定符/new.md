# new

在C++中，关键字new是一个非常重要的内存管理工具，它用于动态地在运行时从堆上分配内存。
new操作符允许程序员在程序执行过程中创建对象和数组，并返回指向新分配内存的指针。

## new使用方法

c++通过new关键字进行动态分配内存。
new开辟的空间存储在堆上，而我们定义的变量存储在栈上。
new分配的空间使用delete释放，new[] 使用 delete[]。

### 开辟单个堆区元素

语法：

```cpp
type* name = new type(content); // 申请类型为type的name对象
/*
type:元素类型
content是元素内容
name是变量名
*/
delete name;    // 释放name对象
```

### 创建数组并返回数组指针

语法:

```cpp
type* name = new type[size];    // 申请数组
/*
type:元素类型
name是变量名
size:数组空间数量
*/
delete []name // 释放数组
```

这将分配足够内存来存储arraySize个连续的Type对象，并返回一个指向第一个元素的指针。注意，这里不会调用构造函数，除非是使用了初始化列表（C++11起）。

==注意：new [] 和 delete [] 必须匹配！==

### 使用new进行初始化

在默认情况下，new是不会对分配的int进行初始化的。要想使分配的int初始化为0，需要显式地调用其初始化函数：

```cpp
int* buffer = new int(); // 分配的一个int初始化为0
int* buffer = new int(0); // 分配的一个int初始化为0
int* buffer = new int(5); // 分配的一个int初始化为5
int* buffer = new int[100];//分配的一个100个int，均为随机值
int* buffer = new int[100](); // 分配的512个int都初始化为0
```

但是无法将分配的所有元素（如数组全体元素）同时初始化为非0值，以下代码是不合法的：

```cpp
int* buffer = new int[512](0); // 语法错误！
int* buffer = new int[512](5); // 语法错误！
```

- 不能为动态新数组指定新的初始值设定项。

### 带参数的构造函数

如果你的类有带参数的构造函数，你可以这样使用new：

```cpp
Type* pointer = new Type(arg1, arg2, ...);
```

这将调用匹配参数列表的构造函数来初始化新对象。

### 初始化列表 (C++11)

C++11引入了列表初始化语法，也可以应用于new操作符：

```cpp
Type* obj = new Type{arg1, arg2}; // 对象
Type* arr = new Type[3]{val1, val2, val3}; // 数组
```

这使得可以更清晰地初始化对象或数组元素。

### 返回值与异常安全

new表达式可能抛出std::bad_alloc异常，当内存不足时。因此，在使用new时应考虑异常处理。

### new与delete

动态分配的内存必须通过delete操作符手动释放，以避免内存泄漏：

```cpp
int *pointer = new int(5);
int *array = new int[5];

delete pointer;          // 释放单个对象
delete[] array;          // 释放数组
```

## new和malloc的区别

1. malloc与free是C++/C语言的标准库函数，new/delete是C++的运算符。它们都可用于申请动态内存和释放内存。
2. 对于非内部数据类型的对象而言，光用maloc/free无法满足动态对象的要求。对象在创建的同时要自动执行构造函数，对象在消亡之前要自动执行析构函数。 由于malloc/free是库函数而不是运算符，不在编译器控制权限之内，不能够把执行构造函数和析构函数的任务强加于malloc/free。
3. new操作符内存分配成功时，返回的是对象类型的指针，类型严格与对象匹配，无须进行类型转换；malloc内存分配成功则是返回void *，需要通过强制类型转换将void*指针转换成我们需要的类型。
4. new内存分配失败时，会抛出bac_alloc异常，它不会返回NULL；malloc分配内存失败时返回NULL。
5. 使用new操作符申请内存分配时无须指定内存块的大小，编译器会根据类型信息自行计算；malloc则需要显式地指出所需内存的尺寸。

## 三种new

new的三种面貌：

- 内存分配运算符：operator new()
- 定位放置new：placement new()
- new运算符：new operator

C++中使用new运算符产生一个存在于Heap（堆）上对象时，实际上调用了operator new()函数和placement new()函数。
在使用new创建堆对象时，我们要清楚认清楚new的三种面貌，分别是：new operator、operator new()和placement new()。

### operator new：内存分配运算符

**operator new内存分配运算符**是指C++中的全局内存分配函数，它是一个可以重载的操作符，用于在程序运行时从自由存储区（通常是堆）分配内存。
==注意：::operator new 和 ::operator delete前面加上::表示全局==

operator new()用于申请Heap空间，功能类似于C语言的库函数malloc()，尝试从堆上获取一段内存空间，如果成功则直接返回，如果失败则转而去调用一个new handler，然后抛出一个bad_alloc异常。

#### 函数原型

operator new()的函数原型一般为：

```cpp
void* operator new (std::size_t size) throw (std::bad_alloc);
```

具体实现如下:

```cpp
void *__CRTDECL operator new(size_t size) throw (std::bad_alloc)
{       
    // try to allocate size bytes
    void *p;
    while ((p = malloc(size)) == 0)      //申请空间
        if (_callnewh(size) == 0)        //若申请失败则调用处理函数
        {       
            // report no memory
            static const std::bad_alloc nomem;
            _RAISE(nomem);               //#define _RAISE(x) ::std:: _Throw(x) 抛出nomem的异常
        }
    return (p);
}
```

- 这个函数接收一个表示所需内存大小的参数（以字节为单位），并返回一个指向已分配内存的指针。如果内存分配失败，它通常会抛出一个std::bad_alloc异常。

- operator new()分为全局和类成员。
  - 当为类成员函数时，使用new产生类对象时调用的则是其成员函数operator new()。
  - 如果要重载全局的operator new会改变所有默认的operator new的方式，所以必须要注意。
- 正如new与delete相互对应，operator new与operator delete也是一一对应，如果重载了operator new，那么理应重载operator delete。

#### operator new操作符的一般调用方法

调用operator new申请内存，内存申请的大小为自定义类Func的大小，经过调试发现，并没有输出类Func的构造函数，也没有调用Func的析构函数

```cpp
Student *pstu = (Student *)::operator new(sizeof(Student)); // 申请内存,不调用构造函数
::operator delete(pstu);    // 释放内存，不调用析构函数
```

#### 重载operator new操作符

1. 首先Student类中添加如下信息，重载operator new操作符，支持接受一个参数。重载operator delete操作符，支持接受一个参数，该参数是一个指针，指向将要释放内存的地址。

    ```cpp
    operator new声明：
    void * operator new(size_t size);
    void operator delete(size_t size);

    void * Student::operator new(size_t size)
    {
        cout << "operator new" << endl;
        return ::operator new(size);
    }

    void Student::operator delete(void * ptr)
    {
        cout <<"operator delete" << endl;
    }
    ```

2. 主程序中调用new创建Student对象，然后调用delete释放对象

```cpp
Student * sptr = new Student;
delete sptr;
```

函数operator new 通常声明如下：

```cpp
void * operator new(size_t size);
```

其返回值类型是void * ，返回一个指针，指向一块原始的、未设初值的内存，函数中size_t参数表示需要分配多少内存。你可以重载operator new，加上额外的参数，但参数第一个类型必须是size_t。
例子：

```cpp
void *rawMemory = operator new(sizeof(string));
```

这里的operator new将返回指针，指向一块足够容纳一个string对象的内存。和malloc一样，operator new唯一任务就是分配内存。

### new operator：new运算符

**new operator(new运算符)**是C++保留的关键字，我们无法改变其含义(无法重载)，但我们可以改变new完成它功能时调用的两个函数，operator new()和placement new()。也就是说我们在使用运算符new时，其最终是通过调用operator new()和placement new()来完成堆对象的创建工作。使用new operator时，其完成的工作有如下三步：
(1)调用::operator new申请内存(这里理解为C语言中的malloc)
(2)调用构造函数，将配置得来的对象设立初值。
(3)返回对象指针

因此，当我们经常按照如下方式使用new operator时：

```cpp
string* sp=new string(“hello world”);
```

实际上等价于：

```cpp
//第一步：申请原始空间，行为类似于malloc
void* raw=operator new(strlen(“hello world”));
//第二步：通过placement new调用string类的构造函数，初始化申请空间
new (raw) string(“hello world”);
//第三部：返回对象指针
string* sp=static_cast<string*>(raw);
```

- new操作符不能被重载

### placement new()：定位放置new

一般来说，使用new申请空间时，是从系统的堆中分配空间，申请所得空间的位置根据当时内存实际使用情况决定。但是，在某些特殊情况下，可能需要在程序员指定的特定内存创建对象，这就是所谓的“定位放置new”（placement new）操作。placement new()是一个特殊的operator new()，因为其是operator new()函数的重载版本，只是取了个别名叫作placement new罢了。作用是在已经获得的堆空间上调用类构造函数来初始化对象，也就是定位构造对象。通常情况下，构造函数是由编译器自动调用的，但是不排除程序员手动调用的可能性，比如对一块未初始化的内存进行处理，获得想要的对象，这是需要求助于placement new()。placement new()是C++标准库的一部分，被申明在头文件`<new>`中

#### placement new()函数原型

```cpp
void* operator new(std::size_t, void* __p);
```

具体实现如下：

```cpp
void* operator new(std::size_t, void* __p) throw()
{
    return __p;
}
```

注意：

1. placement new()的函数原型不是void*placement new(std::size_t, void* __p);
2. placement new只是operator new()的一个重载，多了一个已经申请好的空间，由void* __p指定；
3. 用法是new (addr) constructor()，对addr指定的内存空间调用构造函数进行初始化。为何称为placement new，从其用法可以看出只是用于调用构造函数。
定位放置new操作的语法形式不同于普通的new操作。例如，一般都用如下语句A*p=new A;申请空间，而定位放置new操作则使用如下语句A* p=new (ptr) A;申请空间，其中ptr就是程序员指定的内存首地址。

考察如下程序。

```cpp
#include <iostream>
using namespace std;
 
class A{
    int num;
public:
    A(){
        cout<<"A's constructor"<<endl;
    }
 
    ~A(){
        cout<<"~A"<<endl;
    }
    void show(){
        cout<<"num:"<<num<<endl;
    }
};
 
int main(){
    char mem[100];
    mem[0]='A';
    mem[1]='\0';
    mem[2]='\0';
    mem[3]='\0';
    cout<<(void*)mem<<endl;
    A* p=new (mem) A;
    cout<<p<<endl;
    p->show();
    p->~A();
    getchar();
}
```

程序运行结果：

```cpp
0024F924
A’s constructor
0024F924
num:65
~A
```

阅读以上程序，注意以下几点。

1. 用定位放置new操作，既可以在栈(stack)上生成对象，也可以在堆（heap）上生成对象。如本例就是在栈上生成一个对象。
2. 使用语句A* p=new (mem) A;定位生成对象时，指针p和数组名mem指向同一片存储区。所以，与其说定位放置new操作是申请空间，还不如说是利用已经请好的空间，真正的申请空间的工作是在此之前完成的。
3. 使用语句A *p=new (mem) A;定位生成对象是，会自动调用类A的构造函数，但是由于对象的空间不会自动释放（对象实际上是借用别人的空间），所以必须显示的调用类的析构函数，如本例中的p->~A()。
4. 万不得已才使用placement new，只有当你真的在意对象在内存中的特定位置时才使用它。例如，你的硬件有一个内存映像的I/O记时器设备，并且你想放置一个Clock对象在哪那个位置。

### 三种new总结

1. 若想在堆上建立一个对象，应该用new操作符。它既分配内存又调用其构造函数进行初始化。
2. 若仅仅想分配内存，应该调用operator new(),他不会调用构造函数。
3. 若想定制自己在堆对象被建立时的内存分配过程，应该重写自己的operator new()。
4. 若想在一块已经获得的内存空间上建立一个对象，应该用placement new。虽然在实际开发过程中，很少需要重写operator new()，使用内置的operator new()即可完成大部分程序所需的功能。但知道这些，有助于一个C++程序猿对C++内存的管理有个清楚的认识。

### delete 和 delete[]

为了避免内存泄漏，每个动态内存分配必须与一个等同相反的 deallocation 对应。数operator delete与delete操作符的关系与operator new与new操作符是一样的。delete用于使用使用new申请的空间，operator delete用于释放operator new申请的空间（类似于malloc与free），那谁来清理placement new初始化的内存内容呢？唯一办法就是调用对象的析构函数。
示例代码：

```cpp
string* sp=new string(“hello world”);
delete sp;
```

第一行代码在上文已经剖析，那么当调用delete sp时，发生了什么?
delete sp等价于：

```cpp
ps->~string(); //用于清理内存内容，对应placement new
operator delete(ps);//释放内存空间，对应于operator new()
```

其中operator delete()的函数原型为：

```cpp
void operator delete(void *memoryToBeDeallocated);
```

[delete](../关键字与限定符/=delete.md)

## malloc

## realloc函数

1. 函数原型
extern void *realloc(void*mem_address, unsigned int newsize)

2. 头文件
`# include <stdlib.h>` 或`#include <malloc.h>`

3. 作用
    先判断当前的指针是否有足够的连续空间，如果有，改变mem_address指向的地址，并且将返回mem_address；如果空间不够，先按照newsize指定的大小分配另一块新空间，将原有数据从头到尾拷贝到新分配的内存区域，而后释放原来mem_address所指内存区域（注意：原来指针是自动释放2，不需要使用free），同时返回新分配的内存区域的首地址。
    新的大小可大可小（如果新的大小大于原内存大小，则新分配部分不会被初始化；如果新的大小小于原内存大小，可能会导致数据丢失。
    举例：

    ```cpp
    int *p=(int *)malloc(sizeof(int));//定义一个指向int的指针，指针名为p
    int *base=(int *)realloc(p,10);//重新将p指向的地址扩大范围为10个字节，用新指针base指向扩大后的地址，同时自动释放原指针p；
    ```

4. malloc与realloc搭配使用，用法也有很多相似之处。

- realloc失败的时候，返回NULL。
- realloc失败的时候，原来的内存不改变，不会释放也不会移动。
- 假如原来的内存后面还有足够多剩余内存的话，realloc的内存=原来的内存+剩余内存,realloc还是返回原来内存的地址; 假如原来的内存后面没有足够多剩余内存的话，realloc将申请新的内存，然后把原来的内存数据拷贝到新内存里，原来的内存将被自动 free 掉,realloc返回新内存的地址。
- 如果size为0，效果等同于 free ()。这里需要注意的是只对 指针 本身进行释放，例如对二维指针**a，对a调用realloc时只会释放一维，使用时谨防 内存泄露 。
- 传递给realloc的 指针 必须是先前通过 malloc (), calloc (), 或realloc()分配的。
- 传递给realloc的 指针 可以为空，等同于 malloc 。
