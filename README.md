# 说明

#### 介绍
基于entity-component-system(ECS)模式实现的宝石三消例子。

#### 使用说明

1. git clone https://github.com/sb-baifeng-sb/match3.git
2. brew install cmake (Linux: sudo apt install cmake)
3. brew install sfml (Linux: sudo apt install libsfml-dev)
4. sh init.sh (首次运行时需要使用)
5. sh build.sh
6. sh run.sh

#### 其他

如果已经安装了cmake可以跳过第2步

如果想要重新编译项目，使用 sh build.sh -clean

目前已知的问题：如果玩家消除的太快，会引发宝石下落系统出错引起崩溃和一些看起来很奇怪的问题，解决方案<操作慢点就好了>。

