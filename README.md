# grpcMonitor
基于分布式架构的linxu性能分析监控系统，为了能够实时的监控多台服务器的cpu状态，软中断，系统负载，内存和网络等性能指标。提供qt实现的UI界面，可以直观展示监控到的数据。

配置：
1.构建项目镜像
下载好之后，进入到docker/build目录下执行
docker build --network host -f base.dockerfile .

2.命令镜像id
tag后面的标签，是下载号镜像后的镜像id
docker tag 10ba4324da04 linux:monitor

3.启动容器
进入到docker/build/scripts目录下，有两个可以自动编译的脚本
#启动容器
./monitor_docker_run.sh 
#进入容器
./monitor_docker_into.sh

4.编译代码
进入容器之后，进入到/work/cmake目录下
cd /work
cd cmake
cmake .. 据父目录中的 CMakeLists.txt 文件生成构建系统（例如 Makefiles）
make -j8 使用 8 个并行任务（-j8）来加速构建过程


5.实际运行
  5.1启动rpc服务器
  进入/work/build/rpc_manager/server,执行./server
  5.2启动监控服务
  进入/work/build/test_monitor/src，执行那个./monitor
  5.3启动UI界面
  进入/work/build/display_monitor，执行./display
