# 使用C++对Linux下Tcp进行简单封装


### 功能综述

对Tcp连接以及Event进行简单封装，方便使用，引入线程池，利用回调函数机制实现reactor架构

### 使用

1. 初始化Acceptor对象，传入ip以及port，然后初始化Eventloop对象，传入刚才生成的Acceptor对象
2. 设置回调函数
3. 提供了测试类，g++编译 

```
cd bin
g++ *.cc -o main -lpthread
```

#### 示例
bin目录下test.cc
