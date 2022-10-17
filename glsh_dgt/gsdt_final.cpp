/*
 * @Author: Thoma4
 * @Date: 2022-10-17 17:33:47
 * @LastEditTime: 2022-10-17 21:51:56
 */
#include <iostream>
#include <ctime>
#include <random>
using namespace std;

#define stt_min 186
#define stt_max 200
#define digger_eat 352

int main()
{
    clock_t test_start, test_finish;
    double total_time = 0;

    default_random_engine eg;                              //初始化随机数引擎
    uniform_int_distribution<int> uf_st(1, 200);           //起始时钟 矿工站稳时的倒计时
    uniform_int_distribution<int> uf_ht(stt_min, stt_max); //激发时钟 动曾的攻击间隔倒计时
    eg.seed(time(0));

    const int hitt1 = 74, hitt2 = 102, hitt3 = 130, hitt4 = 158; //曾的相对命中时机
    int countEat = 0;                                            //统计有伤测试次数

    int glq_num, gla_num, test_times;
    printf("input gloom_shroom number([quiet] & [active]) & [test times]:\n");
    cin >> glq_num >> gla_num >> test_times;
    system("CLS");

    test_start = clock();
    for (int ti = 0; ti < test_times; ti++) //测试次数
    {
        int gCDq[glq_num] = {0}, gCDa[gla_num] = {0}, //曾本轮攻击间隔
            gtq[glq_num] = {0}, gta[gla_num] = {0};   //曾倒计时数组

        int gametick = 0, hit_digger_times = 0; //游戏进行时间(测试时间)&命中次数

        int ufh_const = uf_ht(eg), ufs_const = uf_st(eg); //第一次生成是固定的,予以剔除
        for (int gnum = 0; gnum < glq_num; gnum++)
            gtq[gnum] = uf_st(eg); //*没必要增设标志位 因为初始化倒计时不会被计入gCD
        for (int gnum = 0; gnum < glq_num; gnum++)
            gta[gnum] = uf_st(eg);

        while (gametick <= stt_max) //动曾处理
        {
            gametick++;
            for (int gnum = 0; gnum < gla_num; gnum++)
            {
                gta[gnum]--;
                if (gta[gnum] <= 0)                     //*若本轮倒计时结束
                    gta[gnum] = gCDa[gnum] = uf_ht(eg); //获取曾本轮的攻击间隔赋给gCDa
            }
        }
        gametick = 0; //测试时间归零

        while (hit_digger_times < 15 && gametick < digger_eat) //循环退出条件:命中达到15次or测试时间>矿工啃食时间
        {
            gametick++;
            for (int gnum = 0; gnum < glq_num; gnum++)
            {
                gtq[gnum]--;
                //*若本轮倒计时结束
                if (gtq[gnum] <= 0)
                    gtq[gnum] = gCDq[gnum] = uf_ht(eg); //获取曾本轮的攻击间隔赋给gCDq
                //*统计命中矿工的次数
                if (gtq[gnum] == gCDq[gnum] - hitt1 || gtq[gnum] == gCDq[gnum] - hitt2 ||
                    gtq[gnum] == gCDq[gnum] - hitt3 || gtq[gnum] == gCDq[gnum] - hitt4)
                    hit_digger_times++;
            }
            for (int gnum = 0; gnum < gla_num; gnum++)
            {
                gta[gnum]--;
                //*若本轮倒计时结束
                if (gta[gnum] <= 0)
                    gta[gnum] = gCDa[gnum] = uf_ht(eg); //获取曾本轮的攻击间隔赋给gCDa
                //*统计命中矿工的次数
                if (gta[gnum] == gCDa[gnum] - hitt1 || gta[gnum] == gCDa[gnum] - hitt2 ||
                    gta[gnum] == gCDa[gnum] - hitt3 || gta[gnum] == gCDa[gnum] - hitt4)
                    hit_digger_times++;
            }
        }
        if (hit_digger_times < 15 || gametick >= digger_eat)
            countEat++;

        printf("test num: %d\n", ti + 1);
        // printf("hdt = %d\n", hit_digger_times); //输出结束时的攻击次数
        // printf("gametick = %d\n", gametick);    //输出此时的游戏时间
        printf("fail / total = %d / %d\n", countEat, test_times);
        if (ti < test_times - 1)
            system("CLS");
    }
    test_finish = clock();
    total_time = (double)(test_finish - test_start) / CLOCKS_PER_SEC; //统计n次测试总用时
    printf("total time: %lf (s)\n", total_time);
    double failp = double(countEat) / double(test_times);
    printf("In this test(%d quiet, %d active):\n", glq_num, gla_num);
    printf("probability of failure = %lf, (%lf %).\n", failp, failp * 100);
    system("pause");
    return 0;
}