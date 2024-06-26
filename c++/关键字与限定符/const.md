# const

## const 修饰变量

### const 修饰普通变量

当``const``关键字用于修饰普通变量时，它定义了一个``常量变量``，意味着一旦赋予初始值后，这个变量的值就不能再被改变。这有助于提高程序的健壮性，减少因意外修改变量值导致的错误，并且可以使程序的意图更加清晰。

```cpp
const 数据类型 变量名 = 初始值;
const int age = 25;

在这个例子中，age是一个常量整型变量，其值被设定为25，并且之后的任何尝试修改age值的操作都将导致编译错误。
```

#### 注意事项

1. 初始化：const变量必须在定义时进行初始化。这是因为如果允许后期修改，那么const就失去了意义；如果不初始化，则编译器无法知道变量的确切值，也就无法实施“不可修改”的规则。

2. 存储类别：const变量可以是全局的、局部的、静态的或作为类的成员。它们的存储位置（如数据段、栈或堆）依据变量的其他属性（如作用域和存储类别）而定，并不直接由const关键字决定。

3. 编译时计算：如果const变量的值能在编译时确定（例如，字面量或编译时常量表达式），编译器可能会将其值直接内联到使用该变量的地方，从而可能提高程序效率。

4. 顶层const与底层const：此处讨论的const修饰普通变量属于“顶层const”，它限制了变量本身的可变性。与之相对的是“底层const”，通常与指针或引用一起出现，影响所指对象的可变性，而不是变量本身的可变性。

#### 优点

- 安全性：防止意外修改重要数据。
- 清晰性：使代码易于理解和维护。
- 性能：对于编译器能识别为编译时常量的const变量，可能带来优化机会。

#### const 对比 #define

宏定义也可以定义成常量，二者有什么区别呢？

- 类型安全检查:const常量会进行"类型安全检查"，对define只进行字符替换，没有类型安全检查，在字符替换时可能会产生意料不到的错误。
- 节省空间:const常量更"节省空间"，避免不必要的内存分配- 保存内存地址:const常量从汇编的角度来看，只是给出了对应的"内存地址"，而不是像#define一样给出的是"立即数"，所以，const定义的常量在程序运行过程中只有一份拷贝，而#define宏定义的常量在内存中有若干个拷贝

### const 修饰引用

#### const引用

1. 定义：
    可以把引用绑定到const对象上，就像绑定到其他对象上一样，我们称之为对常量的引用（reference to const）。
2. 本质：
    - 引用本身就是 顶层const，底层为常指针(指针常量)，不能再更换绑定对象。
    - cosnt 引用为 底层const + 顶层 const,即为常量引用。意思是不能通过该引用修改原对象。

```c++
int i = 512;         // i是普通变量
const int ci = 1024; // ci 为常量


const int &r1 = i;  // const引用可以绑定普通变量
const int &r2 = ci; // const引用可以绑定常量

int const &r3 = i;  // 该写法与r1等价
int const &r4 = ci; // 该写法与r2等价


r1 = 42;        // 不能对常量引用的对象赋值
int &r5 = ci;   // 不能使用普通引用绑定常量
```

#### 初始化const引用

一般的，引用的类型要与其所引用对象的类型一致，但是有两个例外：

1. 在初始化常量引用时允许用任意表达式作为初始值，只要该表达式的结果能转换成引用的类型即可。
尤其，允许为一个常量引用绑定非常量的对象、字面值，甚至是个一般表达式：

```c++
int i = 1;
const int &r1 = i;  // 允许const引用绑定非常量的对象
const int &a1 = 2;  // 允许const引用绑定字面值
const int &a2 = 3+4;// 允许const引用绑定一般表达式
```

特殊的：

```cpp
double dval=3.14;
const int & ri=dval;
```

>此处ri引用了一个int形的数，对ri的操作应该是整数运算，但dval却是一个双精度浮点数而非整数，因此为了让ri绑定一个整数，编译器会自动变成以下形式。

```c++
const int temp=dval;
const int &ri=temp;
```

>在这种情况下，ri并没有绑定dval而是绑定了一个临时量，所谓临时量对象就是当编译器需要一个空间来暂存表达式的求值结果时临时创建的一个未命名的对象。程序员们经常把临时对象简称为临时量。当修改dval时，实际上ri引用的值并不发生变化。

