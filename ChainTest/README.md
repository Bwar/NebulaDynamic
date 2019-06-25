#### 动态执行链示例

把此目录编译出来的ChainTest.so放的plugins目录下，配置由Interface节点加载。
将下面这段配置添加到NebulaInterface.json的dynamic_loading中
```json
        {
            "so_path":"plugins/ChainTest.so", "load":true, "version":1,
            "cmd":[
            ],
            "module":[
                {"path":"/chain_test", "class":"hello::ModuleChainTest"}
            ],
            "session":[],
            "step":[]
        }
```
同时将下面这段配置添加到NebulaInterface.json的runtime配置里。
```json
"runtime":{
        "chains":{
            "chain_1":["hello::StepOne", "hello::StepTwo", "hello::MatrixOne", "hello::MatrixTwo"],
            "chain_2":["hello::MatrixTwo",
                       ["hello::StepOne", "hello::StepTwo", "hello::StepOne"],
                       "hello::MatrixOne",
                       "hello::MatrixTwo"
            ],
            "chain_3":["hello::StepOne", "hello::MatrixTwo", "hello::StepTwo", "hello::MatrixOne"]
        }
```
chain_2的["hello::StepOne", "hello::StepTwo", "hello::StepOne"]为并行步骤，注意，并行步骤必须都为Step，不可以含有Matrix。

本测试需在NebulaLogic加载了Hello.so才能完成，因为StepOne和StepTwo两个步骤都是往LOGIC发送请求并得到LOGIC的响应后才完成。

配置完毕，启动NebulaInterface和NebulaLogic后，用以下命令分别测试：
```bash
curl -H "Content-Type:application/json" -X POST -d '{"chain_flag":"chain_1"}' http://${your_ip}:16003/chain_test
curl -H "Content-Type:application/json" -X POST -d '{"chain_flag":"chain_2"}' http://${your_ip}:16003/chain_test
curl -H "Content-Type:application/json" -X POST -d '{"chain_flag":"chain_3"}' http://${your_ip}:16003/chain_test
```
"chain_flag"的值为"runtime"配置中"chains"里的key。

chain_1的结果输出：
```json
[{
                "hello::StepOne:38":    "Nebula: hello!\n"
        }, {
                "hello::StepTwo:39":    "Nebula: hello!\n"
        }, {
                "hello::MatrixOne:13":  "is a matrix."
        }, {
                "hello::MatrixTwo:6":   "is a matrix."
        }]
```

chain_2的结果输出：
```json
[{
                "hello::MatrixTwo:6":   "is a matrix."
        }, {
                "hello::StepOne:44":    "Nebula: hello!\n"
        }, {
                "hello::StepTwo:45":    "Nebula: hello!\n"
        }, {
                "hello::StepOne:46":    "Nebula: hello!\n"
        }, {
                "hello::MatrixOne:13":  "is a matrix."
        }, {
                "hello::MatrixTwo:6":   "is a matrix."
        }]
```

chain_3的结果输出：
```json
[{
                "hello::StepOne:32":    "Nebula: hello!\n"
        }, {
                "hello::MatrixTwo:6":   "is a matrix."
        }, {
                "hello::StepTwo:33":    "Nebula: hello!\n"
        }, {
                "hello::MatrixOne:13":  "is a matrix."
        }]
```


