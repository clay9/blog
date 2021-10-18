+++
title = "web框架搭建"
date = 2021-08-28T15:14:00+08:00
lastmod = 2021-10-18T21:18:58+08:00
categories = ["project"]
draft = false
+++

使用docker搭建web,
包含web服务器(nginx), php7.4.7, lavarel7.12.0, mssql

<!--more-->


## 基本信息 {#基本信息}

| 软件           | 版本          | 备注                   |
|--------------|-------------|----------------------|
| docker desktop | 2.0.0.3       | sdocker engine 18.09.2 |
| laravel        | 7.12.0        |                        |
| php            | php:7.4.7-fpm |                        |
| mssql          | 2017-CU13     |                        |


## 架构分析 {#架构分析}

```text
+-------------+	 +-------------+       	+--------------+
|  nginx      | -----> |  php        | ----->	|   mssql      |
|             |      	 |             |    	|              |
+-------------+      	 +-------------+    	+--------------+
  		       	  ^
 		       	  |
 	       	       	  | <---
		       	  |	  \------
       	       	       +--+-------+  	 \---+------------+
		       | laravel  |  	     | composer   |
		       |          |	     |            |
		       +----------+	     +------------+

```

```text
通过composer把laravel信息打入到php载体中(这里是docker容器)
在docker_compose中设置转移信息, 使nginx的信息交由php处理
开发环境需要laraverl && composer,  生产环境不需要
```


## 下载laravel && compose完成laravel的项目依赖 {#下载laravel-and-and-compose完成laravel的项目依赖}

1.  下载laravel

    ```text
    laravel对php有版本要求, 所以这里下载的是v7.12.0
    ```

    <https://github.com/laravel/laravel/releases/tag/v7.12.0>
2.  完成laravel的依赖安装

    ```text
    这里compose直接安装在了本地mac环境上, 没有装在docker容器中, 效果一样
    不知道为什么, 有些文件下载会失败, 建议多敲几次该命令
    ```

    ```text
    # 进入laravel项目目录, 并输入
    composer install
    ```


## 编写dockerfile && docker-compose.yml {#编写dockerfile-and-and-docker-compose-dot-yml}

[参考文档](https://learnku.com/laravel/t/38564)

```text
dockerfile 与 docker-compose.yml应该在laravel项目的根目录下, 因为后续有把laravel打入到php载体的操作
```

1.  docker-compose.yml

    ```text
     version: '2'
     services:

     # The Application  php-fpm
     app:
     # 这里通过app.dockerfile安装
     build:
        context: ./
        dockerfile: app.dockerfile
     working_dir: /var/www
     volumes:
    ​    - ./:/var/www
     environment:
    ​    - "DB_PORT=3306"
    ​    - "DB_HOST=database"

    # The Web Server
    web:
       build:
          context: ./
          dockerfile: web.dockerfile
       working_dir: /var/www
       # 这里表示继承app中的设定
       volumes_from:
    ​       - app
      ports:
    ​      - 8080:80

    # The Database
    database:
      image: mysql:5.6
      volumes:
    ​    - dbdata:/var/lib/mysql
      environment:
    ​    - "MYSQL_DATABASE=homestead"
    ​    - "MYSQL_USER=homestead"
    ​    - "MYSQL_PASSWORD=secret"
    ​    - "MYSQL_ROOT_PASSWORD=secret"
      ports:
    ​    - "33061:3306"
      volumes:
         dbdata:
    ```

2.  app.dockerfile

    ```text
    这里注释了php的扩展, 但仍然安装laravel成功了, 很奇怪
    ```

    ```text
    # php -- 使用特定7.4.7
    From php:7.4.7-fpm

    #RUN apt-get update && apt-get install -y libmcrypt-dev \
    #    mysql-client libmagickwand-dev --no-install-recommends \
    #     && docker-php-ext-install mcrypt pdo_mysql
    ```

3.  web.dockerfile

    ```text
    FROM nginx:1.10
    ADD vhost.conf /etc/nginx/conf.d/default.confx
    ```

4.  nginx config配置

    ```text
    server {
    listen 80;
    index index.php index.html;
    root /var/www/public;

    location / {
        try_files $uri /index.php?$args;
    }

    location ~ \.php$ {
       fastcgi_split_path_info ^(.+\.php)(/.+)$;
       # 这里表示把信息转移给app即php处理
       fastcgi_pass app:9000;
       fastcgi_index index.php;
       include fastcgi_params;
       fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
       fastcgi_param PATH_INFO $fastcgi_path_info;
      }
    }
    ```


## 安装docker-compose.yml中信息 {#安装docker-compose-dot-yml中信息}

```text
# 进入到docker-compose-yml的目录
docker-compose up
```


## laravel打入到php载体中 {#laravel打入到php载体中}

1.  laravel环境配置

    ```text
    # 进入到laravel的根目录
    mv .env.example .env
    ```
2.  应用程序密钥和优化

    ```text
    docker-compose exec app php artisan key:generate
    docker-compose exec app php artisan optimize
    ```


## 测试 {#测试}

访问<http://0.0.0.0:8080> 应该能看到laravel的标志


## 生产环境优化 {#生产环境优化}

可以把已经配置好的容器打包为镜像, 并保存为镜像文件.
这样生产环境搭建的时候, 就无需再配置环境(php载体的laravel环境),
同时生成环境可以通过镜像文件加载, 免除了网络问题卡下载的问题.


## 遗留问题 {#遗留问题}

1.  docker php容器映射问题
    如何把php容器的路径 映射出来
2.  生产环境 docker-compse.yml编写问题