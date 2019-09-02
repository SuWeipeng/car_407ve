![](https://github.com/SuWeipeng/img/raw/master/13_car/car_10.jpg)<br>
软件介绍
---
> 使用STM32F407VE单片机。<br>
> 软件高度可移植，原则上各个软件模块 STM32 全系列通用(只要有足够目标模块使用的Flash和RAM既可)。

1. 【编程语言】使用 C/C++ 混合编程；
2. 【无线通信】使用 Mavlink 通信协议；
3. 【控制算法】使用 ardupilot 的 AC_PID 库算法对每个轮进行 PID 控制；
4. 【运动算法】按 Mecanum 轮运动学对 4 个麦轮进行动力分配；
5. 【TO DO】使用 rt-thread 实时操作系统进行线程调度；
6. 【TO DO】使用 ardupilot 日志形式记录软件运行的实时数据。

教程推文
---
> 欢迎关注微信公众号：MultiMCU EDU<br>
> ![](https://github.com/SuWeipeng/img/raw/master/17_wechat/08cm.jpg)

1. [马达驱动](https://mp.weixin.qq.com/s/7Bk-xQbymZaez4g5sUALxw)
2. [物联网通信，如何应用 mavlink 通信协议](https://mp.weixin.qq.com/s/K92U5lO0KGM4mUzyGSXvcg)
3. [让车听遥控的话](https://mp.weixin.qq.com/s/h7FURP4kGNTJmfsHatk-4A)
4. [看完这篇一定能会用 ab 相编码器](https://mp.weixin.qq.com/s/aUa0sHmGF6CbPej6O9IzKQ)
5. [PID 调参](https://mp.weixin.qq.com/s/TO926HglAhvM9RNe-2kJuQ)

