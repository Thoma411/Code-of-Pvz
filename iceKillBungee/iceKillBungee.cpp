/*
 * @Author: Thoma411
 * @Date: 2023-10-23 18:08:37
 * @LastEditTime: 2023-11-04 23:12:07
 * @Description: 非逐帧冰杀小偷模拟
 */
#include <iostream>
#include <ctime>
#include <random>
#include <map>
#include <stdarg.h>
#include "constVar.h"
using namespace std;

#define N 10000000 // 000
const bool debugFlag = false;
map<int, int> cntArr;              // 用于保存随机数和对应的出现次数
default_random_engine eg(time(0)); // 在main函数外部初始化随机数引擎

int leqt(int &i, int &n) // 输出不超过n的i++, 用于不定参数
{
    if (i < n - 1)
        return i++;
    else
        return n - 1;
}

int getRnd(int begt, int endt) // 获取随机数
{
    uniform_int_distribution<int> rndt(begt, endt); // 设置随机数分布的范围
    int tmpRnd = rndt(eg);                          // 第一次生成是固定的,予以剔除
    return rndt(eg);                                // 使用全局的随机数引擎生成随机数
}

void statistic_rnd(int num) // 统计(区间)攻击次数的频率
{
    // 检查该随机数是否已存在于map中，如果存在则增加其出现次数，否则将其插入map中并将出现次数设为1
    if (cntArr.find(num) != cntArr.end())
        cntArr[num]++;
    else
        cntArr[num] = 1;
}

/*
 *计算指定时间内植物的输出伤害(单次)
 *parameter: 落地时的攻击倒计时, 滞留时间, 是否为目标植物x 是动是静
 */
int calc_hit_times(int beg_t, int stay_t, bool target = false)
{
    /*
     *1.动静判断(默认为静)
     *2.计算指定时间内打出的伤害
     *2.1.完整性攻击判定
     *2.2.剩余攻击判定
     TODO:边界值判定
     *3.返回输出伤害
     */
    if (stay_t - beg_t < YYG_h1) // 还没开始攻击小偷就溜了
        return 0;
    else
        stay_t -= beg_t;             // 当前剩余攻击时间
    int atck_rnd = getRnd(186, 200); // 生成下一轮攻击间隔
    if (debugFlag)
        cout << "atck: " << atck_rnd << endl;
    int rounds = 0, hits = 0;          // 攻击轮数(用于一轮攻击打多发的植物)&攻击次数
    while (stay_t - atck_rnd > YYG_h1) // 如果能完整的攻击完一轮
    {
        stay_t -= atck_rnd;          // 更新剩余时间-=本轮攻击间隔
        rounds++;                    // 完整轮数+1
        atck_rnd = getRnd(186, 200); // 重新生成攻击间隔随机数
        if (debugFlag)
            printf("round: %d, atck: %d\n", rounds, atck_rnd);
    }
    if (stay_t >= YYG_h1 && stay_t < YYG_h2) // 74(衔接L34的判定) <= 剩余时间 < 102
        hits += 1;
    else if (stay_t >= YYG_h2 && stay_t < YYG_h3) // 102 <= 剩余时间 < 130
        hits += 2;
    else if (stay_t >= YYG_h3 && stay_t < YYG_h4) // 130 <= 剩余时间 < 158
        hits += 3;
    else if (stay_t >= YYG_h4) // 158 <= 剩余时间 (<200)
        hits += 4;
    else // 未知错误
        return -999;
    return rounds * 4 + hits;
}

/*
 *计算指定时间内植物的输出伤害(单次)
 *parameter: 落地时的攻击倒计时, 滞留时间, 指定rnd总数, rnd1, rnd2, ...
 */
