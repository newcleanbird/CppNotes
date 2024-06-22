# delete

在C++中，delete关键字有两个主要用途，但它们分别位于不同的上下文中，一个是用于动态内存管理，另一个则是用于禁止某些类成员的继承或实例化。

## 动态内存管理 - delete表达式

在C++中，delete关键字是一个操作符，是用来释放之前通过new操作符动态分配的内存的。它确保了对象的析构函数被调用（如果有的话），并且释放了与对象关联的内存。delete有两种主要的使用形式，分别对应于单个对象和对象数组的释放。

### 释放单个对象

当你要释放一个通过new创建的单个对象时，使用以下形式的delete：

```cpp
delete pointer;
```

这里的pointer是一个之前通过new分配的内存地址的指针。执行delete后，对象的析构函数（如果存在）会被调用，以执行必要的清理工作，随后这块内存被标记为可用，可以被后续的内存分配重用。需要注意的是，删除指针后，指针本身并不会被自动置为nullptr，因此建议手动将其置为nullptr以避免悬挂指针的问题：

```cpp
delete pointer;
pointer = nullptr; // 避免悬挂指针
```

#### 单个对象的释放原型

```cpp
void operator delete(void* ptr) noexcept;
```

这个原型表示标准的delete操作，用于释放单个对象的内存。它接受一个指向之前由new分配的内存的指针作为参数，并释放与之关联的内存。noexcept表明此操作不应该抛出异常。如果定义了自己的析构函数且没有显式调用delete释放内存，编译器会自动插入对operator delete的调用。

### 释放对象数组

如果你通过new[]分配了一个对象数组，那么需要使用带有方括号的delete[]来释放：

```cpp
delete[] arrayPointer;
```

使用delete[]时，数组中的每个对象都会调用自己的析构函数（如果有）。与单个对象的释放一样，释放后应该将指针置为nullptr：

```cpp
delete[] arrayPointer;
arrayPointer = nullptr;
```

#### 数组的释放原型

```cpp
void operator delete[](void* ptr) noexcept;
```

这个原型用于释放由new[]分配的数组内存。它同样接受一个指向数组首元素的指针，并负责释放整个数组的内存空间。和单对象的delete一样，它也不应该抛出异常。

### 重载

operator delete和operator delete[]都可以被用户重载，以实现自定义的内存管理策略。重载时，你可以定义额外的参数，比如一个用于追踪内存分配的大小参数，来帮助管理内存。

### C++11 带有对齐参数的operator new和operator delete

在C++中，为了支持对齐要求较高的类型（例如某些SIMD向量或硬件加速器要求的数据结构），C++11引入了带有对齐参数的operator new和operator delete。这些重载版本允许程序员指定内存分配的对齐方式，以确保数据正确对齐，从而提升程序的性能或兼容性。以下是这些操作符的原型和使用方式：

#### 带对齐参数的operator new

```cpp
void* operator new(std::size_t size, std::align_val_t alignment);
```

这里的size参数表示要分配的内存大小，而alignment参数是一个std::align_val_t类型的值，用于指定所需的对齐边界。std::align_val_t是一个能够表示对齐值的类型，通常通过std::align_val_t{N}的形式来构造，其中N是2的幂，代表对齐的字节数。

#### 带对齐参数的operator delete

```cpp
void operator delete(void* ptr, std::align_val_t alignment) noexcept;
```

此版本的operator delete用于释放由带有对齐参数的operator new分配的内存。它同样接受一个指针和对齐值作为参数，以确保正确地释放内存。

#### 使用示例

尽管直接调用这些带有对齐参数的版本并不常见（通常由编译器根据类型自动处理），但在某些自定义内存管理或特定性能优化的场景下，可能会直接使用它们。例如，如果你有一个需要特定对齐的类型，可以这样分配内存：

```cpp
struct AlignedData {
    alignas(64) int data[100];
};

AlignedData* ptr = static_cast<AlignedData*>(::operator new(sizeof(AlignedData), std::align_val_t{64}));
```

释放时，也要使用对应的带有对齐参数的delete：

```cpp
::operator delete(ptr, std::align_val_t{64});
```

#### 注意事项

确保对齐值是一个有效的对齐值，通常是2的幂。
当重载这些操作符时，

### delete总结与注意事项

- 未初始化的指针：不要对未初始化或已经释放过的指针调用delete。
- 重复释放：重复调用delete或delete[]释放同一块内存会导致未定义行为，可能引起程序崩溃。
- 类型匹配：使用new分配内存时指定的类型必须与delete释放时的类型相匹配，包括数组和非数组类型的区别。
- 自定义内存管理：可以通过重载全局的operator new和operator delete来自定义内存分配和释放的行为。如果你使用了自定义的operator new，也应该提供对应的operator delete版本，以保持内存管理的一致性。
[new](../关键字与限定符/new.md)
- 智能指针：现代C++推荐使用智能指针（如std::unique_ptr和std::shared_ptr）来自动管理动态内存，从而减少手动调用delete的需要。
- 在C++11之后，还可以使用带有对齐参数的operator new和operator delete，以支持对齐要求较高的类型。

## 禁止继承或重写 = delete

[=delete](../关键字与限定符/=delete.md)
