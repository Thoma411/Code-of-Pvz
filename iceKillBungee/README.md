<!--
 * @Author: Thoma411
 * @Date: 2023-11-13 21:38:31
 * @LastEditTime: 2024-01-20 17:43:22
 * @Description: README & CHANGELOG . markdown
-->
# 简陋偷率测试器

## 简介

冰杀小偷(Ice Kill Bungee, IKB)，同底线矿工一样，分为理论计算(定性)与批量模拟(定量)。对于某一构型来说，前者只关心该构型是否可能被偷而不关心偷率大小；后者则侧重对实战情况的复现，通过海量模拟测出其偷率究竟几何。

## 使用方法

1. 在[Releases](https://github.com/Thoma411/Code-of-Pvz/releases/tag/IKB_v0.0.1)下载`IKB_240119.zip`并解压，保证以下运行必要文件在同一目录中:
    * `constVar.h`
    * `ialgo.h`
    * `interlayer.h`
    * `ialgo.cpp`
    * `interlayer.cpp`
    * `newExemple.cpp`
    * `run.bat`
2. 进入`newExemple.cpp`，可以仿照已有的几个`newTest()`自行编写测试用例，并修改相应代码段(含"TODO"注释的地方以及`main`函数中标记"!"注释的地方);
3. 确认无误后于cmd(同一目录下)键入`.\run.bat [测试次数(默认1M次)]`等待输出模拟结果.

## 注意事项

* 本品无意推广公开，不保证模拟结果的绝对准确$^{[注]}$，请务必合理使用;
* 本品仅适用于测单偷，不保证多偷结果的准确性;
* 截至目前(240119)，已有可模拟植物包括曾、喷、瓜、地刺类，剩余植物随缘更新；前述植物中瓜由于附带减速引起的一系列复杂情况超出了本人建模能力范围故暂时搁置，只能模拟绿瓜的情况，强行充当冰瓜将导致偷率一定程度地失真，望周知;
* 使用本品将默认您知晓上述说明。

注：一是事实上目前已知的某些模拟结果与前人所得结果存在一定出入(通常<1%)但原因不详；二是对计算过程中遇到的部分复杂情况做了适当转换与化简，因而不是全真模拟，亦不可轻信所得偷率完全合理，请理性看待之。

## 几点说明

* 定性分析基本上已于一月份整合完毕(说基本上是因为当时的表只算了下限没算上限)，目前在忙里偷闲更新的定量测试实际上价值更高一点
* 原理和底线矿大差不差，但偷率计算简单在它不用算矿工蹭了多少HP，偷了就是偷了，没偷就是没偷，没有“如偷”这种中间情况
* 改用非逐帧计算，节省了大量在`底线矿.cpp`里的低效计算，加快了模拟速度
* 虽然不一定能解决，但仍欢迎反馈使用时遇到的问题

## 现有API

### 声明

```c++
int TEST_YYG(bool isFreeze, bool isTarget, bool isWork);
int TEST_DPG(bool isFreeze, bool isTarget, bool isWork);
int TEST_BG(bool isFreeze, bool isCling, bool isTarget, bool isWork);
int TEST_DC(bool isFreeze, bool isDCW, bool isWork);
```

### parameter(True/False, 标"*"的项为可选参数)

* isFreeze:     是否用冰
* isTarget*:    是否被抓(为T即指定蹦极要偷的植物, 地刺默认T, 其余F)
* isWork*:      是否工作(即永动状态, 瓜默认T, 其余F)
* isCling:      是否贴脸(指定瓜相对于蹦极的位置, 当瓜位于x列而蹦极位于x或x+1列时, 令此项为T)
* isDCW*:       是否为地刺王(默认T, 测普通地刺请令此项为F)

## 更新日志

单独写个CHANGELOG不是很直观，干脆就跟README并一起算了

### 2023_11_04

* 包括`constVar.h`与本体`iceKillBungee.cpp`
* 仅支持静曾模拟与锁rnd验算

### 2023_11_06

* 修复了边界值与实际不符的bug
* 添加了若干测试与调试实例

### 2023_11_13

* 将声明、实现与测试用例分离了出来，将`iceKillBungee.cpp`改为`ialgo.cpp`(原先的.cpp已弃用)
* 添加了一键执行.bat，运行时在终端键入`.\run.bat`，即可生成实例`ikb_eg.exe`
* 添加了动曾计算，添加了大喷菇的模拟代码

### 2023_12_10

* 新增瓜的模拟代码，8过由于还没写减速判定所以充其量只是西瓜

### 2023_12_27

* 新增地刺的模拟代码，修改了部分逻辑。

### 2024_01_08

* 新增`interlayer.h`与`interlayer.cpp`以统一调用的函数
* 就tm你冰瓜事多！摆烂不写了

### 2024_01_20

* API说明忘写了，补上
