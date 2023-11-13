/*
 * @Author: Thoma411
 * @Date: 2023-11-13 17:32:45
 * @LastEditTime: 2023-11-13 21:33:22
 * @Description: g++ ialgo.cpp test.cpp -o t.exe
 */
#include "ialgo.h"

#define N 1000
extern map<int, int> cntArr;

int test0(int t, bool p_st = false) // 测试0: 单曾在时间t内的攻击次数
{
    return CHT_YYG(getRnd(1, 200), t, p_st);
}

int test1() // 测试1: 冰杀2曾偷1(单次)
{
    int bgt1 = getRnd(1, 200), bgt2 = getRnd(1, 200);
    int ht1 = CHT_YYG(bgt1, 824, false), ht2 = CHT_YYG(bgt2, 699, false);
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
        hts += CHT_YYG(bgt[i], 363, false);
    }
    int ht6 = CHT_YYG(getRnd(1, 200), 300, false);
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
        hts += CHT_YYG(bgt[i], 352, false);
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
        hts += CHT_YYG(bgt[i], 352, p_st);
    }
    return hts;
}

int test5() // 测试5: 三动曾0被偷
{
    int yyg_num = 3, hts = 0;
    int bgt[yyg_num] = {};
    for (int i = 0; i < yyg_num; i++)
    {
        bgt[i] = getRnd(1, 200);
        hts += CHT_YYG(bgt[i], 363, true);
    }
    return hts;
}

int test6(int t, bool p_st = false) // 测试6: 单喷在时间t内的攻击次数
{
    return CHT_DPG(getRnd(1, 150), t, p_st);
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
    int deb_ht1 = DBG_YYG(200, 824, false, 3, 200, 200, 200);
    int deb_ht2 = DBG_YYG(200, 699, false, 3, 198, 200, 200);
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
        statistic_rnd(DBG_YYG(i, stay_n, false, 1, end_n));
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
        statistic_rnd(test6(300, true));

    for (const auto &pair : cntArr) // 输出每个随机数及其出现次数
        cout << "rnd: " << pair.first << " times: " << pair.second << endl;

    test_finish = clock();
    total_time = (double)(test_finish - test_start) / CLOCKS_PER_SEC; // 统计n次测试总用时
    printf("N = %d\ntotal time: %lf (s)\n", N, total_time);
}