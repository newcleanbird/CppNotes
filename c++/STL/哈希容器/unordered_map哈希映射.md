# unordered_map:哈希表、哈希映射

## 1.介绍

c++的容器——unordered_map，它是一个关联容器，内部采用的是hash表结构，拥有快速检索的功能。

特性：

* 关联性：通过key去检索value，而不是通过绝对地址（和顺序容器不同）
* 无序性：使用hash表存储，内部无序
* Map : 每个值对应一个键值
* 键唯一性：不存在两个元素的键一样
* 动态内存管理：使用内存管理模型来动态管理所需要的内存空间

Hashtable和bucket：
    由于unordered_map内部采用的hashtable的数据结构存储，所以，每个特定的key会通过一些特定的哈希运算映射到一个特定的位置，
    我们知道，hashtable是可能存在冲突的（多个key通过计算映射到同一个位置），在同一个位置的元素会按顺序链在后面。
    所以把这个位置称为一个bucket是十分形象的（像桶子一样，可以装多个元素）。

## 2.模板

unordered_map的官方定义

```cpp
template < class Key,                                    // unordered_map::key_type
           class T,                                      // unordered_map::mapped_type
           class Hash = hash<Key>,                       // unordered_map::hasher
           class Pred = equal_to<Key>,                   // unordered_map::key_equal
           class Alloc = allocator< pair<const Key,T> >  // unordered_map::allocator_type
           > class unordered_map;
    
```

* 主要使用的也是模板的前2个参数<键，值>：`unordered_map<const Key, T> map;`
* key值还可以是链表节点，即：`unordered_map<ListNode*，int>`

### 2.1迭代器

unordered_map的迭代器是一个指针，指向这个元素，通过迭代器来取得它的值。

```cpp
unordered_map<Key,T>::iterator it;
(*it).first;             // the key value (of type Key)
(*it).second;            // the mapped value (of type T)
(*it);                   // the "element value" (of type pair<const Key,T>)
```

其中it->first返回的是key值，it->second返回的是value值

e.g.

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main()
{
    //创建 umap 容器
    unordered_map<string, string> umap{
        {"Python教程","<http://c.biancheng.net/python/"}>,
        {"Java教程","<http://c.biancheng.net/java/"}>,
        {"Linux教程","<http://c.biancheng.net/linux/"}> };
    cout << "umap 存储的键值对包括：" << endl;
    //遍历输出 umap 容器中所有的键值对
    for (auto iter = umap.begin(); iter != umap.end(); ++iter) {
        cout << "<" << iter->first << ", " << iter->second << ">" << endl;
    }
    //获取指向指定键值对的前向迭代器
    unordered_map<string, string>::iterator iter = umap.find("Java教程");
    cout <<"umap.find(\"Java教程\") = " << "<" << iter->first << ", " << iter->second << ">" << endl;
    return 0;
}
```

注意，遍历打印后是乱序的，unordered map是hash表。不是排序的。只有map是排序的，但是map打印也和构造的顺序不一样。
所以键值对的容器一般用来查找，而不是顺序存储
    
e.g.
```cpp
    {
        unordered_map<string,int>mymap = {{"hh",1},{"aa",2},{"ch",4},{"France",6},{"U.S.",8},{"AC.",10}};
        for(auto y = mymap.begin(); y != mymap.end(); ++y)
            cout<<y->first<<"  "<<y->second<<endl;
        cout<<endl;
        map<string,int>mymap_1 = {{"hh",1},{"aa",2},{"ch",4},{"France",6},{"U.S.",8},{"AC.",10}};
        for(auto x = mymap_1.begin(); x != mymap_1.end(); ++x)
            cout<<x->first<<"  "<<x->second<<endl;
    }
    {
        打印：

        U.S. 8
        ch 4
        AC. 10
        aa 2
        France 6
        hh 1
         
        AC. 10
        France 6
        U.S. 8
        aa 2
        ch 4
        hh 1
    }
