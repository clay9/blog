+++
title = "git"
date = 2021-08-28T15:12:00+08:00
lastmod = 2021-09-26T22:48:43+08:00
tags = ["git"]
categories = ["gnu"]
draft = false
+++

git简易指导, 个人使用心得

<!--more-->


## git使用流程 {#git使用流程}


## git原理 && 常见命令 {#git原理-and-and-常见命令}


## git高级特性 {#git高级特性}


### git hooks {#git-hooks}

[参考文档](https://blog.csdn.net/jessise%5Fzhan/article/details/80131618)


### 删除大文件 {#删除大文件}

1.  寻找大文件
    git rev-list --objects --all | grep "$(git verify-pack -v .git/objects/pack/\*.idx | sort -k 3 -n | tail -5 | awk '{print$1}')"
2.  删除大文件
    git filter-branch -f --prune-empty --index-filter 'git rm -rf --cached --ignore-unmatch your-file-name' --tag-name-filter cat -- --all
3.  删除之后
    git gc --prune=now


## git lfs {#git-lfs}

把大文件排除在git仓库之外, git仓库中只有一个指针指向该大文件


### 安装lfs {#安装lfs}

```text
curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash &&
sudo apt-get install git-lfs &&
git lfs install
```


### 初始化 {#初始化}

git lfs install


### 使用 {#使用}

1.  过滤大文件
    git lfs track file\_path
2.  过滤之后, 会生成.gitattributes
3.  提交到远端
    git push      -- 提交普通文件
    git lfs push  -- 提交lfs文件
4.  下载大文件
    git lfs clone url


## git submodule {#git-submodule}

参考文档 <https://www.cnblogs.com/nicksheng/p/6201711.html>

当项目越来越庞大之后，不可避免的要拆分成多个子模块，
我们希望各个子模块有独立的版本管理，并且由专门的人去维护，这时候我们就要用到git的submodule功能

```text
git clone <repository> --recursive 递归的方式克隆整个项目
git submodule add <repository> <path> 添加子模块
git submodule init 初始化子模块
git submodule update 更新子模块
git submodule foreach git pull 拉取所有子模块
```


### 拉取子模块 {#拉取子模块}

-   方法1
    1.  先clone父项目
    2.  git submodule init
    3.  git submodule update
-   方法2
    1.  clone 父项目时 加 --recursive
        git clone url path --recursive


## F&Q {#f-and-q}

1.  问: 命令行下的git status如何显示中文

    ```text
         答：git config --global core.quotepath false
    ```
2.  问：在命令行下(gnu-bash)中git不能补全git的命令

    ```text
    1) 首先获得源码 git clone git://git.kernel.org/pub/scm/git/git.git
    1) 从源码中拷贝git-completion.bash到用户主目录下. git-completion.bash
       cp git/contrib/completion/git-completion.bash ~/.git-completion.bash
    2) 在 .bashrc 中加入 source ~/.git-completion.bash
    3) 在shell下执行 . ~/.bashrc
    ```
3.  问: 如何取消对文件的跟踪

    ```text
    答: 分情况而定
    1) 对于从没有追踪过的文件, 只需要设置.gitignore即可
    2) 对于已经追踪过的文件, 需要git rm --cached (-r) file 然后再加入到.gitignoe中即可
    ```
4.  git对大小写不敏感问题, 可以通过下面命令修改

    ```text
    git config core.ignorecase false
    ```