+++
title = "hexo搭建blog"
date = 2021-08-28T15:20:00+08:00
lastmod = 2021-09-20T20:12:44+08:00
tags = ["hexo"]
categories = ["tool"]
draft = false
+++

使用hexo + org-mode + github搭建blog

<!--more-->


## 为什么要用hexo {#为什么要用hexo}

说hexo之前, 必须先说blog. blog作用有下:

-   利己, 整理自身知识体系 或作记录
-   利人, 分享的精神

blog好处很多, 却也增加了使用者的难度, 比如要理解html等. 同时, 外在的表现(CSS等)往往会导致bloger的重心偏差, 去追求外在的东西.

我们需要一个能让我们专注于文章知识本身, 而无需去关心外在或其他知识的工具, 来帮助我们搭建自己的blog.

当下, 一个不错的选择就是hexo.

hexo不拘束我们的文章语言(markdown, org等), 自动将语言转化为html, 并且提供不错的外观. 使我们可以专注文章本身.


## hexo是什么 {#hexo是什么}

如上所言, hexo是一款不错的blog框架

hexo的主要优点:

-   不限制前端语言
-   自动化生成html
-   丰富便捷的themes
-   统一干净的包管理npm
-   部署简单, 集成方便
-   迅速上手, 学习时间短

hexo的缺点:

-   环境无法移植
    在A pc上搭建的环境, 只能在A pc上发布blog


## hexo怎么使用 {#hexo怎么使用}


### hexo安装 {#hexo安装}

[详细点此查看官网](https://hexo.io)

1.  安装 [Node.js](https://nodejs.org/en/), 获得npm包管理工具
2.  安装 [Git](https://git-scm.com)
3.  安装 Hexo

    ```text
    $ npm install -g hexo-cli
    ```

    至此, hexo已完成安装
4.  安装[hexo-renderer-org](https://github.com/coldnew/hexo-renderer-org)
    这里是org-mode与hexo的结合使用, 非官方的markdown.

    根据[hexo-renderer-org官方文档](https://coldnew.github.io/hexo-org-example/2017/03/05/getting-started-with-hexo-and-org-mode/)一步步操作即可, 具体不详解. 唯一注意的点是:

    -   Emacs line的版本要 >= 24
    -   org-mode的版本最好 >= 9.0
    -   使用的分支是coldnew, 而不是master或emacs!


### hexo创建blog {#hexo创建blog}

[详情点此查看](https://hexo.io)

1.  创建并初始化blog目录

    ```text
    mkdir blog
    cd blog
    hexo init
    ```

注意事项:
hexo命令(例如hexo g) 应该在 hexo init所在目录下使用(上面中是blog目录)


### hexo配置 {#hexo配置}

1.  [基本配置](https://hexo.io/zh-cn/docs/configuration)
    1.  Site

        ```text
        ## 标题
        title:
        ## 副标题
        subtitle:
        ## SEO优化
        description:
        keywords
        ## 作者
        author:
        ## 语言
        language: zh-Hans
        ```
    2.  URL

        ```text
        ## 访问地址
        url: https://clay9.github.io/
        ## root地址
        root: /
        ```
    3.  Deployment

        ```text
        ## 仓库地址
        deploy: https://github.com/clay9/clay9.github.io.git
        ## 仓库协议类型
        type: git
        ```
    4.  org

        ```text
        ## emacs path, 使用bash环境
        emacs:
        ## emacsclient path
        emacclinet:
        ```
    5.  Extensions

        ```text
        ## 主题
        theme: next
        ```

2.  [主题配置:next](http://theme-next.iissnan.com/getting-started.html)
    1.  scheme

        ```text
        scheme: Mist
        ```


### hexo使用 {#hexo使用}


#### 文件链接 {#文件链接}

hexo-renderer-org支持使用org-mode的文件链接方式.
但是有一定的限制.

如果要发布的org文件的名字为A.org. 那么:

1.  A.org中链接的文件必须放在A目录下, 且A目录与A.org同级.
2.  A.org中链接文件格式为:

    ```text
    file:A/文件名字
    ```


### hexo部署 {#hexo部署}

hexo支持多渠道发布, [具体看官网](https://hexo.io/zh-cn/docs/deployment), 这里只说发布到github


#### hexo处理 {#hexo处理}

1.  安装 hexo-deployer-git

    ```text
    $ npm install hexo-deployer-git --save
    ```
2.  修改blog/\_config.yml

    ```text
    deploy:
       type: git
       repo: <repository url>
       branch: [branch]
    ```


#### github处理 {#github处理}

1.  新建项目, 名字为: [YourName].github.io

    至此github方面完成


#### 测试 {#测试}

1.  生成并部署到github上

    ```text
    hexo g -d
    ```
2.  在web中打开[Yourname].github.io, 查看是否可以显示


## hexo高级用法 {#hexo高级用法}


### 自定义域名 {#自定义域名}

实现可以通过wcq.fun 与 www.wcq.fun均可访问


#### hexo配置 {#hexo配置}

blog/source目录下新增CNAME文件, 其内容为域名, 比如

```text
wcq.fun
```


#### 域名服务商配置 {#域名服务商配置}

1.  [wcq.fun绑定教程](https://help.github.com/articles/using-a-custom-domain-with-github-pages/)
2.  [www.wcq.fun绑定教程](https://help.github.com/articles/using-a-custom-domain-with-github-pages/)


### 鼠标点击小心心效果 {#鼠标点击小心心效果}

1.  在themes/next/source/js/src/下新建love.js文件
    并且[copy下面的代码](hexo/love.txt)到love.js中
2.  在themes/next/layout/\_layout.swig末尾添加以下代码:

    ```text
    <!-- 页面点击小红心 -->
    <script type="text/javascript" src="/js/src/love.js"></script>
    ```


### next主题安装第三方插件 {#next主题安装第三方插件}


#### 搜索 {#搜索}

这里使用的是[local search](http://theme-next.iissnan.com/third-party-services.html#local-search)