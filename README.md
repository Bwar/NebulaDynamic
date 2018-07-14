# NebulaDynamic

&emsp;&emsp;Nebula框架动态加载，NebulaDynamic项目下所有第一层子目录都可编译成动态库，编译后
的动态库拷贝到NebulaBootstrap的plugins插件目录下，修改NebulaBootstrap/conf的任
意一个基于Nebula的Server配置文件，启动对应Server即可完成动态加载。Server运行时不能直接替换
动态库，否则会引起进程coredump，这是由于程序运行时的正在使用的代码空间被改变所致，详细原因
这里不解释。若要运行时动态加载，需先卸载动态库，再完成so文件替换，然后重新加载动态库。动态
配置中的"load"和"version"就是做这个用途，Nebula的早期版本提供了卸载动态库再重新加载功能，后
因动态库加载后创建了大量实例，卸载过程容易产生残留，要解决这个问题的工程量比较大，Nebula暂时
去掉了卸载动态库功能。

&emsp;&emsp;动态库的加载配置可以参考[NebulaLogic.json]()配置文件。

``` json
    "dynamic_loading":[
      {
        "so_path":"plugins/logic/Hello.so", "load":true, "version":1,
        "cmd":[
            {"cmd":65531, "class":"logic::CmdHello"}
        ],
        "module":[
        ]
      }
    ],
```

&emsp;&emsp;配置文件中的"dynamic_loading"即动态库加载配置。其中：
* so_pat    动态库相对于NebulaBootstrap根路径的相对路径。
* load      是否动态加载，配置为false则不会被加载。
* version   动态库版本。
* cmd       动态库中包含并需要在动态库加载时创建的Cmd类。
  - cmd     Cmd类对应的命令字。
  - class   Cmd类的类名（需带上名字空间），用于通过反射机制从类名创建类实例。
* module    动态库中包含并需要在动态库加载时创建的Module类。

&emsp;&emsp;动态库加载不成功的原因通常是so_path路径配置错误或路径下动态库不存在。