```cpp
dval = 10.2;
std::cout << dval;  // 变为：10.2
std::cout << ri;    // 不变：3
```

#### 对const的引用可能引用一个并非const的对象

必须认识到，常量引用仅对"引用可参与的操作"做出了限定，对于"引用的对象本身是不是一个常量未作限定"。因为对象也可能是个非常量，所以允许通过其他途径改变它的值：

```cpp
int i = 42;         // i 是一个普通变量
int &r1 = i;        // 使用普通引用绑定普通变量
const int &r2 = i;  // 使用常量引用绑定普通变量
r1 = 0;             // 对普通引用赋值 可以的
r2 = 0;             // 对常量引用赋值 不可以
```

>r2绑定（非常量）整数i是合法的行为。然而，不允许通过r2修改i的值。
尽管如此，i的值仍然允许通过其他途径修改，既可以直接给i赋值，也可以通过像r1一样绑定到i的其他引用来修改。

### const 修饰指针

#### 指针常量、常指针

- 指针本身是个常量对象，指针用来说明常量的类型，表示该常量是一个指针类型的常量，该对象不可修改，不可再指向其他对象。在指针常量中，指针自身的值是一个常量，不可改变，始终指向同一个地址(对象)。
- 指针常量声明时必须初始化

```cpp
int a = 10, b = 20;
int * const p = &a;
*p = 30; // p不能更换绑定的对象，但指向的对象的值可以修改    
```

#### 常量指针、指向常量的指针（`const int *p`， `int const *p`）

- 与引用一样，也可以令指针指向常量或非常量。类似于常量引用，常量指针/指向常量的指针（pointer to const）不能用于改变其所指对象的值。
- 要想存放常量对象的地址，只能使用指向常量的指针：
- 指针的类型必须与其所指对象的类型一致，但也不绝对，因为允许令一个指向常量的指针指向一个非常量对象：
- 和常量引用一样，指向常量的指针也没有规定其所指的对象必须是一个常量。所谓指向常量的指针仅仅要求不能通过该指针改变对象的值，而没有规定那个对象的值不能通过其他途径改变。
- 试试这样想吧：所谓指向常量的指针或引用，不过是指针或引用“自以为是”罢了，它们觉得自己指向了常量，所以自觉地不去改变所指对象的值

### const修饰函数

#### const 修饰"函数参数"

- 表示"参数不可变"，若参数为引用，可以增加效率(引用传递而不用值拷贝)

```c++
int get_data(const int a) // a在本函数中视为常量,不可修改
```

#### const 修饰"函数返回值"

- 表明返回值不可修改
当函数返回一个对象或引用时，在返回类型前加上const关键字，表示该返回的对象或引用所指向的对象是不可修改的。这对于表达函数的意图非常有用，即告诉调用者这个值是用来查看的，而不是用来修改的。例如：

```cpp
class MyClass {
public:
    // 返回一个常量对象，表明不应修改返回的对象
    const MyClass getConstObject() const {
        return MyClass();
    }
};
```

```c++
定义返回值为常量的函数:
const int get_data(A*  const this ) // 返回值是常量
{
    return this->data;
}
使用:
const int data = get_data();    
```

- 实际是否可修改返回的对象需要根据类型确定：

1. 基本类型、结构体、类对象（非引用返回）：
   - 当函数返回const基本类型（如const int）、结构体或类对象时，返回值会被复制给调用者。由于复制的对象是独立的，调用者即使不使用const接收也不会直接影响到原始数据，但使用const接收可以体现调用者的意图，即该值不应被修改。
2. 引用类型：
   - 如果函数返回const引用（如const MyClass&），调用者需要使用相同类型的引用（即const MyClass&）来接收，以确保不通过引用修改原始数据。
   - 对于非const引用的返回值，如果函数实际上返回了const对象的引用，则必须使用const引用接收，否则编译器会报错，因为不能将const对象的引用绑定到非const引用上。
3. 指针类型：
   - 函数返回const指针（如const int*或const MyClass*），调用者应该使用const指针来接收，以确保不会通过指针修改所指数据。
   - 如果函数返回非const指针，但实际指向的是const数据，直接使用非const指针接收虽可能编译通过，但违反了函数设计的意图，应避免这样做。

