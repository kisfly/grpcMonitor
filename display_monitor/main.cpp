#pragma once

#include <QApplication>
#include <thread>
#include "client/rpc_client.h"
#include "monitor_widget.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  //要监视的服务器地址
  std::string server_address = "localhost:50051";
  if (argc > 1) {
    server_address = argv[1];
  }

  monitor::MonitorWidget moitor_widget;
  //初始化rcp客户端
  monitor::RpcClient rpc_client(server_address);
  monitor::proto::MonitorInfo monitor_info;

  //先从服务器获取要监视电脑的信息
  rpc_client.GetMonitorInfo(&monitor_info);
  std::string name = monitor_info.name();

  //获取要显示的窗体对象
  QWidget* widget = moitor_widget.ShowAllMonitorWidget(name);
  //显示
  widget->show();

  std::unique_ptr<std::thread> thread_;
  thread_ = std::make_unique<std::thread>([&]() {
    while (true) {
      monitor_info.Clear();
      //从服务端获取信息
      rpc_client.GetMonitorInfo(&monitor_info);
      //更新显示
      moitor_widget.UpdateData(monitor_info);
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  });
  thread_->detach();

  return app.exec();
}