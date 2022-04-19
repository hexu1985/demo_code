#### workflow使用简介

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

将需要执行脚本或可执行程序,放到workflow/stepXX下(可根据需要创建stepXX子目录)

每次workflow触发时, 会依次遍历stepXX子目录, 处理完step01下的所有可执行程序后, 才会继续遍历出路step02, 以此类推.
