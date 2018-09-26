### 下载地址: http://valgrind.org/downloads/current.html#current
### 安装：
	cd valgrind-3.2.3
	./autogen.sh
	./configure
	make
	sudo make install
### 介绍
> Valgrind支持很多工具:memcheck，addrcheck，cachegrind，Massif，helgrind和Callgrind等。在运行Valgrind时，你必须指明想用的工具,如果省略工具名，默认运行memcheck.
----------
#### 1、memcheck
> memcheck探测程序中内存管理存在的问题。它检查所有对内存的读/写操作，并截取所有的malloc/new/free/delete调用。因此memcheck工具能够探测到以下问题：
- 使用未初始化的内存
- 读/写已经被释放的内存
- 读/写内存越界
- 读/写不恰当的内存栈空间
- 内存泄漏
- 使用malloc/new/new[]和free/delete/delete[]不匹配。
- src和dst的重叠
---------
#### 2、cachegrind
> cachegrind是一个cache剖析器。它模拟执行CPU中的L1, D1和L2 cache，因此它能很精确的指出代码中的cache未命中。如果你需要，它可以打印出cache未命中的次数，内存引用和发生cache未命中的每一行代码，每一个函数，每一个模块和整个程序的摘要。如果你要求更细致的信息，它可以打印出每一行机器码的未命中次数。
---------
#### 3、helgrind
> helgrind查找多线程程序中的竞争数据。helgrind查找内存地址，那些被多于一条线程访问的内存地址，但是没有使用一致的锁就会被查出。这表示这些地址在多线程间访问的时候没有进行同步，很可能会引起很难查找的时序问题。
> 它主要用来检查多线程程序中出现的竞争问题。Helgrind 寻找内存中被多个线程访问，而又没有一贯加锁的区域，这些区域往往是线程之间失去同步的地方，而且会导致难以发掘的错误。Helgrind实现了名为”Eraser” 的竞争检测算法，并做了进一步改进，减少了报告错误的次数。
---------
#### 4、Callgrind
> Callgrind收集程序运行时的一些数据，函数调用关系等信息，还可以有选择地进行cache 模拟。在运行结束时，它会把分析数据写入一个文件。callgrind_annotate可以把这个文件的内容转化成可读的形式。
> 一般用法:
	valgrind --tool=callgrind ./sec_infod
> 会在当前目录下生成callgrind.out.[pid], 如果我们想结束程序, 可以
	killall callgrind
> 然后我们可以用
	callgrind_annotate --auto=yes callgrind.out.[pid] > log
	vi log
----------
#### 5、Massif
> 堆栈分析器，它能测量程序在堆栈中使用了多少内存，告诉我们堆块，堆管理块和栈的大小。Massif能帮助我们减少内存的使用，在带有虚拟内存的现代系统中，它还能够加速我们程序的运行，减少程序停留在交换区中的几率。
----------
#### 6、lackey
> lackey是一个示例程序，以其为模版可以创建你自己的工具。在程序结束后，它打印出一些基本的关于程序执行统计数据。

### 用法
	valgrind [options] prog-and-args [options]
> --tool=<name>
- 最常用的选项。运行 valgrind中名为toolname的工具。默认memcheck。
> -h --help
- 显示所有选项的帮助，包括内核和选定的工具两者。
> --version
- 显示valgrind内核的版本，每个工具都有各自的版本。
> -q --quiet
- 安静地运行，只打印错误信息。
> --verbose
- 更详细的信息。
> -trace-children=<yes|no>
- 跟踪子线程? [default: no]
> --track-fds=<yes|no>
- 跟踪打开的文件描述？[default: no]
> --time-stamp=<yes|no>
- 增加时间戳到LOG信息? [default: no]
> --log-fd=<number>
- 输出LOG到描述符文件 [2=stderr]
> --log-file=<file>
- 将输出的信息写入到filename.PID的文件里，PID是运行程序的进行ID
> --log-file-exactly=<file>
- 输出LOG信息到 file
> --xml=yes
- 将信息以xml格式输出，只有memcheck可用
> --num-callers=<number>
- show <number> callers in stack traces [12]
> --error-exitcode=<number>
- 如果发现错误则返回错误代码 [0=disable]
> --db-attach=<yes|no>
- 当出现错误，valgrind会自动启动调试器gdb。[default: no]
> --db-command=<command>
- 启动调试器的命令行选项[gdb -nw %f %p]
#### 适用于Memcheck工具的相关选项：
> --leak-check=<no|summary|full>
- 要求对leak给出详细信息? Leak是指，存在一块没有被引用的内存空间，或没有被释放的内存空间，如summary，只反馈一些总结信息，告诉你有多少个malloc，多少个free 等；如果是full将输出所有的leaks，也就是定位到某一个malloc/free。 [default: summary]

### 例子
- 编写存在内存泄露的程序main.c
	#include <stdio.h>
	int main()
	{
		int x;
		if(x == 0)
		{
			printf("X is zero");
		}
		return 0;
	}
- 并编译
	gcc -g main.c -o main
- 运行Valgrind
	valgrind --tool=memcheck ./sample

### link
- https://www.cnblogs.com/napoleon_liu/articles/2001802.html
- http://valgrind.org/docs/manual/manual.html
