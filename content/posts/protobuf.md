+++
title = "protobuf"
date = 2021-08-28T15:14:00+08:00
lastmod = 2021-10-18T21:18:57+08:00
categories = ["language"]
draft = false
+++

protobuf使用

<!--more-->


## 安装 {#安装}


## 使用 {#使用}


## 语法 {#语法}


### repeated {#repeated}


## protobuf cmake生成命令 {#protobuf-cmake生成命令}

cmake -G "Visual Studio 16 2019" -A Win32 -DCMAKE\_INSTALL\_PREFIX=../../../../../install ../.. -Dprotobuf\_BUILD\_TESTS=OFF -Dprotobuf\_BUILD\_SHARED\_LIBS=ON
cmake -G "Visual Studio 16 2019" -A Win32 -DCMAKE\_INSTALL\_PREFIX=../../../../../install ../.. -Dprotobuf\_BUILD\_TESTS=OFF

cmake -G "Visual Studio 16 2019" -A Win32 -DCMAKE\_INSTALL\_PREFIX=../install ../cmake -Dprotobuf\_BUILD\_TESTS=OFF -Dprotobuf\_BUILD\_SHARED\_LIBS=ON


## F&Q {#f-and-q}

1.  问: 编译的时候提示找不到定义

    ```text
    // 告诉编译器, 运行时候再找定义
    // 在xx.pb.h中加入如下宏定义
    #define PROTOBUF_USE_DLLS
    ```