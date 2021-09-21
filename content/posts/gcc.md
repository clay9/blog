+++
title = "gcc"
date = 2021-08-28T00:53:00+08:00
lastmod = 2021-09-21T23:15:09+08:00
tags = ["gcc"]
categories = ["gnu"]
draft = false
+++

gcc

<!--more-->


## 安装 {#安装}


## 配置 {#配置}


### gcc {#gcc}

1.  查看搜索路径
    g++ | gcc -print-serach-dirs (可通过--help查看)
2.  头文件搜索路径
    gcc  C\_INCLUDE\_PATH
    g++  CPLUS\_INCLUDE\_PATH

    ep: export CPLUS\_INCLUDE\_PATH=/usr/lib/
    <span class="underline">扩展1</span>

    1.  输出 echo $C\_INCLUDE\_PATH
    2.  调用 $C\_INCLUDE\_PATH
    3.  赋值 export C\_INCLUDE\_PATH
    4.  删除变量 unset C\_INCLUDE\_PATH
    5.  C++调用 string strValue(getenv("C\_INCLUDE\_PATH")
3.  库文件搜索路径
    1.  动态链接库搜索路径
        LD\_LIBRARY\_PATH
    2.  静态链接库搜索路径
        LIBRARY\_PATH


## 使用 {#使用}