```

### 2.2功能函数

#### 2.2.1构造函数

unordered_map的构造方式有几种：

* 构造空的容器
* 用数组构造
* 复制构造
* 范围构造

```cpp
    {
        unordered_map<int,int>hashmap_1;                                            //构造空的容器
        unordered_map<string,int>hashmap_2{{"Jan",44}, {"Jim", 33}, {"Joe", 99}};   //直接构造
        unordered_map<string,int>hashmap_3(hashmap_2);                              // 复制初始化
        unordered_map<string,int>hashmap_4(hashmap_2.begin(),hashmap_2.end());      // 范围初始化
    }
    还有一种是移动构造，不常用:
    {
        #include <iostream>
        #include <string>
        #include <unordered_map>
        using namespace std;

        typedef unordered_map<string,string> stringmap;

        int main ()
        {
        stringmap first;                              // 空
        stringmap second = {{"apple","red"},{"lemon","yellow"}};       // 用数组初始
        stringmap third = {{"orange","orange"},{"strawberry","red"}};  // 用数组初始
        stringmap fourth (second);                    // 复制初始化
        stringmap sixth (fifth.begin(),fifth.end());  // 范围初始化

        cout << "sixth contains:";
        for (auto& x: sixth) cout << " " << x.first << ":" << x.second;
        cout << endl;

        return 0;
        }
    }
    输出结果：
    sixth contains: apple:red lemon:yellow orange:orange strawberry:red
```

### 2.2.2 容量操作
    (1)size()
    //返回unordered_map容器中的元素数量。
    mymap.size()
    (2)max_size
    //返回unordered_map容器可以容纳的元素的最大数量。
    mymap.max_size()
    (3)bucket_count
    //容器内部bucket的数量
    mymap.bucket_count()
    注意：一个bucket下面可能有多个元素
    (4)empty
    //如果容器大小为0则返回true，否则返回false
    mymap.empty()
    (5)load_factor——负载因子
    //返回unordered_map容器中的当前负载因子。
    unordered_map<string,string> mymap = {
            {"us","United States"},
            {"uk","United Kingdom"},
            {"fr","France"},
            {"de","Germany"}
    };
    cout<<mymap.load_factor()
    结果为0.8

### 2.2.3 元素操作

(1)find——查找元素
{
    //查找key所在的元素。
    //- 找到：返回元素的迭代器。通过迭代器的first和second属性获取值
    //- 没找到：返回unordered_map::end
    string input = "mom";
    unordered_map<string, double>::const_iterator got = mymap.find(input);
    if(got == mymap.end())
        cout << "not found";
    else
        cout << got->first << " is " << got->second;
}

(2)insert——插入元素
unordered_map<string,double> myrecipe;
unordered_map<string,double> mypantry = {{"milk",2.0},{"flour",1.5}};
pair<string,double> myshopping ("baking powder",0.3);
myrecipe.insert (myshopping);                        // 复制插入
myrecipe.insert (make_pair<string,double>("eggs",6.0)); // 移动插入
myrecipe.insert (mypantry.begin(), mypantry.end());  // 范围插入
myrecipe.insert ({{"sugar",0.8},{"salt",0.1}});    // 初始化数组插入(可以用二维一次插入多个元素，也可以用一维插入一个元素)
myrecipe["coffee"] = 10.0;  //数组形式插入

(3)at ——查找key所对应的值
{
    //查找key所对应的值
    //- 如果存在：返回key对应的值，可以直接修改，和[]操作一样。
    //- 如果不存在：抛出 out_of_range 异常.
    unordered_map<string,double> mypantry = {{"milk",2.1},{"flour",1.5}};
    cout<<mypantry.at("milk");
    结果打印2.1
}

(4)erase —— 擦除元素
{
    unordered_map<int,int>mymap = {{1111,1},{1112,2},{1113,4},{1114,6},{1115,8},{1117,10}};print_map(mymap);
    mymap.erase(mymap.begin());print_map(mymap);
    mymap.erase(1112);print_map(mymap);
    mymap.erase(mymap.find(1114), mymap.end());print_map(mymap);

    结果：
    1117  10
    1115  8
    1114  6
    1113  4
    1112  2
    1111  1

    1115  8
    1114  6
    1113  4
    1112  2
    1111  1

    1115  8
    1114  6
    1113  4
    1111  1

    1115  8

}

(5)clear—— 清空元素
```cpp
mymap.clear();
{
    unordered_map<int,int>mymap = {{1111,1},{1112,2},{1113,4},{1114,6},{1115,8},{1117,10}};
    cout<<mymap.size()<<"  "<<mymap.max_size()<<"   "<<mymap.bucket_count()<<endl;    
    mymap.clear();
    cout<<mymap.size()<<"  "<<mymap.max_size()<<"   "<<mymap.bucket_count()<<endl;  
    结果：
    6  576460752303423487   7
    0  576460752303423487   7
}
```

(6)swap ——交换

```cpp
//交换两个unordered_map（注意，不是交换特定元素，是整个交换两个map中的所有元素）
mymap.swap(hemap);

