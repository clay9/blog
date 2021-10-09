+++
title = "github"
date = 2021-09-23T21:43:00+08:00
lastmod = 2021-10-09T18:32:38+08:00
tags = ["github"]
categories = ["tool"]
draft = false
+++

github记录

<!--more-->


## github {#github}

Github 本身提供了多种认证方式，所有开发人员可以各取所需。

SSH，这是最原始的方式，如果使用git bash只要按照官方文档一步一步配置就好了
小心坑：SSH有可能需要配置代理，否则无法解析服务器域名。错误如下：
ssh: Could not resolve hostname github.com: no address associated with name
解决办法：给SSH以及git 客户端配置代理。
HTTPS，这也是比较方便的方式，但是每一次都需要输入用户名和密码。
小心坑：本机的SSL证书不是正规机构颁发的，验证失败。错误如下：
fatal: unable to access 'https://github.com/owner/repo.git/': SSL certificate problem: unable to get local issuer certificate

解决办法：将Git的SSL验证关闭，命令如下。
 git config --global http.sslVerify false
Access Token，我个人认为最为便捷的方式之一，不失安全性。
<https://help.github.com/articles/creating-an-access-token-for-command-line-use/>
使用方法：
1)从Settings页面生成唯一的Token

1.  手动拼接出远程仓库的地址，比如：<https://%24GH%5FTOKEN@github.com/owner/repo.git>

3）从以上地址克隆或使用git remote add 的方式关联本地仓库，之后都不需要输入用户名和密码信息


## github action {#github-action}

1.  qygame v1.0版本
    版本信息的描述: x.y.z
    x -- 对外接口改变时, 刷新
    y -- 增加功能时, 刷新
    z -- fix bug等 刷新
    1.  [X] tag 对应关系
        保证repository 及其依赖的repository  及其生成的deploy之间 保持相同的tag
        比如
        frame

        -   publish/server-kernel
        -   proto
        -   publsih/server-frame

        之间tag应该完全相同

    2.  [X] workflow 中编译的时候拉取对应的tag依赖仓库
        比如 frame tag1.0的仓库 应该拉取 publish/server-kernel中tag1.0的仓库编译
    3.  workflow 中如果依赖的仓库的tag还不存在, 应该等待直至其完成后(或github action时间到了), 才进行后续的动作
    4.  [X] frame的 workflow中 当触发tag的时候, 应该判断对应的submodule的tag是否一致, 如果不一致, 应该重新打tag(workflow中处理)
        并重新触发tag流程
2.  [X] frame的 workflow中 当触发tag的时候, 应该判断对应的submodule的tag是否一致, 如果不一致, 应该重新打tag(workflow中处理)
    并重新触发tag流程

    ```text
    更新了tag, 也push到原仓库了
    更新tag之后, 没必要退出当前workflow, 用更新后的tag重新走流程, 因为更新后的tag不会触发workflow, 所以直接使用旧tag的commit走
    workflow即可
    ```
3.  [X] server-subgames
    1.  workflow的编写
    2.  add server-frame deploy => submodule
4.  [X] my\_delete.sh脚本的编写
5.  publish 分支说明
    publish repository\_name分支主要是供依赖者获取使用，目标是repository
    publish tag分支则是供运维人员使用


## workflow -- hugo {#workflow-hugo}

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


## workflow -- server-kernel {#workflow-server-kernel}

name: build-kernel

on:
  push:
    branches:

-   master  # Set a branch to deploy

jobs:
  build:
    runs-on: ubuntu-20.04
    steps:

-   uses: actions/checkout@v2
-   name: step 1 test

run: echo "step 1"

shell: bash

-   name: step 2 make
    run: make

<!--listend-->

-   name: step 3 deploy

    run: echo "step 3"

    shell: bash