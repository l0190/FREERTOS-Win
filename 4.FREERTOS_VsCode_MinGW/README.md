# freeRTOS 系统win-运行

## freeRTOS

### 方式1： winmm
- CMakeLists 添加 target_link_libraries(${PROJECT_NAME} C:/Windows/System32/winmm.dll)
  - 或者 target_link_libraries(${PROJECT_NAME} winmm.dll)
- 一版在  C:/Windows/System32/ 都有预装 winmm.dll

### 方式2 pThread （还未实现）
- 安装 pthreads-w32-2-7-0-release.exe


## mavlink
- 使用：配置好xml 文件，通过工具可自动生成对应的 c文件
- 发送心跳包，以及信息，打印出来； qgc 绑定的udp端口是 14550，飞控自己随机一个端口就行

### UDP 接受数据
- 纵横也是通过使用  recvfrom 来接受 udp数据的，然后就可以进行数据解析了
```c

      leng=recvfrom(socketFdin, 
          (char *)(&rcvPacket), 
          sizeof(SIM_MSG_PACKET),
          0,
          (struct sockaddr *)&from, 
          pFromLen);
```