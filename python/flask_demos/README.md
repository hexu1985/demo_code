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

#### Run

```shell
python main.py
```