- 总结：使用const修饰函数返回值是为传达不可变性的设计意图，无论返回值是何种类型（基本类型、引用、指针或其他复杂类型），调用者都应当尊重这一设计，适当使用const来接收返回值，尤其是当直接操作返回的引用或指针时。这有助于编写更安全、更易理解和维护的代码。

#### const 修饰"成员函数"

**作用：**

1. 表明函数不改变对象状态：这样的成员函数被称为常量成员函数（或const成员函数），它向编译器和程序员保证在该函数内部不会修改类的任何非mutable成员变量。这有助于维护对象的逻辑常量性，即使对象本身可能是可变的。

2. 提升代码可读性和可维护性：通过区分哪些成员函数会修改对象状态，哪些不会，使得代码更容易理解，也有助于其他开发人员更快地了解函数的用途和潜在影响。

3. 支持常量对象调用：const成员函数可以被常量对象调用，而没有const修饰的成员函数则不能。这增加了类的灵活性，使得类的接口更加广泛适用。

4. 重载决策：在函数重载时，const和非const版本的成员函数可以共存，编译器会根据对象是否为常量来选择合适的函数版本调用。

5. 编译器检查：编译器会对const成员函数进行检查，确保它们不修改类的非mutable成员，这有助于提前发现潜在的错误。

**需要注意的点：**

1. mutable成员变量：即使在const成员函数中，被mutable关键字修饰的成员变量仍然是可以修改的。mutable通常用于内部实现细节，比如统计访问次数等，而不影响对象的外部逻辑状态。

2. const正确性：开发者必须确保const成员函数内部确实不改变类的状态（除了mutable成员），否则会导致未定义行为或编译错误。

3. const传播：成员函数内部调用的其他成员函数如果也是const的，则可以继续保证整个操作的const性。如果调用了非const成员函数，则需要确保这样的调用不会违背const的约定。

4. const成员函数的声明和定义：在类的声明和定义中都要加上const关键字来保持一致性。忘记在其中一个地方加const会导致编译错误或不符合预期的函数调用。

5. const成员函数可以被覆盖：在派生类中，const成员函数可以覆盖基类中的同名const成员函数，但必须保持相同的const属性。

#### const "不能"修饰"全局函数(非成员函数)"

当``const``后置修饰成员函数时，它实际上是在修饰该成员函数的隐含参数``this``指针。this指针是一个隐含的常量指针，它指向调用成员函数的对象实例。在成员函数的定义中，``const``关键字的使用表明该函数不会修改通过this指针访问到的任何非mutable成员变量。

- 因为全局函数不属于类，因此没有this指针，因此不能使用const后置修饰全局函数。

>this指针
1.默认的this指针是顶层const，形如 A* const this，是指向类类型非常量版本的常量指针，
2.因为this是隐式的，所以它需要遵循初始化规则，意味着（在默认情况下）我们不能把this绑定到一个常量对象上，这一情况也就使得我们不能在一个常量对象上调用普通的成员函数。
3.后置const修饰成员函数，实际上是底层修饰this指针，不能修改this指针所指向的当前正在调用成员函数的对象实例。

### const修饰类成员

#### const修饰类的成员变量

- 表示成员变量不能被修改，同时只能在初始化列表中赋值

#### const修饰类的成员函数(注意:不能修饰全局函数，因为全局函数没有this指针)

- 该函数不能修改成员变量
- 不能调用非const成员函数，因为任何非const成员函数会有修改成员变量的企图.只能调用const成员函数

#### const修饰类对象

- 对象的任何成员都不能被修改
- const类对象只能调用const成员函数

#### 类中的所有函数都可以声明为const函数吗？哪些函数不能？

1. 静态成员函数（Static Member Functions）：静态成员函数不依赖于类的任何特定实例，它们不操作特定对象的状态，而是与类本身关联。因此，静态成员函数没有this指针，自然也就不能声明为const，因为const修饰成员函数本质上是限制对this所指对象的修改。

2. 修改类成员的函数：任何需要修改类中数据成员的函数不能声明为const。这包括直接修改成员变量的值或调用其他会修改成员变量的方法。

