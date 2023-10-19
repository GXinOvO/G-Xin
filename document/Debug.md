# 1. linux

### 1.1 目录结构

- $Bin$: 全称$binary$，含义是二进制。该目录中存储的都是一些二进制文件，文件都是可以被运行的。
- $Dev$: 该目录中主要存放的是外接设备，例如盘、其他的光盘等。在其中的外接设备是不能直接被使用的，需要挂载(类似window下的分配盘中)
- $Etc$: 该目录主要存储一些配置文件
- $Home$: 表示"家"，表示除了root用户以外其他用户的家目录，类似于windows下的User/用户目录。
- $Proc$: 全称process，表示进程，该目录中存 储的是$Linux$运行时候的进程。
- $Root$: 该目录是$root$用户自己的家目录。
- $Sbin$: 全称$super\ \ binary$，该目录也是存储一些可以被执行的二进制文件，但是必须得有$super$权限的用户才能执行
- $Tmp$: 表示"临时"的，当系统运行时候产生的临时文件会在这个目录存着。
- $Usr$: 存放的是用户自己安装的软件。类似于windows下的$program\ \ files$。
- $Var$: 存放的程序/系统的日志文件的目录
- $Mnt$: 当外接设备需要挂载的时候，就需要挂载到$mnt$目录下

## 2. GCC编译器

### 2.1 前言

1. $GCC$编译器支持编译$Go、Objective-C、Objective-C++、Fortran、Ada、D和BRIG(HSAIL)$等程序；
2. $Linux$开发$C/C++$一定要熟悉$GCC$
3. $VSCode$是通过调用$GCC$编译器来实现$C/C++$的编译工作的
4. 实际使用中:
   - 使用$gcc$指令编译$C$代码
   - 使用$g++$指令编译$C++$代码

### 2.2 编译过程

1. 预处理-$Pre-Processing$

```
# -E 选项指示编译器仅对输入文件进行预处理
g++ -E test.cpp -o test.i		// .i文件
```

2. 编译-$Compiling$

```
# -S 编译选项告诉g++在为C++代码产生了汇编语言文件后停止编译
# g++ 产生的汇编语言文件的缺省扩展名是.s
g++ -S test.i -o test.s
```

3. 汇编-$Assembling$

```
# -c 选项告诉g++仅把源代码编译为机器语言的目标代码
# 缺省时g++建立的目标代码文件有一个.o的扩展名
g++ -c test.s -o test.o
```

4. 链接-$Linking$

```
# -o 编译选项来为将产生的可执行文件用指定的文件名
g++ test.o -o test
```

### 2.3 g++重要编译参数

1. $-g $ 编译带调试信息的可执行文件

```
# -g 选项告诉GCC产生能被GNU调试器GDB使用的调试信息，以调试程序
# 产生带调试信息的可执行文件test
g++ -g test.cpp
```

2. $-O[n]$  优先源代码

``` 
## 所谓优化，例如省略掉代码中从未使用过的变量、直接将常量表达式用结果值代替等等，这些操作会缩减目标文件所包含的代码量，提高最终生成的可执行文件的运行效率。

# -O 选项告诉g++对源代码进行基本优化。这些优化在大多数情况下都会使程序执行的更快。 -O2 选项告诉g++产生尽可能小和尽可能快的代码。如-O2，-O3，-On(n常为0-3)
# -O 同事减小代码的长度和执行时间，其效果等价于-O1
# -O0 表示不做优化
# -O1 为默认优化
# -O2 除了完成-O1的优化之外，还进行一些额外的调整工作，如指令调整等
# -O3 则包括循环展开和其他一些与处理特性相关的优化工作
# 选项将使编译的速度比使用-O时慢，但通常产生的代码执行速度会更快。

# 使用 -O2优化源代码，并输出可执行文件
g++ -O2 test.cpp
```

3. $-I和-L$ 指定库文件 ｜ 指定库文件路径

```
# -l 参数(小写)就是用来制定程序要链接的库，-l参数紧接着就是库名
# 在/lib和/usr/lib和/usr/local/lib力的库直接用-l参数就能链接

# 链接glog库
g++ -lglog test.cpp

# 如果库文件没放在上面三个目录里，需要使用-L参数(大写)指定库文件所在目录
# -L参数跟着的是库文件所在的目录名

# 链接mytest库，libmytest.so在/home/bing/mytestlibfolder目录下
g++ -L /home/bing/mytestlibfolder -lmytest test.cpp
```

4. $-I$ 指定头文件搜索目录

