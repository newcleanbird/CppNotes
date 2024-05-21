# friend友元
在C++中，friend 关键字用于声明友元（Friend）函数或友元类，这是一种特殊机制，允许外部函数或指定的类访问当前类的私有（private）和保护（protected）成员，即使它们不是该类的成员函数或成员类。友元的设计突破了C++严格的封装原则，但有时是必要的，特别是在需要高效访问或操作类的内部数据时。

## 友元的目的
友元的目的:**就是让一个函数或者类 访问另一个类中的私有成员**。

## 友元分为友元函数、友元类。

1. 友元函数：一个非成员函数，被声明为某个类的友元，从而可以访问该类的私有和保护成员。
```cpp
class MyClass {
private:
    int secretData;
public:
    MyClass(int data) : secretData(data) {}
    
    friend void displaySecret(MyClass &obj); // 声明友元函数
};

// 实现友元函数
void displaySecret(MyClass &obj) {
    std::cout << obj.secretData; // 可以访问MyClass的私有成员
}
```

2. 友元类：一个类被声明为另一个类的友元，那么前者的所有成员函数都可以访问后者的私有和保护成员。
```cpp
class Outer {
private:
    int privateVar;
};

class Inner {
public:
    void accessOuterPrivate(Outer &o) {
        o.privateVar = 10; // 可以访问Outer的私有成员
    }
};

class Outer {
private:
    int privateVar;
friend class Inner; // 声明Inner为友元类
};
```

## 友元函数
### 为什么要用友元函数
1. 类的私有成员是不允许类外的任何函数和外部类存取的，可以引入友元函数，是为在该类中提供一个对外(除了它自己以外)访问的窗口
2. 注意:友元函数不是类的成员，不属于任何类
3. 友元函数不属于该类的成员函数,它是定义在类外的普通函数，只是类中声明该函数可以直接访问类中的private或者protected成员 

### 友元函数的声明和定义
1. 声明：友元函数可以在类定义中声明，使用 friend 关键字，然后跟函数原型。
```cpp
class MyClass {
private:
    int secretData;
public:
    MyClass(int data) : secretData(data) {}
    
    friend void displaySecret(MyClass& obj);    // 友元函数
};
```

2. 定义：友元函数的定义与普通函数相同，不在类内部，但可以直接访问类的私有和保护成员。
```cpp
void displaySecret(MyClass& obj) {
    std::cout << "Secret Data: " << obj.secretData << std::endl;
}
```
#### 友元函数注意项
1. 友元函数不是成员函数，即不能用const修饰 无this指针
2. 友元函数可以在类定义的任何地方声明，不受限定符限制
3. 访问权限：友元函数虽然能访问类的私有和保护成员，但它自身并不属于该类的成员函数，因此不能直接使用.或->操作符访问对象成员，需要通过传入对象实例作为参数。
4. 声明位置：友元函数可以在类的公有、私有或保护部分声明，但通常放在公有部分以表明其意图。声明的位置不影响其访问权限。
5. 非成员函数：友元函数可以是独立的全局函数，也可以是另一个类的成员函数。如果是一个类的成员函数，则对该类的所有实例都授予友元访问权限。
6. 多文件编译：如果友元函数定义在另一个文件中，记得在使用前进行适当的声明或定义。


## 友元类
友元类是指一个类被声明为另一个类的友元。友元类可以访问目标类的私有成员，类似于允许其他类访问自己私有成员的特权。

### 定义
当一个类被声明为另一个类的友元时，前者可以访问后者的所有成员，无论它们的访问权限如何。友元关系是单向的，并且是非对称的，也就是说，如果类A是类B的友元，这并不意味着类B自动成为类A的友元。

友元类的声明通常在类的定义内部进行，使用friend关键字：
```cpp
class HelperClass;

class MyClass {
private:
    int data;
public:
    MyClass(int d) : data(d) {}
    friend class HelperClass; // 将HelperClass声明为友元类
};

class HelperClass {
public:
    void manipulateData(MyClass& mc) {
        mc.data *= 2; // 可以直接访问MyClass的私有成员
    }
};
```

### 友元类注意事项：
1. 双向友元：友元关系不具有对称性。如果类A声明类B为友元，类B并不自动成为类A的友元，除非显式声明。
2. 访问权限：友元类的所有成员函数都可以访问另一个类的私有和保护成员，因此需要小心控制，避免不当访问导致的数据不一致或安全性问题。
3. 设计考量：尽量减少友元的使用，因为它们破坏了封装性，降低了类的独立性和代码的可维护性。只有在必要时才使用，比如为了性能优化或实现复杂的协作逻辑。
4. 编译单元：如果友元类定义在不同的编译单元，确保在使用前有正确的声明或包含相应的头文件。
5. 继承与友元关系：友元关系不被继承，即子类不自动继承父类的友元关系，也不能自动成为父类的友元。

## 友元的三种实现
1. 全局函数做友元
2. 类做友元
3. 成员函数做友元

