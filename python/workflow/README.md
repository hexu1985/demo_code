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
- 依赖workflow_node.py, worker_thread.py

