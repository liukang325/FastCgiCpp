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
        location / {
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

编译测试代码：g++ -o mainTest.cgi mainTest.cpp -lfcgi 

编译生成mainTest.cgi后，运行spawn

spawn-fcgi -a 127.0.0.1 -p 8080 -f ./mainTest.cgi


**SQL依赖库安装**

sqlite3: sudo apt-get install libsqlite3-dev

mysql:  sudo apt-get install libmysqlclient-dev