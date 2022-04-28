### 基础组件:

#### uevent_monitor.cpp 

- 通过netlink, 监听Uevent事件, 将disk插拔(主要关心partition的add和remove action)事件上报(通过unix domain socket方式)
- 通过命令行参数指定接收端的unix domain路径, socket类型为数据报

#### uevent_publisher.py

- 将uevent_monitor作为子进程启动, 并接收uevent_montior的输出(通过unix domain socket方式)
- 实现在python中监听uevent事件, 并且通过向UeventPublisher注册observer方式感知uevent事件

#### shell_command_executor.py

- 在python中封装subprocess模块运行可执行程序, 将运行输出打印到logging中

#### worker_thread.py

- 封装命令模式, 通过putTask往worker线程里丢任务, worker线程会依次执行任务. task类要支持execute()函数


### workflow相关组件:

#### 基本概念

以下面的目录结构为例, workflow目录为工作流的top目录, step01目录和step02目录分别代表一个工作节点(WorkflowNode)
```
workflow
├── step01
│   ├── step01_test01.sh
│   ├── step01_test02.sh
│   └── test.txt
└── step02
    ├── step02_test01.sh
    ├── step02_test02.sh
    └── test.txt
```

#### workflow_node.py

- 实现工作流节点类WorkflowNode, 遍历对应的工作流节点目录(例如step01或step02), 执行目录中的可执行程序
- 例如创建WorkflowNode("workflow/step01"), 会遍历workflow/step01目录下的所有可执行程序, 并在调用run时执行各个可执行程序(并行执行)
- 依赖shell_command_executor.py

#### workflow_node_set.py

- 实现工作流类WorkflowNodeSet, 遍历对应的工作流目录(例如workflow), 创建工作流节点(根据子目录, 例如step01, step2), 依次执行各个工作流节点(工作流节点之间串行执行)
- 例如创建WorkflowNodeSet("workflow"), 会遍历workflow目录下的所有子目录, 例如step01和step02, 然后创建WorkflowNode("workflow/setp01")和WorkflowNode("workflow/setp02")工作流节点, 
- 各个工作流节点之间是串行的, 即执行完WorkflowNode("workflow/step01")后, 才会执行WorkflowNode("workflow/setp02"), 工作流节点之间的先后顺序按照子目录名的字典顺序来,
- 依赖workflow_node.py

#### workflow_service.py & main.py

- 实现工作流服务类WorkflowService, 监听uevent和SIGUSR1, 每种事件都会触发启动一次工作流任务(prework -> workflow -> postwork), 
- main.py中初始化日志workflow.service.log.*, 启动定时任务, 依赖python第三方库schedule

#### start_workflow_service.sh & stop_workflow_service.sh

- 启动停止workflow service脚本

#### start_workflow_service_monitor.sh & stop_workflow_service_monitor.sh & workflow.service

- start_workflow_service_monitor.sh: workflow启动及监控脚本, 
- stop_workflow_service_monitor.sh: workflow停止和停止监控脚本
- workflow.service: workflow service配置文件(cp到/lib/systemd/system/目录下)
    ```
    $ sudo systemctl daemon-reload
    $ sudo systemctl start workflow.service
    $ sudo systemctl enable workflow.service
    ```

#### clean_7day_ago_dir.py (prework/step01/)

- 清理"/gondor/yyyymmdd"目录, 保留7天内数据

#### sync_imgs_to_car.sh (postwork/step01/)

- 版本数据隔日自动上车: 二进制全量版本（main/map/calibration/model），隔日自动上车外接盘
- 源目录: /gondor/imgs/sync/
- 目的目录: /media/apollo/xxx/imgs/
- 同步方式: rsync -avP --delete
- 目的盘过滤条件: 存在white-rhino-xxx目录, 存在imgs目录

#### sync_data_from_car.py

- 同步车上数据和日志到边缘服务器
    ```
    同步流程:
    遍历mountpoint对应的目录:
        如果目录下存在white-rhino-*的目录,说明是车上的外接硬盘
        遍历每个white-rhino-*目录:
            把data目录下的bag, log目录和文件, 同步到/gondor/yyyymmdd/white-rhino-*/data目录下
    ```