3. 返回非const引用或指针到类成员的函数：如果一个成员函数返回类成员的引用或指针，并且用户有可能通过这个引用或指针修改类的成员，那么这个函数就不能声明为const，因为这将违反const函数不改变对象状态的原则。

4. 构造函数和析构函数：构造函数用于初始化对象，而析构函数用于清理对象资源，它们都不适合也不需要声明为const，因为它们不涉及对象状态的“不变性”问题。

### const代码示例

```cpp
#include <iostream>

class MyClass {
public:
    // 1. 常量成员函数，不改变对象状态
    void displayValue() const {
        std::cout << "Value: " << value << std::endl;
    }

    // 2. 成员函数接受const引用参数，不修改传入对象
    void setValue(const MyClass& other) {
        value = other.value; // 此处other.value访问的是other的const成员
    }

    // 3. 返回const指针，确保返回的地址内容不被修改
    const int* getPointerToValue() const {
        return &value;
    }

private:
    mutable int counter = 0; // 使用mutable，允许在const成员函数中修改
    int value = 10;
    
    // 4. 常量成员变量，初始化后不可更改
    const int MAX_VAL = 100;

public:
    // 5. 修改counter的函数，演示mutable关键字的使用
    void incrementCounter() const {
        ++counter;
    }
};

int main() {
    MyClass obj1, obj2;

    // 调用常量成员函数
    obj1.displayValue();

    // 传递const引用给函数
    obj1.setValue(obj2);

    // 获取并尝试（错误示范）修改返回的const指针内容
    const int* ptr = obj1.getPointerToValue();
    // 下面的代码会导致编译错误，因为ptr是指向const的
    // *ptr = 20; 

    // 使用mutable成员并在const成员函数中修改
    obj1.incrementCounter();

    return 0;
}
```

- 常量成员函数：displayValue()保证不修改对象状态。
- const引用参数：setValue()接受一个const引用，保证不修改传入的MyClass对象。
- 返回const指针：getPointerToValue()返回一个指向int的const指针，确保指针所指内容不被修改。
- 常量成员变量：MAX_VAL在类中定义为const，其值在对象生命周期内不可变。
- mutable成员变量：counter虽然在常量成员函数incrementCounter()中被修改，但由于被mutable修饰，这是允许的。

### 总结

1. 声明常量：const可以用来定义不可修改的变量，即常量。一旦初始化，其值在程序运行期间不能被改变。

2. 确保不可变性：
   - 成员函数：在成员函数声明末尾添加const，表明该函数不会修改对象的状态（非mutable成员）。这样的函数称为常量成员函数，可以在常量对象上调用。
   - 指针和引用：const可以修饰指针和引用，分别表示指针所指内容不可修改（如const int*）或引用的对象不可修改（如const int&）。

3. 提升代码质量和安全性：
   - 通过限制某些数据的可修改性，减少意外修改的风险，增强程序的稳定性和可靠性。
   - 提高代码的自我文档化能力，使得阅读者能快速识别出哪些部分是不可变的。

4. 重载决议：const和非const成员函数可以构成重载，编译器会根据调用上下文自动选择合适版本，增强了函数接口的灵活性。

5. 编译时检查：编译器会强制执行const的规则，防止违反const限制的操作，帮助提前发现潜在的逻辑错误。

6. 优化：编译器有时可以根据const信息做出优化决策，例如避免不必要的读写检查。

7. 与模板和泛型编程：在模板和泛型编程中，const正确性对于确保类型安全和兼容性至关重要，特别是在类型推导和约束表达式中。

## 顶层const vs 底层const

### 顶层const：防止自身被修改

修饰目标本身为常量

1. 目标为变量->常量

    ```c++
    const int a = 1;  // 常量的值不可修改，禁止给常量赋值
    ```

2. 目标为指针->指针常量/常指针

    ```c++
    int *const p;   // 常指针本身的地址不可修改，即不可再指向其他对象
    ```

### 底层const：防止指向(引用)的对象被修改

#### 指向、引用的对象只可读，不可修改(read-only)

- 并非对象是常量,而是==限制==修饰的指针和引用的==操作==,不能通过该指针和该引用修改对象。但如果对象还有其他普通指针和引用，还是可以修改的。

