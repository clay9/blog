+++
title = "make"
date = 2021-09-23T22:27:00+08:00
lastmod = 2021-09-30T22:50:24+08:00
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