### 全局函数做友元
```cpp
#include <iostream>
#include <string>

using namespace std;

// 房屋类
class Building
{
	// 告诉编译器 laoWang全局函数是 Building类  的好朋友，可以访问Building对象的私有成员
	friend void laoWang1(Building *building);
	friend void laoWang2(Building &building);
	friend void laoWang3(Building building);

public:

	Building()
	{
		m_SittingRoom = "客厅";
		m_BedRoom = "卧室";
	}
	
	string m_SittingRoom;	// 客厅

private:

	string m_BedRoom;		// 卧室
};

//全局函数
void laoWang1(Building *building)
{
	cout << "隔壁老王 全局函数 正在访问：（地址传递） " << building->m_SittingRoom << endl;

	cout << "隔壁老王 全局函数 正在访问：（地址传递） " << building->m_BedRoom << endl;
}

void laoWang2(Building &building)
{
	cout << "隔壁老王 全局函数 正在访问：（引用传递） " << building.m_SittingRoom << endl;

	cout << "隔壁老王 全局函数 正在访问：（引用传递） " << building.m_BedRoom << endl;
}

void laoWang3(Building building)
{
	cout << "隔壁老王 全局函数 正在访问：（ 值传递 ） " << building.m_SittingRoom << endl;

	cout << "隔壁老王 全局函数 正在访问：（ 值传递 ） " << building.m_BedRoom << endl;
}

void test()
{
	Building building;
	laoWang1(&building);
	laoWang2(building);
	laoWang3(building);
}


int main()
{
	test();
}

```
```cpp
隔壁老王 全局函数 正在访问：（地址传递） 客厅
隔壁老王 全局函数 正在访问：（地址传递） 卧室
隔壁老王 全局函数 正在访问：（引用传递） 客厅
隔壁老王 全局函数 正在访问：（引用传递） 卧室
隔壁老王 全局函数 正在访问：（ 值传递 ） 客厅
隔壁老王 全局函数 正在访问：（ 值传递 ） 卧室
```

### 类做友元
```cpp
#include <iostream>
#include <string>

using namespace std;

// 类作友元

class Building;
class LaoWang
{
public:

	LaoWang();

	void visit();	//参观函数  访问Building中的属性

	Building * building;


private:


};

// 房屋类
class Building
{
	// 告诉编译器，LaoWang类是Building类的好朋友，可以访问Building类的私有成员
	friend class LaoWang;
public:
	
	Building();
		
	string m_SittingRoom;	// 客厅
	
private:
	
	string m_BedRoom;		// 卧室
};

// 类外定义成员函数

Building::Building()
{
	m_SittingRoom = "客厅";
	m_BedRoom = "卧室";
}

LaoWang::LaoWang()
{
	// 创建建筑物对象
	building = new Building;
}

void LaoWang::visit()
{
	cout << "隔壁老王LaoWang类正在访问：" << building->m_SittingRoom << endl;

	cout << "隔壁老王LaoWang类正在访问：" << building->m_BedRoom << endl;
}

void test()
{
	LaoWang lw;
	lw.visit();
}

int main()
{
	test();

	return 0;
}
```
输出结果
```s
隔壁老王LaoWang类正在访问：客厅
隔壁老王LaoWang类正在访问：卧室
```

### 成员函数做友元
```cpp
#include <iostream>
#include <string>

using namespace std;

class Building;

class LaoWang
{
public:

	LaoWang();
	void visit1();	//让visit1()函数   可以 访问Building中的私有成员
	void visit2();	//让visit2()函数 不可以 访问Building中的私有成员

	Building *building;

private:

	
};

class Building
{
	// 告诉编译器，LaoWang类下的visit1()函数是Building类的好朋友，可以访问Building的私有成员
	friend void LaoWang::visit1();

public:
	Building();

	string m_SittingRoom;	//客厅
private:

	string m_BedRoom;		//卧室
};


LaoWang::LaoWang()
{
	building = new Building;
}

void LaoWang::visit1()
{
	cout << "隔壁老王LaoWang类中的visit1()函数正在访问：" << building->m_SittingRoom << endl;
	cout << "隔壁老王LaoWang类中的visit1()函数正在访问：" << building->m_BedRoom << endl;
}

void LaoWang::visit2()
{
	cout << "隔壁老王LaoWang类中的visit2()函数正在访问：" << building->m_SittingRoom << endl;
	//cout << "隔壁老王LaoWang类中的visit2()函数正在访问：" << building->m_BedRoom << endl;	//错误！私有属性不可访问
}

Building::Building()
{
	m_SittingRoom = "客厅";
	m_BedRoom = "卧室";
}

void test()
{
	LaoWang lw;
	
	lw.visit1();

	lw.visit2();
}

int main()
{
	test();
	
	return 0;
}
```

## 友元与封装性
封装是面向对象编程的重要特性之一，它强调将数据和对数据的操作封装在一个单元（类）中，同时通过公有接口控制对数据的访问。友元机制可能会打破这种封装性，因为它允许其他类或函数直接访问目标类的私有成员。

