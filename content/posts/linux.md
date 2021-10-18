+++
title = "linux"
date = 2021-10-18T20:30:00+08:00
lastmod = 2021-10-18T21:18:59+08:00
tags = ["linux"]
categories = ["system"]
draft = false
+++

linux常用命令&&工具

<!--more-->


## 查看系统信息 {#查看系统信息}


### 查看库 (动态库, 静态库)的封装信息 {#查看库--动态库-静态库--的封装信息}

readelf
nm
objdump


### fd {#fd}

查询

1.  所有进程允许打开的最大fd数量。查询语句：

    ```text
    /proc/sys/fs/file-max
    ```
2.  所有进程已经打开的fd数量及允许的最大数量。查询语句：

    ```text
    /proc/sys/fs/file-nr
    ```
3.  单个进程允许打开的最大fd数量.查询语句：

    ```text
    ulimit -n
    ```
4.  单个进程（例如进程id为5454）已经打开的fd.查询语句：

    ```text
    ls -l /proc/5454/fd/
    ```


### socket {#socket}

命令: ss
socket Statistics -- socket统计信息
比netstat 更快


## 必备命令(软件) {#必备命令--软件}


### watch {#watch}

周期性的执行某个命令

```text
watch ss -s
```