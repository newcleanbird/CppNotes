# realloc

realloc是C语言中的一个内存管理函数，用于调整之前通过malloc、calloc或realloc分配的内存块的大小。虽然C++提供了更高级的内存管理机制，如智能指针和容器类，但realloc在某些特定场景下，尤其是在与C代码交互或者进行低级别内存管理时，仍然是一个可用的工具。

## 函数原型

```cpp
c:
extern void *realloc(void *mem_address, unsigned int newsize)
c++:
void* realloc(void* ptr, size_t size);
```

参数说明:

- void* ptr：之前通过malloc、calloc或realloc分配的内存块的指针。如果ptr为NULL，则realloc的行为等同于malloc(size)。
- size_t size：新的内存块大小（以字节为单位）。如果size为0且ptr非NULL，则会释放内存并返回NULL。如果size大于原内存块的大小，则尝试扩大内存块；如果size小于原内存块的大小，则可能会缩小内存块，但不会返回多余的内存给系统。

### 头文件

`#include <stdlib.h>` 或`#include <malloc.h>`

### 作用

c:
先判断当前的指针是否有足够的连续空间，如果有，改变mem_address指向的地址，并且将返回mem_address；如果空间不够，先按照newsize指定的大小分配另一块新空间，将原有数据从头到尾拷贝到新分配的内存区域，而后释放原来mem_address所指内存区域（注意：原来指针是自动释放2，不需要使用free），同时返回新分配的内存区域的首地址。
新的大小可大可小（如果新的大小大于原内存大小，则新分配部分不会被初始化；如果新的大小小于原内存大小，可能会导致数据丢失。
举例：

```cpp
int *p=(int *)malloc(sizeof(int));//定义一个指向int的指针，指针名为p
int *base=(int *)realloc(p,10);//重新将p指向的地址扩大范围为10个字节，用新指针base指向扩大后的地址，同时自动释放原指针p；
```

c++:
realloc尝试重新分配内存块的大小。如果现有内存块后面有足够的空间满足新大小要求，它可能会直接调整大小而不移动数据。如果当前内存块无法调整到所需大小（比如因为内存碎片问题），realloc可能会分配一个新的内存块，将原内存块的内容复制到新位置，然后释放旧内存块。这表示调用realloc时，传入的指针可能会改变。

### 返回值

- 成功时，返回调整后内存块的新地址，可能与原地址相同也可能不同。
- 失败时，返回NULL，原内存块保持不变，不会释放。因此，建议在调用realloc前先保存原指针，以便在失败时恢复。

### 示例

```cpp
#include <cstdlib>
#include <iostream>

int main() {
    int *ptr = (int*)malloc(sizeof(int)); // 初始分配
    if (ptr == NULL) {
        std::cerr << "Memory allocation failed.\n";
        return 1;
    }
    
    *ptr = 42; // 写入数据
    
    int *newPtr = (int*)realloc(ptr, sizeof(int) * 6); // 扩展内存大小
    if (newPtr == NULL) { // 检查是否成功
        free(ptr); // 如果失败，释放原始内存
        std::cerr << "Memory reallocation failed.\n";
        return 1;
    } else {
        ptr = newPtr; // 更新指针
    }
    
    for(int i = 1; i <= 5; ++i) {
        ptr[i] = i * 10; // 使用扩展后的内存
    }
    
    // 使用完毕，释放内存
    free(ptr);
    return 0;
}
```

## 注意事项

- 数据移动：调用realloc可能导致数据在内存中的位置发生变化，因此在调用后需要检查返回的指针是否与原指针相同。

- 内存泄漏风险：如果realloc失败，原始内存不会被释放，需要在失败路径上手动处理释放。

- 初始化：与malloc一样，realloc扩展或新分配的内存内容是未定义的，可能需要初始化。

- C++实践：虽然realloc在某些场景下可用，但C++推荐使用容器（如std::vector）或智能指针（如std::unique_ptr配合自定义删除器）来更安全、高效地管理动态内存。这些机制能自动处理内存的扩展和收缩，并且与C++的异常安全机制兼容。

### malloc与realloc搭配使用，用法也有很多相似之处

- realloc失败的时候，返回NULL。
- realloc失败的时候，原来的内存不改变，不会释放也不会移动。
- 假如原来的内存后面还有足够多剩余内存的话，realloc的内存=原来的内存+剩余内存,realloc还是返回原来内存的地址; 假如原来的内存后面没有足够多剩余内存的话，realloc将申请新的内存，然后把原来的内存数据拷贝到新内存里，原来的内存将被自动 free 掉,realloc返回新内存的地址。
- 如果size为0，效果等同于 free ()。这里需要注意的是只对 指针 本身进行释放，例如对二维指针**a，对a调用realloc时只会释放一维，使用时谨防 内存泄露 。
- 传递给realloc的 指针 必须是先前通过 malloc (), calloc (), 或realloc()分配的。
- 传递给realloc的 指针 可以为空，等同于 malloc 。