虽然友元在某些情况下很有用，但过度使用友元可能导致代码失去封装性和难以维护。因此，在使用友元时应该谨慎考虑，确保只有在必要的情况下使用它。


## 友元的特点
- 单项性：友元关系是单向的。即A是B的友元，不代表B也是A的友元。
- 非传递性：如果A是B的友元，B是C的友元，这并不意味着A是C的友元。
- 不可继承：友元关系不能被继承，即子类不能自动成为父类的友元，反之亦然。
- 非类成员：友元不是类的成员，它们不继承也不影响类的接口。
- 访问权限：友元具有完全访问权限，包括私有和保护成员，但不包括访问控制或构造函数、析构函数的特殊性质。
- 使用谨慎：友元破坏了封装性，应谨慎使用，仅在必要时作为优化或设计上的权衡。

### 应用场景
- 操作符重载：如重载 << 或 >> 流操作符，通常需要访问类的私有成员。
- 调试辅助类：提供专门的调试类访问私有成员，便于调试和分析。
- 紧密合作的类：两个类之间有紧密的协作关系，频繁且深入地需要访问彼此的内部状态。
- 优化：在某些性能敏感的代码中，可能需要直接访问成员来避免不必要的函数调用开销。

## 使用友元通用注意事项
- 文档和注释：清楚地记录为什么需要友元关系，因为这可能不是显而易见的。良好的注释有助于维护人员理解设计决策。
- 替代方案：在使用友元之前，考虑是否有其他设计模式或技术可以达到同样的目的，例如提供公共的访问方法或使用委托模式。
- 代码审查：友元的使用应作为代码审查的重点，确保其必要性和正确性，避免过度使用导致的架构混乱。

## 嵌套类与友元的关系
虽然嵌套类和友元在概念上是独立的，它们可以结合使用来实现特定的访问控制策略：

1. 外部类作为嵌套类的友元：默认情况下，外部类不需要声明为嵌套类的友元，因为它已经能够访问嵌套类的所有成员。但如果你定义了一个私有的嵌套类，并且想要在外部类的外部定义一个函数或类作为该嵌套类的友元，那么这种设计可以增强控制和封装。

2. 嵌套类作为外部类的友元：如果希望嵌套类能够访问外部类的私有或保护成员，这是自然的，因为嵌套类定义在外部类的作用域内，天然具有这种访问权限，无需额外声明为友元。

3. 嵌套类作为其他类的友元：嵌套类也可以被声明为外部类之外的其他类的友元，这种情况下，嵌套类扮演了一个特殊的访问角色，可以访问那些非友元类无法访问的资源。

## 为什么流插入和流提取运算符不能直接写在类内？
友元声明（friend声明）在C++中用于赋予非成员函数或另一个类访问当前类的私有（private）和保护（protected）成员的权限。流插入运算符（operator<<）和流提取运算符（operator>>()）的重载通常被声明为类的友元，以允许这些运算符直接访问类的私有成员来进行读写操作。

**为什么流插入和流提取运算符不能直接写在类内？**
1. 访问权限：直接在类内部定义这两个运算符作为成员函数会面临一个根本性的问题——成员函数的第一个参数隐式地是this指针，代表当前对象。而对于流操作符，我们希望第一个参数是流对象（如std::cin或std::cout），第二个参数是我们自定义的对象。成员函数的形式不符合这种需求。

2. 操作符对称性：流插入运算符（<<）和流提取运算符（>>）应当是左右对称的，即一个用于输出（写），另一个用于输入（读）。将它们作为成员函数定义会破坏这种对称性，因为成员函数总是与左侧的对象（类实例）绑定，而流操作符需要同时处理流对象和类实例。

3. 友元的优势：将这些运算符定义为友元函数，可以让它们自由地接受两个独立的参数：流对象和类的实例。这样不仅解决了访问权限问题，还保持了操作符使用的自然性和灵活性，符合C++社区的编码习惯和预期。

示例理解：
假设有一个简单的Date类，我们想让它能够与std::ostream（输出流）和std::istream（输入流）配合使用。
```cpp
class Date {
private:
    int year, month, day;

public:
    // 构造函数、析构函数和其他成员函数...

    // 声明友元函数
    friend std::ostream& operator<<(std::ostream& os, const Date& d);
    friend std::istream& operator>>(std::istream& is, Date& d);
};

// 实现在类外
std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << d.year << "-" << d.month << "-" << d.day;
    return os;
}

std::istream& operator>>(std::istream& is, Date& d) {
    is >> d.year >> d.month >> d.day;
    return is;
}
```
通过这样的设计，我们既保持了类的封装性（私有成员依然受到保护），又提供了与流的便捷交互能力。友元声明在这里扮演了桥梁的角色，使得非成员函数能够访问必要的内部状态，以完成数据的读取和输出任务。


总之，友元机制是C++为了在封装和效率、灵活性之间寻找平衡而引入的特殊设计，使用时应充分考虑其对封装性的破坏，并确保其必要性和合理性。

