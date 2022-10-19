/*
 * @Author: Thoma4
 * @Date: 2022-10-08 15:46:35
 */
#include <iostream>
#include <ctime>
#include <random>
#include <windows.h>
using namespace std;

#define stt_min 186
#define stt_max 200
#define digger_eat 352
// #define test_times 10000
// #define gl_num 5

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

    int gl_num = 4, test_times = 100;
    cout << "input [gloom_shroom number] & [test times]:\n";
    cin >> gl_num >> test_times;
    system("CLS");

    test_start = clock();
    for (int ti = 0; ti < test_times; ti++) //测试次数
    {
        int gCD[gl_num] = {0};                  //曾本轮攻击间隔
        bool hit_flag[gl_num] = {false};        //攻击判定标志位 1可以攻击
        int gametick = 0, hit_digger_times = 0; //游戏进行时间(测试时间)&命中次数

        int ufh_const = uf_ht(eg), ufs_const = uf_st(eg); //第一次生成是固定的,予以剔除
        int gt[gl_num] = {0};
        for (int gnum = 0; gnum < gl_num; gnum++)
            gt[gnum] = uf_st(eg);

        while (hit_digger_times < 15 && gametick < digger_eat) //循环退出条件:命中达到15次or测试时间>矿工啃食时间
        {
            // cout << gt1 << "\t" << gt2 << "\t" << gt3 << "\t" << gt4 << "\t" << gt5 << "\n";
            gametick++;
            for (int gnum = 0; gnum < gl_num; gnum++)
            {
                gt[gnum]--;
                //*若本轮倒计时结束
                if (gt[gnum] <= 0)
                {
                    gt[gnum] = gCD[gnum] = uf_ht(eg); //获取曾本轮的攻击间隔赋给gCD
                    hit_flag[gnum] = true;            //将攻击判定标志位置1
                }
                //*统计命中矿工的次数
                if (hit_flag[gnum]) //若标志位=1且为四个命中时刻
                    if (gt[gnum] == gCD[gnum] - hitt1 || gt[gnum] == gCD[gnum] - hitt2 ||
                        gt[gnum] == gCD[gnum] - hitt3 || gt[gnum] == gCD[gnum] - hitt4)
                    {
                        // cout << gt1 << "\t"; //输出命中时机(倒计时)
                        hit_digger_times++;
                    }
            }
            // Sleep(10);
        }
        if (hit_digger_times < 15 || gametick >= digger_eat)
            countEat++;

        cout << "\n\n";
        cout << "test num: " << ti + 1 << endl
             // << "hdt = " << hit_digger_times << endl
             << "gametick = " << gametick << endl //输出此时的游戏时间
             << "fail / total = " << countEat << " / " << test_times << endl;
        if (ti < test_times - 1)
            system("CLS");
    }
    test_finish = clock();
    total_time = (double)(test_finish - test_start) / CLOCKS_PER_SEC; //统计n次测试总用时
    cout << "total time: " << total_time << " (s)" << endl;
    double failp = double(countEat) / double(test_times);
    cout << "In this test, " << gl_num << "YYGs' probability of failure = " << failp << ".\n";
    system("pause");
    return 0;
}
