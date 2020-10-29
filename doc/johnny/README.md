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
#release
cd $ROOT/erizo/build/release 
cmake ../../src -DERIZO_BUILD_TYPE=release
#debug
cd $ROOT/erizo/build/debug 
cmake ../../src -DERIZO_BUILD_TYPE=debug
cmake --build .
#script
./scripts/installErizo.sh -e
./scripts/installErizo.sh -a
#node gyp
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

