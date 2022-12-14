<!--
 * @Author: Thoma4
 * @Date: 2022-10-20 13:27:10
 * @LastEditTime: 2022-11-21 22:47:48
 * @Description: 
-->
# 更新日志

## 1.2f &emsp; 2022_11_21

* 增设啃食结算间隔，调整了存储有伤测试的数据结构和文件的写入部分
* **U&P** :
  * 同`1.1`

## 1.1f &emsp; 2022_10_21

* 修复了计算边界值产生的伤害有误的问题，修改了失败条件的判定基准，结果上更贴近游戏实测了
* 需要注意的是，在这一版输出的文本文件中，啃食时间1对应矿工存活时间353, 所以伤害为4，而0(对应352)则不会被出现在记录中
* **U&P** :
  * 同`1.1`

## 1.1 &emsp; 2022_10_20

* 反向继承了`0.a8`的文件写入
* **U&P** :
  * 按提示依次输入静曾数量、动曾数量、测试规模和自定义文件后缀后回车
  * 程序运行完毕后会输出该情况下的失败概率
  * 有伤部分会被按`矿工啃食时长\t产生伤害量\n`的格式输出至文本文件

## 1.0 &emsp; 2022_10_17

* 融合了前两个版本，支持测试动曾+静曾的组合构型
* **U&P** :
  * 按提示依次输入静曾数量、动曾数量和测试规模后回车
  * 程序运行完毕后会输出该情况下的失败概率

## 0.a8 &emsp; 2022_10_09

* 纯动曾模拟测试，改自`0.q5`纯静曾版，同样只能测纯动曾的构型
* 新增文件写入
* **U&P** :
  * 按提示依次输入动曾数量和测试规模后回车
  * 程序运行完毕后会输出该情况下的失败概率
  * 有伤部分会被按`矿工啃食时长\t产生伤害量\n`的格式输出至文本文件

## 0.q5 &emsp; 2022_10_08

* 纯静曾模拟测试，只能测试守底均为静曾的构型的失败概率
* **U&P** :
  * 按提示依次输入静曾数量和测试规模后回车
  * 程序运行完毕后会输出该情况下的失败概率(以及程序测试部分运行时间)
