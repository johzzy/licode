licode 测试笔记

0. 官方示例
```
./scripts/initLicode.sh             // 启动 licode 
./scripts/initBasicExamples.sh      // 启动 example
```

1. 运行
```
ROOT=$ROOT
BUILD_DIR=$ROOT/build
sudo rabbitmq-server > $BUILD_DIR/rabbit.log &
# 1
cd $ROOT/nuve/nuveAPI
node nuve.js 
# 2
cd $ROOT/erizo_controller/erizoController
node erizoController.js
# 3
cd $ROOT/erizo_controller/erizoAgent
#node erizoAgent.js $* &
#node erizoAgent.js # 有问题
export NVM_DIR=$ROOT/build/libdeps/nvm
. $ROOT/build/libdeps/nvm/nvm.sh
$ROOT/build/libdeps/nvm/versions/node/v12.13.0/bin/node erizoAgent.js
node erizoAgent.js
# 4
cd $ROOT/extras/basic_example
node basicServer.js
```

2. 编译
```
## 首次编译
./scripts/installMacDeps.sh

## 常规执行
./scripts/installNuve.sh
./scripts/installErizo.sh # 报错修复详见 `报错处理`
./scripts/installBasicExample.sh

## 启动
### 首次启动 
./scripts/initLicode.sh 

### 常规启动
node nuve/nuveAPI/nuve.js
node erizo_controller/erizoController/erizoController.js
node erizo_controller/erizoAgent/erizoAgent.js

### web 客户端
node extras/basic_example/basicServer.js

## 退出
killall node


############### 内部细节
## release
cd $ROOT/erizo/build/release 
cmake ../../src -DERIZO_BUILD_TYPE=release
## debug
cd $ROOT/erizo/build/debug 
cmake ../../src -DERIZO_BUILD_TYPE=debug
cmake --build .
## script
./scripts/installErizo.sh -e
./scripts/installErizo.sh -a
## node gyp
export ERIZO_HOME=$ROOT/erizo
cd $ROOT/erizoAPI
npm install --unsafe-perm

```

3. 移除 $ROOT/build/libdeps/nvm
```
# 1. install erizo
source ~/Workspace/hello/ExportEnvironmentVariable python
./scripts/installErizo.sh
# 2. install nuve
source ~/Workspace/hello/ExportEnvironmentVariable mongo
./scripts/installNuve.sh
# 3. 分别运行 nuve.js erizoController.js erizoAgent.js basicServer.js
node nuve/nuveAPI/nuve.js
node erizo_controller/erizoController/erizoController.js
node erizo_controller/erizoAgent/erizoAgent.js
node extras/basic_example/basicServer.js
#配置文件见 licode_config.js
```

4. VIOP-9, Pass packets to RR and NACK Generator
```
RtcpFeedbackGenerationHandler::read

```

5. 报错处理

clion 配置: 
    
    ./scripts/installErizo.sh 调用 generateProject.sh 和 buildProject.sh 

    其等价于编译 licode/erizo/src/CMakeLists.txt, 生成路径为 licode/erizo/build/debug 和 licode/erizo/build/release

编译报错:

    编译报错 error: no member named 'url' in 'AVFormatContext'
    注释 scripts/installMacDeps.sh 中 install_mediadeps/install_mediadeps_nogpl 函数 关于 libav 的安装

