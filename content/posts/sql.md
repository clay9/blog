+++
title = "数据库开发"
date = 2021-08-28T15:17:00+08:00
lastmod = 2021-09-20T23:31:30+08:00
categories = ["protocol"]
draft = false
+++

数据库开发

<!--more-->


## 数据库开发 {#数据库开发}


### win下 {#win下}

[详细解释](https://www.bbsmax.com/A/kjdwDq7wzN/)

1.  原生接口
2.  ODBC
3.  OLE
4.  ADO


### linux下 {#linux下}

1.  原生接口
2.  ODBC


## sqlserver {#sqlserver}


### 优缺点 {#优缺点}


### Docker安装sqlserver {#docker安装sqlserver}

[官方文档](https://docs.microsoft.com/zh-cn/sql/linux/quickstart-install-connect-docker?view=sql-server-2017&pivots=cs1-bash)

1.  搜索镜像
    docker search mssql
2.  安装镜像(这个是官网的)
    docker pull microsoft/mssql-server-linux
3.  运行镜像, 创建容器
    docker run -e "ACCEPT\_EULA=Y" -e "SA\_PASSWORD=hack@2020" -p 9988:1433 --name mssql -d microsoft/mssql-server-linux

    注: 如果不指定映射的端口, 则可能随机使用一个端口
        密码必须8位数, 否则会创建失败
        -p 第一个参数为主机端口, 第二参数为docker容器端口
4.  进入容器
    docker exec -it mssql bash
5.  测试sql server命令
    /opt/mssql-tools/bin/sqlcmd -S localhost -U SA -P "passwd"
6.  如果启动失败
    docker logs mssql 查看日志信息


### sqlcmd用法 {#sqlcmd用法}

1.  登录

    ```text
    /opt/mssql-tools/bin/sqlcmd -S 127.0.0.1 -U SA -P "hack@2020"
    ```
2.  执行语句查询

    ```text
    select * from sys.databeses
    go
    ```

    一定记得使用go


### unicode支持 {#unicode支持}

```text
排序规则会影响字符集
```

-   服务器 排序规则
-   数据库 排序规则
-   表中的字段 排序规则

<!--listend-->

1.  排序规则会影响字符集, 比如排序规则为xx\_UTF8, 那么其默认的字符集为unicode
2.  nchar nvarchar类型会无视排序规则, 直接把改字段变为unicode编码

    ```text
    使用的时候 记得加N, exp:  N'排序规则'
    ```


### client 与 server {#client-与-server}

最理想的状态

1.  server 是 unicode编码(只要nchar, nvarchar即可)
2.  client 是 unicode编码
3.  unixodbc 编译的时候, 添加了 utf8的支持

    ```text
    ./configure --enable-iconv=yes --with-iconv-char-enc=UTF-8
    ```

总结:
数据库表字段的编码,
服务器程序运行环境的编码,
unixodbc编译时候的字符编码
三者需要统一, 这样写入数据库的时候 才不会乱码

```text
服务器运行环境 locale可以查看
locale -a显示系统支持的字符集
```


### 遇到的奇怪的问题 && 解决思路 {#遇到的奇怪的问题-and-and-解决思路}

简述: 通过odbc 操作sqlserver, 插入中文错误
现象:

1.  读取sqlserver中文正常
2.  插入sqlserver中文乱码

思路:

1.  查看sqlserver 的编码集(排序规则)
2.  查看qy-server的运行环境

    ```text
    locale
    ```
3.  编译unixodbc的时候是否加入了编码的支持
4.  查看odbc的配置文件

    ```text
    odbcinst -j
    这次的问题在于 odb的配置文件中 有重名的DSN
    ```


## mysql {#mysql}

优点:
缺点:

1.  没有存储过程


## ODBC {#odbc}

1.  安装odbc驱动

    ```text
    建议使用官方源码安装 http://www.unixodbc.org
    ```

    下载源码之后

    ```text
    ./configure --enable-gui=no --enable-iconv=yes --with-iconv-char-enc=UTF-8
    ./configure --enable-gui=no --enable-iconv=yes --with-iconv-char-enc=GB18030
    这里需要添加中文支持, 不然会发生数据库读取中文正常, 写入中文时候乱码
    ```
2.  安装对应的sql的驱动

    ```text
    这里sql的驱动是 odbc下的sql驱动
    ```

    以mssql为例
    下载并安装
3.  查看sql的驱动信息

    ```text
    debin在 /usr/local/etc/odbcinst.ini
    ```

    ```text
    [ODBC Driver 17 for SQL Server]
    Description=Microsoft ODBC Driver 17 for SQL Server
    Driver=/opt/microsoft/msodbcsql17/lib64/libmsodbcsql-17.6.so.1.1
    UsageCount=1
    ```

    说明sql的驱动安装成功
4.  编写DSN

    ```text
    debin在 /usr/local/etc/odbc.ini
    ```

    ```text
    [MssqlDB]
    Driver = ODBC Driver 17 for SQL Server
    Server = tcp:172.16.238.10,1433
    ```
5.  测试连接

    ```text
    isql MssqlDB user_name user_passwd -v
    ```

    如果连接成功

    ```text
    +---------------------------------------+
    | Connected!                            |
    |                                       |
    | sql-statement                         |
    | help [tablename]                      |
    | quit                                  |
    |                                       |
    +---------------------------------------+
    ```


## 常用数据库语句 {#常用数据库语句}

```text
sql server
```

1.  查询sql版本

    ```text
    select @@version
    go
    ```

2.  查询支持的字符集

    ```text
    只有2019版本 才支付utf-8字符集
    ```

    ```text
    select * from ::fn_helpcollations()
    go
    ```

    查询当前系统的排序规则

    ```text
    SELECT SERVERPROPERTY('Collation')
    ```

    查询排序规则的字符集

    ```text
    SELECT COLLATIONPROPERTY('Chinese_PRC_Stroke_CI_AI_KS_WS', 'CodePage')
    ```

    ```text
    936 简体中文GBK
    950 繁体中文BIG5
    437 美国/加拿大英语
    932 日文
    949 韩文
    866 俄文
    65001 unicode UFT-8
    ```

3.  查询所有的库

    ```text
    select * from sys.databeses order by name
    go
    ```

    有时候显示的数据太多, 我们可以只显示需要的比如

    ```text
    select name from sys.databeses order by name
    go
    ```
4.  查询当前数据库所有表
    1.  方法一

        ```text
        select * from sys.objects where type='U'
        go
        ```

        --XType='U':表示所有用户表;
        --XType='S':表示所有系统表;
    2.  方法二

        ```text
        select * from sys.tables
        go
        ```
5.  查询表中所有的字段
    SELECT \* FROM SysColumns WHERE id=Object\_Id('TableName');

SELECT COLLATIONPROPERTY('Chinese\_PRC\_CS\_AS\_WS', 'CodePage')

SELECT COLLATIONPROPERTY('Chinese\_PRC\_90\_CI\_AS\_SC\_UTF8', 'CodePage')
SELECT COLLATIONPROPERTY('Latin1\_General\_100\_CI\_AI\_SC\_UTF8', 'CodePage')
SELECT COLLATIONPROPERTY('SQL\_Latin1\_General\_CP1\_CI\_AS', 'CodePage')
SELECT COLLATIONPROPERTY('Chinese\_Simplified\_Stroke\_Order\_100\_CI\_AI', 'CodePage')