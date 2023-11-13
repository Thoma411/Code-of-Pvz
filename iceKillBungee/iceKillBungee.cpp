/*
 * @Author: Thoma411
 * @Date: 2023-10-23 18:08:37
 * @LastEditTime: 2023-11-13 16:40:26
 * @Description: 非逐帧冰杀小偷模拟
 */
#include <iostream>
#include <ctime>
#include <random>
#include <map>
#include <stdarg.h>
#include "constVar.h"
using namespace std;

#define N 1000000 // 000
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
 *动静特判 仅判断当生成的rnd<=攻击间隔(1,200)的第一轮
 *返回时间t=rnd条件下本轮的攻击次数
 *默认停留时间>=200
 */
int QA_judge(int beg_t)
{
    /*
     *对给定的rnd, 划分为确定区间和模糊区间:
     *对落在确定区间内的rnd, 不用模拟就能得出攻击次数;
     *对落在模糊区间内的rnd, 再等概率随机生成一个0/1, 为0取小, 为1取大.
     */
    if (beg_t <= 0 || beg_t > 200) // rnd超出范围
        return -999;
    int hits = 0, ofs = getRnd(0, 1);
    // 确定区间
    if (beg_t > 0 && beg_t < 28)
        hits = 0;
    else if (beg_t >= 42 && beg_t < 56)
        hits = 1;
    else if (beg_t >= 70 && beg_t < 84)
        hits = 2;
    else if (beg_t >= 98 && beg_t < 112)
        hits = 3;
    else if (beg_t >= 126 && beg_t <= 200)
        hits = 4;
    // 模糊区间
    else if (beg_t >= 28 && beg_t < 42)
        hits = 0 + ofs;
    else if (beg_t >= 56 && beg_t < 70)
        hits = 1 + ofs;
    else if (beg_t >= 84 && beg_t < 98)
        hits = 2 + ofs;
    else if (beg_t >= 112 && beg_t < 126)
        hits = 3 + ofs;
    else // 未知错误
        return -999;
    return hits;
}

/*
 *计算指定时间内植物(目前只有曾)的输出伤害(单次)
 *parameter: 落地时的攻击倒计时, 滞留时间, 是动是静
 */
int calc_hit_times(int beg_t, int stay_t, bool p_stat = false)
{
    /*
     TODO:1.并入动静判断(默认为静)
     *2.计算指定时间内打出的伤害
     *2.1.完整性攻击判定
     *2.2.剩余攻击判定
     *3.返回输出伤害
     */
    int rounds = 0, hits = 0; // 攻击轮数(用于一轮攻击打多发的植物)&攻击次数
    if (!p_stat)              // *静曾首轮判定
    {
        if (stay_t - beg_t < YYG_h1) // 还没开始攻击小偷就溜了
            return 0;
    }
    else // *动曾首轮判定
        hits = QA_judge(beg_t);
    stay_t -= beg_t; // 计算当前剩余攻击时间

    int atck_rnd = getRnd(186, 200); // 生成下一轮攻击间隔
    if (debugFlag)
        cout << "atck: " << atck_rnd << endl;
    while (stay_t - atck_rnd >= YYG_h1) // 如果能完整的攻击完一轮
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
    int rounds = 0, hits = 0;           // 攻击轮数(用于一轮攻击打多发的植物)&攻击次数
    while (stay_t - atck_rnd >= YYG_h1) // 如果能完整的攻击完一轮
    {
        stay_t -= atck_rnd;                     // 更新剩余时间-=本轮攻击间隔
        rounds++;                               // 完整轮数+1
        atck_rnd = rndArr[leqt(rdi, time_cnt)]; // 重新生成攻击间隔随机数
        if (debugFlag)
            printf("round: %d, atck: %d\n", rounds, atck_rnd);
    }
    if (stay_t >= YYG_h1 && stay_t < YYG_h2) // 74(衔接L101的判定) <= 剩余时间 < 102
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

int test0(int t, bool p_st = false) // 测试0: 非目标单曾在时间t内的攻击次数
{
    return calc_hit_times(getRnd(1, 200), t, p_st);
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
        // printf("yyg[%d]: rnd: %d\n", i, bgt[i]);
        hts += calc_hit_times(bgt[i], 363);
    }
    int ht6 = calc_hit_times(getRnd(1, 200), 300);
    return hts + ht6;
}

