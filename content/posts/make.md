+++
title = "make"
date = 2021-09-23T22:27:00+08:00
lastmod = 2021-10-09T18:32:36+08:00
tags = ["make"]
categories = ["gnu"]
draft = false
+++

make记录

<!--more-->


## 常用 {#常用}

make
make clean
make install -- 编译成功的文件安装到系统目录

make dist 产生发布软件包文件（即distribution package

```text
这个命令将会将可执行文件及相关文件打包成一个tar.gz压缩的文件用来作为发布软件的软件包。
它会在当前目录下生成一个名字类似“PACKAGE-VERSION.tar.gz”的文件
PACKAGE和VERSION，是我们在configure.in中定义的AM_INIT_AUTOMAKE(PACKAGE, VERSION)
```

make distcheck

```text
生成发布软件包并对其进行测试检查，以确定发布包的正确性
这个操作将自动把压缩包文件解开，然后执行configure命令，并且执行make，来确认编译不出现错误
最后提示你软件包已经准备好，可以发布了
```


## make {#make}

1.  -j num  同时启动多少个jobs一起编译, 一般为系统内核数的2倍
2.  make打印信息 不显示目录

    ```text
    make --no-print-directory
    ```
3.  make打印信息优化

    ```text
    SHOW_COMPILE=@echo -e "\033[36mCompling \033[35m==> \033[33m$<\033[0m"
    SHOW_LINK=@echo -e "\033[31mLINKING \033[35m==> \033[33m$(EXEFILE)\033[0m"
    SHOW_DEBUG_BUILD=@echo -e "\033[31mBuilding Debug...\033[0m"
    SHOW_RELEASE_BUILD=@echo -e "\033[31mBuilding Release...\033[0m"
    ```
4.  makefile 中的 "+ - @"
    实际为shell中的规则, 不是makefile中的

    | 符号 | 作用                    |
    |----|-----------------------|
    | @  | 使命令被执行前不回显    |
    | -  | 使任何命令行的非0退出状态都被忽略 |
    | +  | 使命令行可以通过制定-n -q或-t选项来执行 |
5.  内置函数 patsubst
     格式：$(patsubst <pattern>,<replacement>,<text> )
     名称：模式字符串替换函数——patsubst。
     功能：查找<text>中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式<pattern>，如果匹配的话，则以<replacement>替换。
     　　　这里，<pattern>可以包括通配符“%”，表示任意长度的字串。如果<replacement>中也包含“%”，那么，<replacement>中的这个“%”将是<pattern>中的那个“%”所代表的字串。
    　　　（可以用“\\”来转义，以“\\%”来表示真实含义的“%”字符）
     返回：函数返回被替换过后的字符串。

    示例：
    $(patsubst %.c,%.o, a.c b.c)
    把字串“a.c b.c”符合模式[%.c]的单词替换成[%.o]，返回结果是“a.o b.o”
6.  $@ $^ $ $< $?
    $@  表示目标文件
    $^  表示所有的依赖文件
    $<  表示第一个依赖文件
    $?  表示比目标还要新的依赖文件列表
7.  gcc编译过程
    预处理 -E  .cpp -> .i
    汇编   -S  .i   -> .s
    编译   -c  .s   -> .o

    -o 仅仅是输出目标的file\_name, 不一定是连接后的file\_name, 比如

    ```text
    gcc -S hello.i -o hello.s
    ```

    gcc 不带参数可以 跟随.cpp .i .s .o类型的文件, 会自动执行预处理, 汇编, 编译, 连接的动作
    所以连接不需要指定参数
8.  [ ] wildcard
    Makefile规则中，通配符会被自动展开。但在变量的定义和函数引用时，通配符将失效。
    这种情况下如果需要通配符有效，就需要使用函数“wildcard”，它的用法是：$(wildcard PATTERN...) 。
    在Makefile中，它被展开为已经存在的、使用空格分开的、匹配此模式的所有文件列表。
    如果不存在任何符合此模式的文件，函数会忽略模式字符并返回空。
    需要注意的是：这种情况下规则中通配符的展开和上一小节匹配通配符的区别。

9.  makefile只能在taget的地方调用shell, 其他地方无效

    ```text
    其他地方调用需要使用 $(shell cmd)
    ```