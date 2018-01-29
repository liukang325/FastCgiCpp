# FastCgiCpp

**1. 安装spawn-fcgi** （FastCGI进程管理器）

1. 获取spawn-fcgi编译安装包，在  http://redmine.lighttpd.net/projects/spawn-fcgi/wiki  上可以获取当前最新的版本。
2. 解压缩spawn-fcgi-1.6.4.tar.gz包。
3. 进入解压缩目录，执行./configure。
4. make & make install

**2. 安装fastcgi库**

sudo apt-get install libfcgi-dev

**3.修改Nginx的配置文件**

```
        location ~ .*\.(gif|jpg|jpeg|png|bmp|swf|css|js|woff|ttf|map|mp4)$ {
            root   /home/liukang/workspace/FastCgiCpp/html/example;
        }

        location / {
             index /index.fcgi;
             try_files $uri $uri/ /index.fcgi?$query_string;
        }

        location ~ \.fcgi$ {
            fastcgi_pass 127.0.0.1:8080;
            fastcgi_index index.fcgi;
            fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
            include fastcgi_params;
        }
```
重启nginx: sudo /usr/local/nginx/sbin/nginx -s reload


**4.测试代码编辑检查是否配置成功**


编译单线程测试代码：g++ -o mainTest.cgi mainTest.cpp -lfcgi 

编译生成mainTest.cgi后，运行spawn : spawn-fcgi -a 127.0.0.1 -p 8080 -f ./mainTest.cgi

编译多线程测试代码：g++ -o mainThreadTest.cgi mainThreadTest.cpp -lfcgi -lpthread

编译生成mainThreadTest.cgi后，运行spawn : spawn-fcgi -a 127.0.0.1 -p 8080 -f ./mainThreadTest.cgi


**5.SQL依赖库安装**

sqlite3: sudo apt-get install libsqlite3-dev

mysql:  sudo apt-get install libmysqlclient-dev


**6.boost依赖库安装 (websocketpp need)**

sudo apt-get install libboost-dev

sudo apt-get install libboost-all-dev


**7.编译**

创建 FastCgiCpp-build 文件夹，与FastCgiCpp同级目录

```
cd FastCgiCpp-build
cmake ../FastCgiCpp
make
```

在"执行CMake"这一步的参数中填入-DCMAKE_BUILD_TYPE=Debug 可以进行程序调试

在 FastCgiCpp-build/bin/ 目录下有生成的index.fcgi

```
cd FastCgiCpp-build/bin/
spawn-fcgi -a 127.0.0.1 -p 8080 -f ./index.fcgi
```


-------------------------


用到的第三方开源库：

jsoncpp: https://github.com/open-source-parsers/jsoncpp

websocketpp: https://github.com/zaphoyd/websocketpp

