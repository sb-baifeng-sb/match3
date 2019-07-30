# 说明

#### 介绍
基于entity-component-system(ECS)模式实现的宝石三消例子。

#### 使用说明

1. git clone https://github.com/sb-baifeng-sb/match3.git
2. brew install cmake (Linux: sudo apt install cmake)
3. brew install sfml (Linux: sudo apt install libsfml-dev)
4. cd match3
5. sh init.sh (首次运行时需要使用)
6. sh build.sh
7. sh run.sh

#### 其他

如果已经安装了cmake可以跳过第2步

如果想要重新编译项目，使用 sh build.sh -clean

目前已知的问题：宝石下落系统比较脆弱，随着游戏的过程中，会出现画面出错和崩溃，不过这不影响这个项目作为一个ECS模式的源码范例。

<img src="./screenshot.jpg" width="50%">