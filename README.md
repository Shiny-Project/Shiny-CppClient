# SHINY C++ CLIENT SDK

这是Shiny的一个C++版客户端，用于从Shiny服务端接收推送。

目前仅在win10+msvc14.1上通过测试，其他系统和编译器未经测试。如有问题，请提issue。

## 安装准备

1. CMake（最新版）
2. Boost（Win请去下[pre-built](https://sourceforge.net/projects/boost/files/boost-binaries/)，其他系统我相信你们会自己搞定哒！）
3. [Socket.io C++ Client](https://github.com/socketio/socket.io-client-cpp/releases) （下Release版本，最新master源码有坑）
4. [腾讯神器（划掉）RapidJSON](https://github.com/Tencent/rapidjson/releases)
5. [WebSocket++](https://github.com/zaphoyd/websocketpp/releases)
6. [OpenSSL-devel](https://slproweb.com/products/Win32OpenSSL.html) （请下载64位，非light的开发者用版本，非Windows用户你可以自己找到的，一般也就是`apt install openssl-dev`一下）（Optional，如果你需要https/wss则需要这个库）

Socket.io C++ Clinet里面的lib目录里两个子目录是空的，简单的把下载好的RapidJSON和WebSocket++解压后直接放进去就行了。注意目录名不要带版本号。

以下两个文件能找到就说明你放置正确：
```bash
./lib/rapidjson/include/rapidjson/document.h
./lib/websocketpp/websocketpp/client.hpp
```

这两个库都是Header Only的，所以不需要编译。

## 编译前你需要知道的坑

1. WebSocket++的SSL版本用了一个最新版OpenSSL已经停用了的宏，[这导致如果你用的OpenSSL比较新，就会编译失败](https://github.com/zaphoyd/websocketpp/issues/599)。可以参考[这个补丁](https://github.com/aYasukiIkeuchi/websocketpp/commit/7c2e2ec25f10d86ae8f45cff0131f4f74f1ddb38)对代码进行相应修改来回避这个问题。
2. Socket.io C++ Client 的CMakeLists的INSTALL目标过于清真。这导致了在Windows下使用VS的时候，不管你是编译Debug还是编译Release，编译出的库都会放置在`./build/lib/Release`（或Debug）下面。这会造成当你需要从Debug切换到Release时，Socket.io C++ Client也要重新编译。

## 预编译

首先预编译 Socket.io C++ Client：

给CMake设置两个STRING型的ENTRY：
```bash
BOOST_ROOT=<your boost install path// eg. C:/local/boost_1_65_1>
BOOST_VER=<your boost version // eg. 1.65.1>
```

然后Configure两次、Generate、Open Project，编译INSTALL目标

（非Windows用户：`cmake -DBOOST_ROOT:STRING=<your boost install path> -DBOOST_VER:STRING=<your boost version> ./`。然后`make install`）

## 编译与安装

给CMake设置一个STRING型的ENTRY：
```bash
SIO_DIR=<your socket.io c++ client path>
```
此变量是 Socket.io C++ Client的根目录。

如果你需要开启SSL，需要再设置一个BOOL型的ENTRY:
```
ENABLE_SSL=ON
```
然后Configure两次、Generate、Open Project，编译INSTALL目标

编译之后你应该得到的：

```bash
./bin/shiny_cpp_client_sdk.lib  # -----静态库文件
./include # -----include 目录
```

## 使用

你可以参考test.cpp是如何调用这个库的。别忘了在你的编译器选项里加入include和lib

## LICENSE

MIT