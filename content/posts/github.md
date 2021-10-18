+++
title = "github"
date = 2021-09-23T21:43:00+08:00
lastmod = 2021-10-18T21:19:00+08:00
tags = ["github"]
categories = ["tool"]
draft = false
+++

github记录

<!--more-->


## github 认证方式 {#github-认证方式}

Github 本身提供了多种认证方式，所有开发人员可以各取所需。

1.  SSH，这是最原始的方式，如果使用git bash只要按照官方文档一步一步配置就好了
    小心坑：SSH有可能需要配置代理，否则无法解析服务器域名。错误如下：
    ssh: Could not resolve hostname github.com: no address associated with name
    解决办法：给SSH以及git 客户端配置代理。
2.  HTTPS，这也是比较方便的方式，但是每一次都需要输入用户名和密码。
    小心坑：本机的SSL证书不是正规机构颁发的，验证失败。错误如下：
    fatal: unable to access 'https://github.com/owner/repo.git/': SSL certificate problem: unable to get local issuer certificate

    解决办法：将Git的SSL验证关闭，命令如下。
    git config --global http.sslVerify false
3.  Access Token，我个人认为最为便捷的方式之一，不失安全性。
    <https://help.github.com/articles/creating-an-access-token-for-command-line-use/>
    使用方法：

    1.  从Settings页面生成唯一的Token
    2.  手动拼接出远程仓库的地址，比如：<https://%24GH%5FTOKEN@github.com/owner/repo.git>

    3）从以上地址克隆或使用git remote add 的方式关联本地仓库，之后都不需要输入用户名和密码信息


## github action实例解析 -- hugo {#github-action实例解析-hugo}

```text
workflow中所有缩进必须是空格, 不能是tab
```

name: github page

on:

push:
  branches:

-   master  # Set a branch to deploy

pull\_request:

jobs:

deploy:

runs-on: ubuntu-20.04

steps:

-   uses: actions/checkout@v2
    with:
      submodules: true  # Fetch Hugo themes (true OR recursive)
      fetch-depth: 0    # Fetch all history for .GitInfo and .Lastmod

<!--listend-->

-   name: Setup Hugo

    uses: peaceiris/actions-hugo@v2
    with:
      hugo-version: 'latest'

<!--listend-->

-   name: Build
    run: hugo --minify

<!--listend-->

-   name: Deploy
    uses: peaceiris/actions-gh-pages@v3

    if: github.ref == 'refs/heads/master'

    with:
      github\_token: ${{ secrets.HUGO\_PUBLISH\_TOKEN }}
      publish\_dir: ./public


## github action实例解析 -- qygame调用docker {#github-action实例解析-qygame调用docker}

name: 'make for qygame'
autho: wcq
description: 'make for qygame'

inputs:

qygame\_token:

description: 'Set a generated GITHUB\_TOKEN for pushing to the remote branch.'

required: true

runs:

using: 'docker'

image: 'Dockerfile'