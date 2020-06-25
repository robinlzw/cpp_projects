# alphaquant

======================================================================

说明：

本SDK仅供参考学习，方便自动化下单，使用请遵守相关国家法规，不配资，不操纵股价。

======================================================================

安装部署：

系统需求：Windows或Linux系统或Mac，python2或python3

下载后解压缩即可，不需要安装运行券商交易客户端

Windows命令行运行stock_live_trade.exe

Linux或Mac系统命令行运行 wine stock_live_trade.exe，Linux和Mac系统需安装wine，可在命令行参数指定监听端口，例： stock_live_trade.exe 0.0.0.0 58888

命令行运行pip install thrift

将alpha_live_trade.py和alpha_trade目录拷贝到自己源代码目录，import alpha_live_trade即可使用

解压目录下的example目录中是例子代码，推荐使用pycharm编辑调试代码

API文档: http://www.alpha-qt.com/?page_id=175
 
QQ交流群：575874566

stock_live_trade.exe编译说明：
vs2015及以上，需要thrift，libevent，boost，zlib，openssl

=============================================================================

模拟盘使用说明

1 模拟盘不需要开启stock_live_trade.exe进程

2 有两种方法可使用python接口

  ● 使用实盘api，调用任何其他API先调用：SetServer("sim.bbbstock.com",  62228)
  
  ● 下载bbbstock_sim_trade.py在代码中 import bbbstock_sim_trade
  
3 请到http://www.bbbstock.com 注册账号，该合作伙伴目前还在起步阶段，有使用问题或建议请在qq群反馈，我们会转达。
