+++
title = "php"
date = 2021-08-28T15:13:00+08:00
lastmod = 2021-09-20T23:36:43+08:00
categories = ["language"]
draft = false
+++

php && php框架

<!--more-->


## 说明 {#说明}

php是web后端常用的开发语言
有cli和fpm版本, cli版本暂时不知道什么用,
fpm版本可以供其他软件使用, 比如apache2, nginx


## 安装 {#安装}

强烈推荐使用docker安装php

```text
docker install php:7.4.7-fpm
```


## laravel {#laravel}

[中文翻译文档](https://learnku.com/docs/laravel/7.x)
[官方文档](https://laravel.com)

laravel是流行的php框架

```text
唯一感触就是环境配置真麻烦
```

laravel与hexo非常类似, 都是通过命令生成一个项目.
不同的是laravel需要把很多信息打入到php所在的载体中(docker容器或者服务器)(在compose install的时候打入).
而hexo则是通过命令, 把源文件生成为静态文件, 静态文件可以被github-page等服务器识别, 供web解析


### laravel安装adminLTE -- 通过mix方式安装 {#laravel安装adminlte-通过mix方式安装}

```text
laravel7.x 安装adminlte2.4
```

1.  下载adminLTE到工程中

    ```text
    composer require "almasaeed2010/adminlte=~2.4"
    ```
2.  编写app.scss &&  app.js && webpack.mix.js  TODONOW 如何编写
    app.scss路径 resources/sass/app.scss
    app.js路径 resources/js/app.js
    webpack.mix.js路径 在项目根目录下
3.  npm install && npm run dev

    ```text
    项目根目录下执行
    npm install 安装js依赖  (根据package.json来安装)
    npm run dev 把webpack.mix.js(类似工程项目)中内容编译
    ```
4.  xxx.blade.php代码中引用修改

    ```text
    css文件引用修改
    js文件引用修改
    ```

    ```text
    <!DOCTYPE html>
    <html>
    <head>
    .
    .
    .
       <link rel="stylesheet" href="{{ mix('css/app.css') }}">
    </head>

    <body class="hold-transition skin-blue sidebar-mini">
    .
    .
    .
      <script src="{{ mix('js/app.js') }}"></script>
    </body>
    </html>
    ```


### laravel安装adminLTE -- 直接放到public目录下面即可 {#laravel安装adminlte-直接放到public目录下面即可}

1.  把adminLTE代码(github下载的源码) 放到laravel项目的pulic目录中
2.  修改项目中对adminLTE的引用路径

    ```text
    <!-- Font Awesome -->
    <link rel="stylesheet" href="adminlte/plugins/fontawesome-free/css/all.min.css">
    <!-- icheck bootstrap -->
    <link rel="stylesheet" href="adminlte/plugins/icheck-bootstrap/icheck-bootstrap.min.css">
    <!-- Theme style -->
    <link rel="stylesheet" href="adminlte/dist/css/adminlte.min.css">
    ```

    注意路径的起始位置为laravel项目的public
3.  重启php 与 nginx!!!!!

    ```text
    需要重启才能生效
    ```


### laravel学习 {#laravel学习}

/project path/app目录 逻辑代码(后端代码)

```text
app目录下的Http中放的是我们需要的 逻辑代码
app/Http中 controlers与middleware交互是通过app/Http/kernel.php中的变量map来寻找的
```

/project path/resources/views 前端代码(表现层代码)

```text
模板文件一般放在layouts目录下面
```


#### 访问DB数据库 {#访问db数据库}

注意事项

1.  修改config/database.php

    ```text
    吐槽 database.php中sql server的demo不正确
    ```

    配置为

    ```text
    'sqltest' => [
         'driver' => 'sqlsrv',
         //'url' => env('DATABASE_URL'),
         'host' => '172.22.0.4',
         'port' => '1433',
         'database' =>'QPAccountsDB',
         'username' => 'sa',
         'password' => 'hack@2020',
         'charset' => 'utf8',
         'prefix' => '',
         'prefix_indexes' => true,
     ],
    ```
2.  提示 修改了database.php后 需要执行以下命令

    ```text
    提示错误为
    ```

    ```text
    php artisan config:cache
    ```

    成功了会显示

    ```text
    Configuration cache cleared!
    Configuration cached successfully!
    ```
3.  提示错误  There is no existing directory at "%s" and its not buildable
    1.  查看storage权限 是否为775
    2.  执行以下命令

        ```text
        php artisan route:clear   &&
        php artisan config:clear &&
        php artisan cache:clear
        ```
4.  查看php是否开启了对DB的支持(这里以mssql为例)
    详见本文档的 支持mssql && sqlserver
5.  数据库表的搭建
    1.  创建数据库 && 在app/User.php中选择数据库

        ```text
        protected $connection = 'QPWebDB';
        ```
    2.  在选择的数据库中创建table

        ```text
        php artisan migrate
        ```
6.  测试laravel的注册, 登录功能
    访问 0.0.0.0:8080  进行注册,登录测试


#### web站点访问流程 -- 以登录为例 {#web站点访问流程-以登录为例}

```text
controler 管理类
middleware 中间件
```

访问web站点
--> 通过/project path/routes/web.php中的路由找到controler -- /project path/app/Http/controler/HomeControler.php
--> controler转交给middleware处理 -- auth

```text
根据/project path/app/Http/kernel中的变量map找到middleware
如果有缓存, 则进入到home界面, 否则进入到login界面, 由controler中控制
```

--> middleware通过route找到view (route 与 view之间通过XXX.blade.php关联)
--> 显示view页面
--> 点击login页面中的登录按钮
--> view找到对应的对应的controlers -- /projectt path/app/Http/Controllers/Auth/LoginController.php

```text
根据Auth::routes()找到 TODONOW可以查看在哪里实现的该函数
```

--> controler转交给middleware处理 -- /projcet path/Http/Middleware/RedirectIfAuthenticated.php
--> middleware中继续往下传递


#### 总结 {#总结}

1.  laravel 可以分为下面几个模块
    route     -- 路由
    controler -- 管理器
    middleware-- 中间件
    view      -- 视图文件(前端显示)
    guard

    其架构为

    ```text

    		      +-----------+
    	      	      | controler | -----	     +------------+
    +----------+     /--> +-----------+      \---> |  middleware|
    |  route   | ----	       |    ^  	       	     +------------+
    +----------+ --	       v    |  	       	   ---
    	       \---   +------------+    ----/
    		   \> |   view     | <-/
    		      +------------+

    ```

    ```text
    route可以访问 controler 与view
    controler可以访问view,  或者把复杂逻辑交给middleware
    midlleware可以访问view
    view 可以把action提交给controler, 由controler管理
    ```


## compose {#compose}

compose 解决项目中对php的依赖

```text
mac系统下
```


### 安装 {#安装}

```text
# 安装compose
curl -sS https://getcomposer.org/installer | php
# 修改为全局可用
sudo mv composer.phar /usr/local/bin/composer
# 查看是否安装成功
composer --version
```


### 更新源 {#更新源}

```text
国外的源 被墙了
```

```text
# 修改为国内的源
composer config -g repo.packagist composer https://packagist.phpcomposer.com
```


## pear && pecl {#pear-and-and-pecl}

```text
实际中并未使用到 :)
```

pecl是php扩展池,
pear管理php自身扩展库, 可以在pecl中下载php扩展


## 使用 {#使用}

实际使用, 可以参考下面的
web服务器 + php + lavarel + 数据库
TODONOW 待补充连接


## 支持mssql && sqlserver {#支持mssql-and-and-sqlserver}

1.  下载odbc驱动

    ```text
    apt install unixodbc
    ```
2.  下载微软的 dobc for sql
    [微软官方下载地址](https://docs.microsoft.com/zh-cn/sql/connect/odbc/microsoft-odbc-driver-for-sql-server?view=sql-server-linux-2017)
    根据服务器和php选择下载 并安装

    ```text
    dpkg -i msodbcsql17_17.5.2.1-1_amd64.deb
    ```
3.  下载微软的 php for sql扩展
    [微软官方下载](https://docs.microsoft.com/zh-cn/sql/connect/php/microsoft-php-driver-for-sql-server?view=sql-server-linux-2017)
    并根据操作放入到php的lib目录, 同时修改php.ini
4.  重启php 与 web载体(nginx, apache2)
5.  测试是否安装成功
    [官方测试代码](https://docs.microsoft.com/zh-cn/sql/connect/php/installation-tutorial-linux-mac?view=sql-server-linux-2017#testing-your-installation)