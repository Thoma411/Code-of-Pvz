/*
 * @Author: Thoma411
 * @Date: 2023-11-13 17:23:07
 * @LastEditTime: 2023-11-13 21:33:49
 * @Description:
 */
#ifndef _IALGO_H_
#define _IALGO_H_

#include <iostream>
#include <ctime>
#include <random>
#include <map>
#include <stdarg.h>
using namespace std;

int leqt(int &i, int &n);       // 输出不超过n的i++, 用于不定参数
int getRnd(int begt, int endt); // 获取随机数
void statistic_rnd(int num);    // 统计(区间)攻击次数的频率

int QAJ_YYG(int beg_t);                                           // 动静判定-曾
int CHT_YYG(int beg_t, int stay_t, bool p_stat = false);          // 计算指定时间内曾的输出伤害
int DBG_YYG(int beg_t, int stay_t, bool p_st, int time_cnt, ...); // 调试CHT

int QAJ_DPG(int beg_t);
int CHT_DPG(int beg_t, int stay_t, bool p_stat = false);

#endif