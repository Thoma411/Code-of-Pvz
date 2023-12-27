/*
 * @Author: Thoma411
 * @Date: 2023-11-13 17:32:45
 * @LastEditTime: 2023-12-27 22:12:49
 * @Description: g++ ialgo.cpp test.cpp -o t.exe
 */
#include "ialgo.h"

#define N 1000000 // 10e7
extern map<int, int> cntArr;

// 测试0: 单曾在时间t内的攻击次数
int test0(int t, bool p_st = false)
{
    return CHT_YYG(getRnd(1, 200), t, p_st);
}

// 测试1: 冰杀2曾偷1(单次)
int test1(int stt = getRnd(699, 899))
{
    int ht1 = CHT_YYG(getRnd(1, 200), stt, false),
        ht2 = CHT_YYG(getRnd(1, 200), stt + 125, false);
    return ht1 + ht2;
}

// 测试2: 原速n曾无被偷(单次)
int test2(int n)
{
    int hts = 0;
    int bgt[n] = {};
    for (int i = 0; i < n; i++)
    {
        bgt[i] = getRnd(1, 200);
        // printf("yyg[%d]: rnd: %d\n", i, bgt[i]);
        hts += CHT_YYG(bgt[i], 363, false);
    }
    return hts;
}

// 测试3: 快速测底线损伤(4q)
int test3()
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

// 测试4: 快速测底线损伤(3q/a)
int test4(bool p_st = false)
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

// 测试5: 三动曾0被偷
int test5()
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

// 测试6: 单喷在时间t内的攻击次数
int test6(int t, bool p_st = false)
{
    return CHT_DPG(getRnd(1, 150), t, p_st);
}

// 测试7: 原速n曾偷1(单次)
int test7(int n)
{
    int hts = 0;
    int bgt[n - 1] = {};
    for (int i = 0; i < n - 1; i++)
    {
        bgt[i] = getRnd(1, 200);
        hts += CHT_YYG(bgt[i], 363, false);
    }
    int ht_other = CHT_YYG(getRnd(1, 200), 300, false); // 被偷的
    return hts + ht_other;
}

// 测试8: 1曾*n大喷-冰杀
int test8(int n, int stt = getRnd(699, 899))
{
    int hts = 0, bgt_dpg[n] = {};
    for (int i = 0; i < n; i++)
    {
        bgt_dpg[i] = getRnd(1, 150);
        hts += CHT_DPG(bgt_dpg[i], stt + 125, false);
    }
    hts += CHT_YYG(getRnd(1, 200), stt + 125, false);
    return hts;
}

// 测试9: 3西瓜
int test9(int n, int stt = getRnd(699, 899))
{
    int hts = 0, bgt[n - 1] = {};
    for (int i = 0; i < n - 1; i++)
    {
        bgt[i] = getRnd(1, 300);
        hts += CHT_BG(bgt[i], stt + 125, false);
    }
    hts += CHT_BG(getRnd(1, 300), stt, true); // 被偷的
    return hts;
}

// 测试10: 地刺
int test10(int stt)
{
    return CHT_DC(stt);
}

// 测试11: 1曾1刺
int test11(int stt)
{
    int hts = 0;
    hts += CHT_YYG(getRnd(1, 200), stt + 125);
    hts += CHT_DC(stt, false);
    return hts;
}

// 统计随机数分布
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

/*
 *验证双曾冰杀失败的极端情况
 *测算此极小概率事件更精确的办法可能是用这个函数模拟
 *在一个小区间上枚举所有可能情况(目测不止不在宝前贴中列的7种...)
 */
void debug1()
{
    // int beg_t = 170, stay_t = 300, rnd1 = 186;
    // int deb_ht = debug_hits(beg_t, stay_t, 1, rnd1);
    int deb_ht1 = DBG_YYG(200, 699 + 125, false, 3, 200, 200, 200);
    int deb_ht2 = DBG_YYG(200, 699, false, 3, 198, 200, 200);
    printf("debug_hts = %d, %d\n", deb_ht1, deb_ht2);
    // printf("debug_hts = %d\nbeg_t: %d\tstay_t: %d\trnd1: %d",
    //        deb_ht, beg_t, stay_t, rnd1);
}

// 罗列单曾的每一种情况
void debug2(int beg_n, int end_n, int stay_n)
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

// 罗列单喷的每一种情况
void debug3(int beg_n, int end_n, int stay_n)
{
    cntArr.clear();
    for (int i = beg_n; i <= end_n; i++)
    {
        // printf("debug_hts = %d\n", debug_hits(i, 300, 1, end_n));
        statistic_rnd(DBG_DPG(i, stay_n, false, 1, end_n));
    }
    for (const auto &pair : cntArr) // 输出每个随机数及其出现次数
        cout << "rnd: " << pair.first << " times: " << pair.second << endl;
}

// 通用测试模板
void ctest()
{
    clock_t test_start, test_finish;
    double total_time = 0; // 模拟测试总时长(计算部分)
    test_start = clock();

    for (int i = 0; i < N; i++)
        // statistic_rnd(test6(300, true));
        statistic_rnd(test7(6));
    // statistic_rnd(test9(3));
    // statistic_rnd(test11(getRnd(699, 899)));

    for (const auto &pair : cntArr) // 输出每个随机数及其出现次数
        cout << "rnd: " << pair.first << " times: " << pair.second << endl;
    //! 若要引用此结果作为概率, 请特别注意是否受冰(受冰21(含), 否则22(含)均算作失败)!
    int fail = cmpLeq(22);
    double perct = double(fail) / double(N);

    test_finish = clock();
    total_time = (double)(test_finish - test_start) / CLOCKS_PER_SEC; // 统计n次测试总用时
    printf("N = %d\tfail = %d\tP = %lf\ntotal time: %lf (s)\n", N, fail, perct, total_time);
}

int main()
{
    ctest();
    // debug3(1, 150, 824);
}