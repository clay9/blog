+++
title = "glog"
date = 2021-10-09T09:36:00+08:00
lastmod = 2021-10-18T21:19:01+08:00
tags = ["glog"]
categories = ["tool"]
draft = false
+++

glog是google开发的日志库

<!--more-->


## 功能 {#功能}


## 安装 {#安装}


## 配置 {#配置}


## 使用 {#使用}

1.  LOG\_IF(INFO, condition)
2.  LOG\_EVERY\_N(INFO, 20)
    每20次 打印一次
3.  LOG\_IF\_EVERY\_N(INFO, condition, 20)
    符合条件下, 每20次打印一次
4.  LOG\_FIRST\_N(INFO, 20)
    只打印前20次
5.  LOG\_EVERY\_T(INFO, 2.35)
    每2.35s打印一次


## 记录 {#记录}

1.  glog
    参考文档 \_https://zhuanlan.zhihu.com/p/26025722
    1.  severity levels
        INFO, WARNING, ERROR, FATAL
    2.  setting flags
        1.  in file
            You can also modify flag values in your program by modifying global variables FLAGS\_\* . Most settings start working immediately after you update FLAGS\_\*
        2.  when run
            If the Google gflags library isn’t installed, you set flags via environment variables, prefixing the flag name with GLOG\_, e.g.,
            GLOG\_logtostderr=1 ./your\_application
    3.  Debug mode
    4.  conditional logging
    5.  check macros
    6.  VLOG -- yourself-macro
    7.  Custom Log Prefix Format
    8.  Automatically remove old logs