```
# -I
# /usr/include目录一般是不用指定的，gcc知道去那里找，但是如果头文件不在/usr/include里我们就要用-I参数指定了，如果头文件放在/myinclude目录里，那编译命令行就要加上-I/myinclude参数了，如果不加你会得到一个"xxxx..h: No such file or directory"的错误。-I参数可以用相对路径，比如头文件在当前目录，可以用-I.来指定。上面我们提到的-cflags参数就是用来生成-I参数的。

g++ -I/myinclude test.cpp
```

5. $-Wall$ 打印警告信息

```
# 打印出gcc提供的警告信息
g++ -Wall test.cpp
```

6. $-w$ 关闭警告信息

```
# 关闭所有警告信息
g++ -w test.cpp
```

7. $-std=c++11$ 设置编译标准

```
# 使用c++11标准编译test.cpp
g++ -std=c++11 test.cpp
```

8. $-o$ 指定输出文件名

```
# 指定即将产生的文件名

# 指定输出可执行文件名为test
g++ test.cpp -o test
```

9. $-D$ 定义宏

```宏
# 在使用gcc/g++编译的时候定义宏

# 常用场景:
# -DDEBUG 定义DEBUG宏，可能文件中有DEBUG宏部分的相关信息，用个DDEBUG来选择开启或关闭DEBUG
```

​	示例代码:

```
// -Dname 定义宏name，默认定义内容为字符串"1"

#include <stdio.h>

int main()
{
	#ifdef DEBUG
		printf("DEBUG LOG\n");
	#endif
		printf("in\n");
}
// 1. 在编译的时候，使用g++ -DDEBUG main.cpp
// 2. 第7行代码可以被执行
```

### 2.4 生成库文件并编译

1. 链接**静态库**生成可执行文件:

```
## 进入src目录下
$cd src

# 汇编，生成Swap.o文件
g++ Swap.cpp -c -I../include
# 生成静态库libSwap.a
ar rs libSwap.a Swap.o

## 回到上级目录
$cd ..

# 链接，生成可执行文件:staticmain
g++ main.cpp -Iinclude -Lsrc -lSwap -o staticmain
```

2. 链接**动态库**生成可执行文件:

```
## 进入src目录下
$cd src

# 生成动态库libswap.so
g++ swap.cpp -I../include -fPIC -shared -o libswap.so
## 上面命令等价于以下两条命令
# gcc swap.cpp -I../include -c -fPIC
# gcc -shared -o libswap.so swap.o

## 回到上级目录
$cd ..
# 链接，生成可执行文件:sharemain
# 这里-lswap是因为lib会省略，libswap被省略至swap
g++ main.cpp -Iinclude -Lsrc -lswap -o sharemain
```

### 2.5 运行可执行文件

1. 运行可执行文件(静态)

```
# 运行可执行文件
./staticmain
```

2. 运行可执行文件(动态)

```
# 运行可执行文件 
LD_LIBRARY_PATH=src ./sharemain
```

## 3. GDB调试器

### 3.1 前言

- $GDB(GNU\ \ Debugger)$是一个用来**调试C/C++程序**的功能强大的**调试器**，是linux系统开发C/C++最常用的调试器
- 程序员可以**使用$GDB$来跟踪程序中的错误**，从而减少程序员的工作量
- $Linux$开发C/C++一定要熟悉$GDB$
- $VSCode$是通过调用$GDB$调试器来实现C/C++的调试工作的

> $Windows$系统中，常见的集成开发环境$(IDE)$，如$VS、VC$等，他们内部已经嵌套了相应的调试器

### 3.2 $GDB$主要功能

- 设置**断点**(断点可以是条件表达式)
- 使程序在指定的代码行上暂停执行，便于观察
- **单步**执行程序，便于调试
- 查看程序中变量值的变化
- 动态改变程序的执行环境
- 分析崩溃程序产生的$core$文件

### 3.3 常用调试命令参数

​	调试开始：执行$gdb[exefilename]$，进入$gdb$调试程序，其中$exefilename$为要调试的可执行文件名

