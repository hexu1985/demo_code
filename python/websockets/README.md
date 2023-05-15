### virtualenv安装websockets并指定python版本

以ubuntu18.04上安装python3.9为例

更新软件包列表并安装必备组件：

```
$ sudo apt update
$ sudo apt install software-properties-common
```

将Deadsnakes PPA添加到系统的源列表中：

```
$ sudo add-apt-repository ppa:deadsnakes/ppa
```

出现提示时，按[Enter]以继续。

启用存储库后，您可以通过执行以下命令安装Python 3.9：

```
$ sudo apt install python3.9
$ sudo apt install python3.9-dev
```
通过键入以下命令验证安装是否成功

```
$ python3.9 --version
```
输出(视安装版本而定)：

3.9.13

如果要使用虚拟环境的话, 需要安装

```
$ sudo apt install python3.9-venv
```

创建虚拟环境

```
$ python3.9 -m venv venv
```

激活虚拟环境
```
$ source venv/bin/activate
(venv) $ pip install websockets --trusted-host pypi.douban.com
```

退出虚拟环境

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