(7)count——元素计数
mymap.swap(k);
在容器中搜索键为k的元素，并返回找到的元素数量。
因为unordered_map容器不允许重复的键，这意味着如果容器中存在具有该键的元素，则该函数实际返回1，否则返回0。
```

## unordered_map 进阶操作

“直接定址”与“解决冲突”是哈希表的两大特点。
    hash_map中直接地址用hash函数生成，解决冲突，用比较函数解决。
    由此可见，要使用哈希表, 和用户相关的是：hash函数和比较函数

(1)在声明自己的哈希函数时要注意以下几点：
    使用struct，然后重载operator().
    返回是size_t
    参数是你要hash的key的类型。
    函数是const类型的。
    方法：一般自定义类型可能包含几种内置类型，我们可以分别计算出内置类型的 Hash Value 然后对它们进行结合得到一个哈希值，一般直接采用移位加异或（XOR）便可得到还不错的哈希值（碰撞不会太频繁），

(2)比较函数的实现
    <1> 重载==运算符
    <2> 仿函数

(3)键值为基本数据类型的unordered_map使用
在SGI STL中，提供了以下hash函数：

```cpp
{
    struct hash<char*>
    struct hash<const char*>
    struct hash<char>
    struct hash<unsigned char>
    struct hash<signed char>
    struct hash<short>
    struct hash<unsigned short>
    struct hash<int>
    struct hash<unsigned int>
    struct hash<long>
    struct hash<unsigned long>
}
```

好在,系统为string也提供了hash函数hash< string >,因此当键值为string时，不用自己写哈希函数，
如下，分别为基本数据类型和自定义数据类型使用unordered_map

```cpp
{
    #include<iostream>
    #include<unordered_map>
    #include <string>
    using namespace std;
    void test1(){
    unordered_map<string, int> map;
    hm["孙"]=0;
    hm["李"]=1;
    hm["张"]=2;
    for (auto h : map)
    {
        cout << h.first << "->" << h.second << endl;
    }
    }
    void test2(){
    unordered_map<int, int> map;
    hm[0]=0;
    hm[1]=1;
    hm[2]=2;
    for (auto h : map)
    {
    cout << h.first << "->" << h.second << endl;
    }
    }
    int main()
    {
        test1();//键值为string验证
        test2();//键值为int验证
    }
}
```

但是什么时候我们才要进行hash函数与比较函数的重写呢？
在键值为自定义数据类型的时候，或者当键值string类型时，需要对其进行一些操作时。

```cpp
{
    //自定义数据类型作为键值：
    struct Node
    {
    Node(int data, string letter){ this->data = data; this->letter = letter; }
    int data;
    string letter;
    bool operator==(const Node & p) const
    {
    return data == p.data && letter == p.letter;
    }
    };
    struct hash_name
    {
    size_t operator()(const Node & p) const{
    return hash<string>()(p.letter) ^ hash<int>()(p.data);
    }
    };
    int main(void)
    {
        Node n1(1, "a");
        Node n2(2, "b");
        Node n3(3, "c");
        Node n4(4, "d");
        unordered_map<Node, int, hash_name>map;
        map[n1] = 1;
        map[n2] = 2;
        map[n3] = 3;
        map[n4] = 4;
        for (auto h : map){
            cout << h.first.letter << "->" << h.second << endl;
            }
    }
}
```