```
## 以下命令后括号内为命令的简化使用，比如run(r),直接输入命令 r 就代表命令run

$(gdb)help(h)	# 查看命令帮助，具体命令查询在gdb中输入help + 命令

$(gdb)run(r)	# 重新开始运行文件(run-text: 加载文本文件，run-bin: 加载二进制文件)

$(gdb)start		# 单步执行，运行程序，停在第一行执行语句

$(gdb)list(l)	# 查看原代码(list-n,从第n行开始查看代码。list + 函数名: 查看具体函数)

$(gdb)set			# 设置变量的值

$(gdb)next(n)	# 单步调试(逐过程，函数直接执行)

$(gdb)step(s)	# 单步调试(逐语句: 跳入自定义函数内部执行)

$(gdb)backtrace(bt)	# 查看函数的调用的栈帧和层级关系

$(gdb)frame(f)	# 切换函数的栈帧

$(gdb)info(i)	# 查看函数内部局部变量的数值

$(gdb)finish	# 结束当前函数，返回到函数调用点

$(gdb)continue(c)	# 继续运行

$(gdb)print(p)	# 打印值及地址

$(gdb)quit(q)	# 退出gdb

$(gdb)break+num(b)	# 在第num行设置断点

$(gdb)info breakpoints	# 查看当前设置的所有断点

$(gdb)delete breakpoints num(d)	# 删除第num个断点

$(gdb)display	# 追踪查看具体变量值

$(gdb)undisplay	# 取消追踪观察变量

$(gdb)i watch	# 被设置观察点的变量发生修改时，打印显示

$(gdb)enable breakpoints	# 启用断点

$(gdb)disable breakpoints	# 禁用断点

$(gdb)x	# 查看内存x/20xw 显示20个单元，16进制，4字节每单元

$(gdb)run argv[1] argv[2]	# 调试时命令行传参

$(gdb)set follow-fork-mode child	# Makefile项目管理: 选择跟踪父子进行(fork())
```

> $Tips:$
>
> 1. 编译程序时需要加上$-g$，之后才能用$gdb$进行调试:$gcc\ \ -g\ \ main.c\ \ -o\ \ main$
> 2. 回车键: 重复上一命令

## 4. CMake

### 4.1 前言

- $CMake$时一个**跨平台**的安装**编译工具**，可以用**简单**的语句来描述**所有平台**的安装(编译过程)
- $CMake$可以说已经成为**大部分C++开源项目标配**

### 4.2 语法特性介绍

- **基本语法格式：指令(参数1  参数2  ...)**

  - 参数使用**括弧**括起
  - 参数之间使用**空格**或**分号**分开

- **指令是大小写无关的，参数和变量是大小写相关的**

  ```
  set(HELLO hello.cpp)
  add_executable(hello main.cpp hello.cpp)
  ADD_ECECUTABLE(hello main.cpp ${HELLO})
  ```

- **变量使用${}方式取值，但是在IF控制语句中是直接使用变量名**

### 4.3 重要指令和$CMake$常用变量

#### 4.3.1 重要指令

<!--TODO : add a c++ project 多目录构建 -->

- $cmake\_minimum\_required$  -  **指定$CMake$的最小的版本要求**

  - 语法: **cmake\_minimum\_required(VERSION versionNumber[FATAL\_ERROR])**

  ```
  # CMake最小版本要求为2.8.3
  cmake_minimum_required(VERSION 2.8.3) 
  ```

- $Project$  **-  定义工程名称，并可指定工程支持的语言**

  - 语法：**project(projectname [CXX] [C] [Java])**

  ```
  # 指定工程名为HELLOWORLD
  project(HELLOWORLD)
  ```

- $set$ - **显式的定义变量**

  - 语法: **set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])**

  ```
  # 定义SRC变量，其值为sayhello.cpp hellp.cpp
  set(SRC sayhello.cpp hello.cpp)
  ```

- $include\ directories$ **- 想工程添加多个特定的头文件搜索路径** ---> 相当于指定g++编译器的-I参数

  - 语法: **include_directories([AFTER | BEFORE] [SYSTEM] dir1 dir2 ...)**

  ```
  # 将/usr/include/myincludefolder和./include 添加到头文件搜索路径
  include_directories(/usr/include/myincludefolder ./include)
  ```

- $link\_directories$ **- 想工程添加多个特定的库文件搜索路径** ---> 相当于指定g++编译器的-L参数

  - 语法: **link_directories(/usr/lib/mylibfolder ./lib)**

  ```
  # 将/usr/lib/mylibfolder 和 ./lib 添加到库文件搜索路径
  link_directories(/usr/lib/mylibfolder ./lib)
  ```

- $add\_library$ **- 生成库文件**

  - 语法: **add_library(libname [SHARED | STATIC | MODULE] [EXCLUDE_FROM_ALL] source1 source2 ... sourceN**

  ```
  # 通过变量SRC生成libhello.so共享库
  add_library(hello SHARED ${SRC})
  ```

- $add\_compile\_options$ **- 添加编译参数**

  - 语法: **add_compile_options(<option> ...)**

  ```
  # 添加编译参数 -Wall -std=c++11
  add_compile_options(-Wall -std=c++11 -O2)
  ```

- $add\_executable$ **- 生成可执行文件**

  - 语法: **add_executable(exename source1 source2 ... sourceN)**

  ```
  # 编译main.cpp生成可执行文件main
  add_executable(main main.cpp)
  ```

- $target\_link\_libraries$ **- 为target添加需要链接的共享库** ---> 相同于指定g++编译器-l参数

  - 语法: **target_link_libraries(target library1<debug | optimized> library2 ...)**

  ```
  # 将hello动态库文件链接到可执行文件main
  target_link_libraries(main hello)
  ```

- $add\_subdirectory$ **- 向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置**

  - 语法: **add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])*

  ```
  # 添加src子目录，src中需有一个CMakeLists.txt
  add_subdirectory(src)
  ```

