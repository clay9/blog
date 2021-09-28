+++
title = "nginx"
date = 2021-08-28T15:20:00+08:00
lastmod = 2021-09-28T17:51:20+08:00
tags = ["nginx"]
categories = ["tool"]
draft = false
+++

nginx是使用率最高的web容器

<!--more-->


## 安装 {#安装}

```text
docker pull nginx
```

```text
docker run --name nginx-test -p 8080:80 -d nginx
```


## 配置 {#配置}

配置文件在/etc/nginx

/etc/nginx/nginx.conf是总的, 默认不修改
/etc/nginx/config.d/\* 下的是配置的, 一般一个文件配置一个站点


## 使用 {#使用}