int debug_hits(int beg_t, int stay_t, int time_cnt, ...) // 不定参数
{
    va_list rnds; // 指定不定个随机数
    va_start(rnds, time_cnt);
    int *rndArr = new int[time_cnt];
    for (int i = 0; i < time_cnt; i++) // 保存所有指定的攻击间隔rnd到数组
        rndArr[i] = va_arg(rnds, int);
    va_end(rnds);
    int rdi = 0; // rndArr的指针, 指向当前指定的rnd

    if (stay_t - beg_t < YYG_h1) // 还没开始攻击小偷就溜了
        return 0;
    else
        stay_t -= beg_t;                        // 当前剩余攻击时间
    int atck_rnd = rndArr[leqt(rdi, time_cnt)]; // 生成下一轮攻击间隔
    if (debugFlag)
        cout << "atck: " << atck_rnd << endl;
    int rounds = 0, hits = 0;          // 攻击轮数(用于一轮攻击打多发的植物)&攻击次数
    while (stay_t - atck_rnd > YYG_h1) // 如果能完整的攻击完一轮
    {
        stay_t -= atck_rnd;                     // 更新剩余时间-=本轮攻击间隔
        rounds++;                               // 完整轮数+1
        atck_rnd = rndArr[leqt(rdi, time_cnt)]; // 重新生成攻击间隔随机数
        if (debugFlag)
            printf("round: %d, atck: %d\n", rounds, atck_rnd);
    }
    if (stay_t >= YYG_h1 && stay_t < YYG_h2) // 74(衔接L34的判定) <= 剩余时间 < 102
        hits += 1;
    else if (stay_t >= YYG_h2 && stay_t < YYG_h3) // 102 <= 剩余时间 < 130
        hits += 2;
    else if (stay_t >= YYG_h3 && stay_t < YYG_h4) // 130 <= 剩余时间 < 158
        hits += 3;
    else if (stay_t >= YYG_h4) // 158 <= 剩余时间 (<200)
        hits += 4;
    else // 未知错误
        return -999;
    delete rndArr; // 释放rndArr占用的内存
    return rounds * 4 + hits;
}

int test0(int t) // 测试0: 非目标单曾在时间t内的攻击次数
{
    return calc_hit_times(getRnd(1, 200), t);
}

int test1() // 测试1: 冰杀2曾偷1(单次)
{
    int bgt1 = getRnd(1, 200), bgt2 = getRnd(1, 200);
    int ht1 = calc_hit_times(bgt1, 824), ht2 = calc_hit_times(bgt2, 699);
    if (debugFlag)
        cout << "beg_time: " << bgt1
             << ht1 << endl;
    return ht1 + ht2;
}

int test2() // 测试2: 原速6曾偷1(单次)
{
    int yyg_num = 5, hts = 0;
    int bgt[yyg_num] = {};
    for (int i = 0; i < yyg_num; i++)
    {
        bgt[i] = getRnd(1, 200);
        hts += calc_hit_times(bgt[i], 363);
    }
    int ht6 = calc_hit_times(getRnd(1, 200), 300);
    return hts + ht6;
}

int test3() // 测试3: 快速测底线损伤
{
    int yyg_num = 4, hts = 0;
    int bgt[yyg_num] = {};
    for (int i = 0; i < yyg_num; i++)
    {
        bgt[i] = getRnd(1, 200);
        hts += calc_hit_times(bgt[i], 352);
    }
    return hts;
}

void debug1()
{
    // int beg_t = 170, stay_t = 300, rnd1 = 186;
    // int deb_ht = debug_hits(beg_t, stay_t, 1, rnd1);
    int deb_ht1 = debug_hits(200, 824, 3, 200, 200, 200);
    int deb_ht2 = debug_hits(200, 699, 3, 198, 200, 200);
    printf("debug_hts = %d, %d\n", deb_ht1, deb_ht2);
    // printf("debug_hts = %d\nbeg_t: %d\tstay_t: %d\trnd1: %d",
    //        deb_ht, beg_t, stay_t, rnd1);
}

int main()
{
    // clock_t test_start, test_finish;
    // double total_time = 0; // 模拟测试总时长(计算部分)
    // test_start = clock();

    // // int testArr[5] = {}; // 概率分布数组
    // // int hts = 0;

    // for (int i = 0; i < N; i++)
    //     statistic_rnd(test0(300));

    // for (const auto &pair : cntArr) // 输出每个随机数及其出现次数
    //     cout << "rnd: " << pair.first << " times: " << pair.second << endl;

    // test_finish = clock();
    // total_time = (double)(test_finish - test_start) / CLOCKS_PER_SEC; // 统计n次测试总用时
    // printf("N = %d\ntotal time: %lf (s)\n", N, total_time);

    // for (int i = 0; i < 5; i++)
    //     cout << testArr[i] << " ";

    debug1();

    // system("pause");
    return 0;
}