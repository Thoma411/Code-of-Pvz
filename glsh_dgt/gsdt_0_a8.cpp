/*
 * @Author: Thoma4
 * @Date: 2022-10-08 15:46:35
 */
#include <iostream>
#include <ctime>
#include <random>
#include <vector>
using namespace std;

#define stt_min 186
#define stt_max 200
#define digger_eat 352
#define hitt_HP 15
// #define test_times 10000
// #define gl_num 5

int main()
{
    clock_t test_start, test_finish;
    double total_time = 0;

    int gl_num = 4, test_times = 100;
    char dfName[128] = {0};
    cout << "input gloom_shroom(a)_number, test_times:\n";
    cin >> gl_num >> test_times;
    sprintf(dfName, "%da_%d.txt", gl_num, test_times);
    system("CLS");

    default_random_engine eg;                              //初始化随机数引擎
    uniform_int_distribution<int> uf_st(1, 200);           //起始时钟 矿工站稳时的倒计时
    uniform_int_distribution<int> uf_ht(stt_min, stt_max); //激发时钟 动曾的攻击间隔倒计时
    eg.seed(time(0));

    const int hitt1 = 74, hitt2 = 102, hitt3 = 130, hitt4 = 158; //曾的相对命中时机
    int countEat = 0;                                            //统计有伤测试次数
    vector<int> eatTimeArr;                                      //结束时间表
    eatTimeArr.clear();

    test_start = clock();
    for (int ti = 0; ti < test_times; ti++) //测试次数
    {
        int gCD[gl_num] = {0},                  //曾本轮攻击间隔
            gt[gl_num] = {0};                   //曾倒计时数组
        int gametick = 0, hit_digger_times = 0; //游戏进行时间(测试时间)&命中次数

        int ufh_const = uf_ht(eg), ufs_const = uf_st(eg); //第一次生成是固定的,予以剔除
        for (int gnum = 0; gnum < gl_num; gnum++)
            gt[gnum] = uf_st(eg);

        while (gametick <= stt_max) //动曾处理
        {
            gametick++;
            for (int gnum = 0; gnum < gl_num; gnum++)
            {
                gt[gnum]--;
                if (gt[gnum] <= 0)                    //*若本轮倒计时结束
                    gt[gnum] = gCD[gnum] = uf_ht(eg); //获取曾本轮的攻击间隔赋给gCD
            }
        }
        gametick = 0; //测试时间归零

        while (hit_digger_times < hitt_HP /* && gametick < digger_eat*/) //循环退出条件:命中达到15次
        {
            gametick++;
            for (int gnum = 0; gnum < gl_num; gnum++)
            {
                gt[gnum]--;
                //*若本轮倒计时结束
                if (gt[gnum] <= 0)
                    gt[gnum] = gCD[gnum] = uf_ht(eg); //获取曾本轮的攻击间隔赋给gCD
                //*统计命中矿工的次数
                if (gt[gnum] == gCD[gnum] - hitt1 || gt[gnum] == gCD[gnum] - hitt2 ||
                    gt[gnum] == gCD[gnum] - hitt3 || gt[gnum] == gCD[gnum] - hitt4)
                    hit_digger_times++;
            }
        }
        if (/*hit_digger_times < hitt_HP ||*/ gametick >= digger_eat)
        {
            countEat++;
            eatTimeArr.push_back(gametick - digger_eat); // 352对应啃食时刻0
        }

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
    double failp = double(countEat) / double(test_times);

    FILE *fpt; //输出测试结果至文本文件
    fpt = fopen(dfName, "a+");
    for (int it = 0; it < eatTimeArr.size(); it++)
    {
        int eatHP = eatTimeArr[it] / 4 * 4 + 4;
        fprintf(fpt, "%d\t%d\n", eatTimeArr[it], eatHP);
    }
    fclose(fpt);

    cout << "total time: " << total_time << " (s)" << endl;
    cout << "In this test, " << gl_num << "YYGs' probability of failure = " << failp << ".\n";
    // system("pause");
    return 0;
}
