# 简介
    ESP32 Drive层适配，依赖于ESP-IDF底层库；

# 目录结构
    驱动层 -> Drive（inc / src / doc）其中Drive层主要放置与硬件强相关的底层代码，并对底层逻辑进行封装，保证可靠性和普适性的同时，兼容AUTOSAR标准；
    封装层 -> Wrapper（inc / src / CmakeLists）Wrapper层主要是对Drive层的二次封装，是平台Platform与底层的主要交互层；之所以对Drive层进行在封装，是为了以后Drive层如果使用Vector工具配置生层（不同芯片原厂提供的MCAL源码不一定完全兼容），通过Wrapper封装可以更快的适配Platform，减少平台层和应用层的不兼容变更；

# 支持模块
## I2C模块