int test3() // 测试3: 快速测底线损伤(4q)
{
    int yyg_num = 4, hts = 0;
    int bgt[yyg_num] = {};
    for (int i = 0; i < yyg_num; i++)
    {
        bgt[i] = getRnd(1, 200);
        // printf("yyg[%d]: rnd: %d\n", i, bgt[i]);
        hts += calc_hit_times(bgt[i], 352);
    }
    return hts;
}

int test4(bool p_st = false) // 测试4: 快速测底线损伤(3q/a)
{
    int yyg_num = 3, hts = 0;
    int bgt[yyg_num] = {};
    for (int i = 0; i < yyg_num; i++)
    {
        bgt[i] = getRnd(1, 200);
        // printf("yyg[%d]: rnd: %d\n", i, bgt[i]);
        hts += calc_hit_times(bgt[i], 352, p_st);
    }
    return hts;
}

void debug0()
{
    cntArr.clear();
    int test_r = 0;
    for (int i = 0; i < N; i++)
    {
        test_r = getRnd(186, 200);
        statistic_rnd(test_r);
    }
    for (const auto &pair : cntArr) // 输出每个随机数及其出现次数
        cout << "rnd: " << pair.first << " times: " << pair.second << endl;
}

void debug1() // 验证双曾冰杀失败的极端情况
{
    // int beg_t = 170, stay_t = 300, rnd1 = 186;
    // int deb_ht = debug_hits(beg_t, stay_t, 1, rnd1);
    int deb_ht1 = debug_hits(200, 824, 3, 200, 200, 200);
    int deb_ht2 = debug_hits(200, 699, 3, 198, 200, 200);
    printf("debug_hts = %d, %d\n", deb_ht1, deb_ht2);
    // printf("debug_hts = %d\nbeg_t: %d\tstay_t: %d\trnd1: %d",
    //        deb_ht, beg_t, stay_t, rnd1);
}

void debug2(int beg_n, int end_n, int stay_n) //
{
    // printf("debug_hts = %d\n", debug_hits(beg_n, 300, 1, end_n));
    cntArr.clear();
    for (int i = beg_n; i <= end_n; i++)
    {
        // printf("debug_hts = %d\n", debug_hits(i, 300, 1, end_n));
        statistic_rnd(debug_hits(i, stay_n, 1, end_n));
    }
    for (const auto &pair : cntArr) // 输出每个随机数及其出现次数
        cout << "rnd: " << pair.first << " times: " << pair.second << endl;
}

int main()
{
    clock_t test_start, test_finish;
    double total_time = 0; // 模拟测试总时长(计算部分)
    test_start = clock();

    for (int i = 0; i < N; i++)
        // statistic_rnd(test0(300, true));
        statistic_rnd(test4());

    for (const auto &pair : cntArr) // 输出每个随机数及其出现次数
        cout << "rnd: " << pair.first << " times: " << pair.second << endl;

    test_finish = clock();
    total_time = (double)(test_finish - test_start) / CLOCKS_PER_SEC; // 统计n次测试总用时
    printf("N = %d\ntotal time: %lf (s)\n", N, total_time);

    // for (int i = 0; i <= 200; i++) // 调试动静(一轮)判定
    //     printf("i: %d\th: %d\n", i, QA_judge(i));

    // for (int i = 186; i <= 200; i++)
    // {
    //     debug2(1, i, 363);
    //     printf("\n");
    // }

    // debug0();

    // system("pause");
    return 0;
}