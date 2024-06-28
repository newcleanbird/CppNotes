# cmake简介

CMake是一个跨平台的安装/编译链工具，它能用简单的语句描述所有平台的安装/编译过程。通常在UNIX环境下，CMake根据CMakeLists.txt生成Makefile，在Makefile中定义了具体的编译过程。

## C++项目运行

第一步，在CMakeLists.txt所在目录创建build子目录，切换至build目录并执行“cmake ..”生成Makefile，即本地构建系统。

第二步，此时还应在build目录中，执行“cmake --build .”或“make”生成目标文件或可执行文件。

## 常用指令

### 1.cmake_minimum_required

最低版本号要求
cmake_minimum_required(VERSION 3.10)：指定运行此配置文件所需的 CMake 的最低版本；一般只需指定最小版本。

```cmake
cmake_minimum_required (VERSION 3.1)
```

#### 2.project

项目信息
project：参数值是 Demo1，该命令表示项目的名称是 Demo1 。

```cmake
project (Demo1)
```

### 3.指定C++标准

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED True)

### 4.add_executable

指定生成目标

```cmake
# 第一种：Normal Executables
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
# 第二种：Imported Executables
add_executable(<name> IMPORTED [GLOBAL])
# 第三种：Alias Executables
add_executable(<name> ALIAS <target>)
```

使用指定的源文件来生成目标可执行文件。具体分为三类：普通、导入、别名。此处我们就以普通可执行文件进行说明。

其中`<name>`是可执行文件的名称，在cmake工程中必须唯一。WIN32用于在windows下创建一个以WinMain为入口的可执行文件。MACOSX_BUNDLE用于mac系统或者IOS系统下创建一个GUI可执行应用程序。

### 5.aux_source_directory  

查找指定目录下的所有源文件，然后存进指定变量名
aux_source_directory:该命令会查找指定目录下的所有源文件，然后将结果存进指定变量名。
语法：

```cmake
aux_source_directory(<dir> <variable>)
```

e.g.

```cmake
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})
```

### 6.add_library

根据源码来生成一个库供他人使用
CMake中的add_library命令用于使用指定的源文件向项目(project)中添加库，其格式如下：

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

add_library根据源码来生成一个库供他人使用。`<name>`是个逻辑名称，在项目中必须唯一。完整的库名依赖于具体构建方式（可能为`lib<name>.a` or `<name>.lib`）。

STATIC指静态库，SHARED指动态库，MODULE指在运行期通过类似于dlopen的函数动态加载。

### 7.add_subdirectory

将子目录添加到构建系统中

```cmake
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
```

将子目录添加到构建系统中。source_dir指定一个目录，其中存放CMakeLists.txt文件和代码文件。binary_dir指定的目录存放输出文件，如果没有指定则使用source_dir。

### 8.link_libraries

为目标文件链接依赖的库。
已弃用，参考target_link_libraries

```cmake
link_libraries([item1 [item2 [...]]]
               [[debug|optimized|general] <item>] ...)
```

### 9.target_link_libraries

为目标文件链接依赖的库。

```cmake
target_link_libraries(<target>
                      <PRIVATE|PUBLIC|INTERFACE> <item>...
                     [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
```

为目标文件链接依赖的库。PUBLIC修饰的库或目标会被链接，并成为链接接口的一部分。PRIVATE修饰的目标或库会被链接，但不是链接接口的一部分。INTERFACE修饰的库会追加到链接接口中，但不会用来链接目标文件`<target>`。

### 10.include_directories

将指定目录添加到编译器的头文件搜索路径之下.

```cmake
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
```

将指定目录添加到编译器的头文件搜索路径之下，指定目录被解释为当前源码路径的相对路径。[AFTER|BEFORE]定义了追加指定目录的方式在头还是尾。[SYSTEM]告诉编译器在一些平台上指定目录被当作系统头文件目录。

### 11.include

从指定的文件加载、运行CMake代码。

```cpp
include(<file|module> [OPTIONAL] [RESULT_VARIABLE <VAR>]
                      [NO_POLICY_SCOPE])
```

从指定的文件加载、运行CMake代码。如果指定文件，则直接处理。如果指定module，则寻找module.cmake文件，首先在${CMAKE_MODULE_PATH}中寻找，然后在CMake的module目录中查找。

### 12.link_directories

```cmake
link_directories([AFTER|BEFORE] directory1 [directory2 ...])
```

为链接器添加库的搜索路径，此命令调用之后生成的目标才能生效。link_directories()要放在add_executable()之前。

### 13.find_package

加载外部库到项目中，并且会加载库的细节信息。

```cmake
## 共支持两种模式
# mode1: Module, 此模式需访问Find<PackageName>.cmake文件
find_package(<PackageName> [version] [EXACT] [QUIET] [MODULE]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])

# mode2: Config, 此模式需访问<lowercasePackageName>-config.cmake or <PackageName>Config.cmake
find_package(<PackageName> [version] [EXACT] [QUIET]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [CONFIG|NO_MODULE]
             [NO_POLICY_SCOPE]
             [NAMES name1 [name2 ...]]
             [CONFIGS config1 [config2 ...]]
             [HINTS path1 [path2 ... ]]
             [PATHS path1 [path2 ... ]]
             [PATH_SUFFIXES suffix1 [suffix2 ...]]
             [NO_DEFAULT_PATH]
             [NO_PACKAGE_ROOT_PATH]
             [NO_CMAKE_PATH]
             [NO_CMAKE_ENVIRONMENT_PATH]
             [NO_SYSTEM_ENVIRONMENT_PATH]
             [NO_CMAKE_PACKAGE_REGISTRY]
             [NO_CMAKE_BUILDS_PATH] # Deprecated; does nothing.
             [NO_CMAKE_SYSTEM_PATH]
             [NO_CMAKE_SYSTEM_PACKAGE_REGISTRY]
             [CMAKE_FIND_ROOT_PATH_BOTH |
              ONLY_CMAKE_FIND_ROOT_PATH |
              NO_CMAKE_FIND_ROOT_PATH])
```

find_package一般用于加载外部库到项目中，并且会加载库的细节信息。如上find_package有两种模式：Module与Config。

## CMake 常用变量和常用环境变量

CMAKE_SOURCE_DIR：根源代码目录，工程顶层目录。暂认为就是PROJECT_SOURCE_DIR
CMAKE_CURRENT_SOURCE_DIR：当前处理的 CMakeLists.txt 所在的路径
PROJECT_SOURCE_DIR：工程顶层目录
CMAKE_BINARY_DIR：运行cmake的目录。外部构建时就是build目录
CMAKE_CURRENT_BINARY_DIR：The build directory you are currently in.当前所在build目录
PROJECT_BINARY_DIR：暂认为就是CMAKE_BINARY_DIR
