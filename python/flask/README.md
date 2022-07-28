flask 1.1.1 doc: <https://flask.net.cn/>
flask latest doc: <https://dormousehole.readthedocs.io/en/latest/index.html>


### 安装 virtualenv

```
$ sudo apt install python3-venv
```

### 创建一个虚拟环境

创建一个项目文件夹，然后创建一个虚拟环境。创建完成后项目文件夹中会有一个 venv 文件夹：

```
$ mkdir myproject
$ cd myproject
$ python3 -m venv venv
```

### 激活一个虚拟环境

```shell
$ python3 -m venv venv
$ source venv/bin/activate
$ pip install -r requirements.txt
```
新开发package, 在根目录下新建文件夹做开发


### 安装 Flask

在已激活的虚拟环境中可以使用如下命令安装 Flask：

```
$ pip install Flask
```

### Run

```shell
python main.py
```

### 退出虚拟环境

```
(venv) $ deactivate
```


### Python虚拟环境和requirements.txt文件的使用

可以执行之后，把你的依赖包写入requirements.txt，执行命令:
```
(venv) $ pip freeze > requirements.txt
```

打开requirements.txt ，也可以查看你的依赖包。

如果确实你的依赖包，请检查。
如果是导出少了，可以手动添加，否则不要手动添加未使用的包，以免增添累赘。

然后可以通过pip install -r安装requirements.txt指定的依赖. 具体的

```
(venv) $ pip install -r requirements.txt
```