```c++
// 常量指针/指向常量的指针
int c = 3;
const int * p2 = &c; 
// 常量引用
const & r1 = c; // 引用只有底层修改，因为引用本身就为常量，所以修饰后，引用的量不可变。
```

### 引用只有底层const
>
>引用底层实现是一个常指针，相当于已经被顶层修饰，因此引用只有底层修饰。

### 指针既可以是顶层const也可以是底层const

```c++
int i = 0;
int *const p1 = &i;     // 顶层const，修饰指针本身，因此不能改变p1的值
const int ci = 10;      // 顶层const，修饰量本身，因此不能改变ci的值
const int * p2 = &ci;   // 底层const，修饰的是指向的对象/变量的值不可修改(指向的是常量)，因此不允许改变允许改变 p2 的值

const int *const p3 = p2; // 指向常量的常指针：左边const 底层const(指向常量)，右边const 顶层const(常指针)
const int &r = ci;        // 因为引用不可变，因此引用只有底层const,const 引用 绑定 const常量
```

### 当执行对象的拷贝操作时，顶层const和底层const区别明显

1. 顶层const：不可修改->可读(随意拷贝)
    顶层const不受什么影响：即自身是常量，自身不变，不影响赋值，常量可以给其他任何左值赋值。
2. 底层const：底层const = 底层const
    当执行对象的拷贝操作时，拷入和拷出的对象必须具有相同的底层const资格，或者两个对象的数据类型必须能够转换才行。

>一般来说，非常量可以转换成常量，常量不能转化为非常量。

```c++
int *p = p3;    // 错误：p3是个指向常量的常指针(底层const + 顶层const)，p是普通指针，因此不能进行拷贝
p2 = p3;        // 正确：p2 p3都是底层const
p2 = &i         // 正确：int i = 0, int * 能转化成 const
int &r = ci;    // 错误：普通的引用int&，不能绑定到int常量上
const int &r2 = i;  // 正确：const int&可以绑定到一个普通int上

p3既是顶层const也是底层const，拷贝p3时可以不在乎它是一个顶层const，但是必须清楚它指向的对象得是一个常量。
因此，不能用p3去初始化p，因为p指向的是一个普通的（非常量）整数，p可以修改p3所指空间的数据，为防止p3修改导致错误所以禁止这种行为。
另一方面，p3的值可以赋给p2，是因为这两个指针都是底层const，p3可以相信p2不会修改数据，所以可以放心的把自己指向的地址分享给p2
```

### 总结与记忆

#### 1.(常指针=指针常量) 和 (常目标指针=常量指针)的区分

##### (1)常指针、指针常量

```c++
int *const p; // p是个定值,即指针p不能变
```

这两个是同一个意思，都是在==修饰“指针”==，主语为==指针==，说指针是一个常量``(*const p)``，==指针的指向不能改变==。
>例子：数组名为指针常量，数组名代表数组首地址，指针指向不能改变。

##### (2)常目标指针、常量指针：（经常用来保护数据，我们应该经常使用这个）

```c++
int const *p;   // *p是p指向的对象,const *p即指针指向的对象不可变
```

都是在==修饰“常量”==，主语是==目标==，说目标是常量``(const *p)``，==*p的内容不能被修改==。
>例子：存储在只读存储区的字符串，该字符串是一个常量，内容不能被修改。

#### 2.定义一个指向常量的指针常量

1. 这是一个指针，指针要是一个常量--->`*const p`
2. 整体又是一个常量，所以 `const *const p`
3. 答案：`int const *const p` 或者 `const int *const p`；

#### 3.记忆方法

1. 常指针，说的就是指针是一个常量，指针就是p 所以直接 ``*const p``；
2. 指针常量，这里都说了指针是常量，那指针就是一个常量，指针就是p 所以直接 ``*const p``；
3. 常目标指针：常目标的意思就是目标是常量，目标就是*p，所以直接``const *p``；
4. 常量指针：常量是指针？这个说法就有问题，常量就是常量，内容不可以修改，常量的指针。所以直接``const *p``；
5. 指针是常量，所以地址不能修改（指向不能修改）。
6. 目标是常量，所以内容不能修改。
