
1. 启动supervisord 

```
supervisord -c ./supervisord.conf
```

2. 查看进程状态

```
supervisorctl -c ./supervisord.conf status
```

3. 停止进程

```
supervisorctl -c ./supervisord.conf stop test
```

4. 启动进程

```
supervisorctl -c ./supervisord.conf start test
```