- $aux\_source\_directory$ **- 发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表**

  - 语法: **aux_source_directory(dir VARIABLE)**

  ```
  # 定义SRC变量，其值为当前目录下所有的源代码文件
  aux_source_directory(. SRC)
  # 编译SRC变量所代表的源代码文件，生成main可执行文件
  add_executable(main ${SRC})
  ```

#### 4.3.2 $CMake$常用变量

- $CMAKE\_C\_FLAGS$	**gcc编译选项**

- $CMAKE\_CXX\_FLAGS$ **g++编译选项**

  ```
  # 在CMAKE_CXX_FLAGS编译选项后追加-std=c++11
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  ```

- $CMAKE\_BUILD\_TYPE$  **编译类型(Debug, Release)**

  ```
  # 设定编译类型为debug，调试时需要选择debug
  set(CMAKE_BUILD_TYPE Debug)
  # 设定编译类型为release，发布时需要选择release
  set(CMAKE_BUILD_TYPE Release)
  ```

- $CMAKE\_BINARY\_DIR$

  $PROJECT\_BINARY\_DIR$

  <projectname>**_BINARY_DIR**

  > 1. 这三个变量指代的内容是一致的
  > 2. 如果是in source build，指的就是工程顶层目录
  > 3. 如果是out-of-source编译，指的是工程编译发生的目录
  > 4. PROJECT_BINARY_DIR跟其他指令稍有区别，不过现在，你可以理解为他们是一致的。

- $CMAKE\_SOURCE\_DIR$

  $PROJECT\_SOURCE\_DIR$

  <projectname>**_SOURCE_DIR**

  > 1. 这三个变量指代的内容是一致的，不论采用何种编译方式都是工程顶层目录
  > 2. 也就是在in source buld时，他跟CMAKE_BINARY_DIR等变量一致
  > 3. PROJECT_SOURCE_DIR跟其他指令稍有区别，现在，你可以理解为他们是一致的。

- $CMAKE\_C\_COMPILER$**: 指定C编译器**
- $CMAKE\_CXX\_COMPILER$**: 指定C++编译器**
- $EXECUTABLE\_OUTPUT\_PATH$**: 可执行文件输出的存放路径**
- $LIBRARY\_OUTPUT\_PATH$**: 库文件输出的存放路径**

### 4.4 $CMake$编译工程

$CMake$目录结构: 项目主目录存在一个$CMakeLists.txt$

**两种方式设置编译规则: **

1. 包含源文件的子文件夹**包含**CMakeLists.txt文件，主目录的CMakeLists.txt通过add_subdirectory添加自目录即可。
2. 包含源文件的子文件夹**未包含**CMakeLists.txt文件，子目录编译规则体现在主目录的CMakeLists.txt中。

####  4.4.1 编译流程

**在linux平台下使用CMake构建C/C++工程的流程如下:**

- 手动编写$CMakeLists.txt$
- 执行命令**cmake PATH**生成$Makefile$(PATH是顶层CMakeLists.txt所在的目录)
- 执行命令**make**进行编译

```
# important tips
.			# 表示当前目录
./		# 表示当前目录

..		# 表示上级目录
../		# 表示上级目录
```

#### 4.4.2 两种构建方式

- **内部构建(in-source build):** 不推荐使用

  内部构建会在同级目录下产生一大堆中间文件，这些中间文件并不是我们最终所需要的，和工程源文件放在一起会显得杂乱无章

  ```
  ## 内部构建
  
  # 在当前目录下，编译本目录的CMakeLists.txt，生成Makefile和其他文件
  cmake
  # 执行make命令，生成target
  make
  ```

- **外部构建(out-of-source build):** 推荐使用

  将编译输出文件与源文件放到不同目录中

  ```
  ## 外部构建
  
  # 1. 在当前目录下，创建build文件夹
  mkdir build
  # 2. 进入到build文件夹
  cd build
  # 3. 编译上级目录的CMakeLists.txt，生成Makefile和其他文件
  cmake ..
  # 4. 执行make命令，生成target
  make
  ```

  
