/*
 * @Author: Thoma4
 * @Date: 2022-10-17 17:33:47
 * @LastEditTime: 2022-10-21 23:39:06
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <random>
using namespace std;

const int fName_suf = 64; //输出文件自定义后缀
const int stt_min = 186;
const int stt_max = 200;
const int digger_eat = 352;
const int hitt_HP = 15;

int main()
{
    clock_t test_start, test_finish;
    double total_time = 0; //模拟测试总时长(计算部分)

    int glq_num, gla_num, test_times;
    char dfName[fName_suf * 2], cfName[fName_suf]; //输出文件名=默认+自定义后缀.txt
    printf("input gloom_shroom number(quiet, active), test_times, fname_suf(EN):\n");
    cin >> glq_num >> gla_num >> test_times >> cfName;
    sprintf(dfName, "%dq%da_%d_%s.txt", glq_num, gla_num, test_times, cfName);
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
        int gCDq[glq_num] = {0}, gCDa[gla_num] = {0}, //曾本轮攻击间隔
            gtq[glq_num] = {0}, gta[gla_num] = {0};   //曾倒计时数组
        int gametick = 0, hit_digger_times = 0;       //游戏进行时间(测试时间)&命中次数

        int ufh_const = uf_ht(eg), ufs_const = uf_st(eg); //第一次生成是固定的,予以剔除
        for (int gnum = 0; gnum < glq_num; gnum++)
            gtq[gnum] = uf_st(eg); //*没必要增设标志位 因为初始化倒计时不会被计入gCD
        for (int gnum = 0; gnum < gla_num; gnum++)
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

        //添加啃食伤害计算(输出到文件 以便后续做方差分析)
        while (hit_digger_times < hitt_HP /* && gametick <= digger_eat*/) //循环退出条件:命中达到15次
        {
            gametick++;
            for (int gnum = 0; gnum < glq_num; gnum++)
            {
                gtq[gnum]--;
                if (gtq[gnum] <= 0)
                    gtq[gnum] = gCDq[gnum] = uf_ht(eg);
                if (gtq[gnum] == gCDq[gnum] - hitt1 || gtq[gnum] == gCDq[gnum] - hitt2 ||
                    gtq[gnum] == gCDq[gnum] - hitt3 || gtq[gnum] == gCDq[gnum] - hitt4)
                    hit_digger_times++;
            }
            for (int gnum = 0; gnum < gla_num; gnum++)
            {
                gta[gnum]--;
                if (gta[gnum] <= 0)
                    gta[gnum] = gCDa[gnum] = uf_ht(eg);
                if (gta[gnum] == gCDa[gnum] - hitt1 || gta[gnum] == gCDa[gnum] - hitt2 ||
                    gta[gnum] == gCDa[gnum] - hitt3 || gta[gnum] == gCDa[gnum] - hitt4)
                    hit_digger_times++;
            }
        }
        // FIXME !修正边界值错误 忽略时刻352
        if (/*hit_digger_times < hitt_HP ||*/ gametick > digger_eat)
        {
            countEat++;
            // eatTimeArr[ti] = gametick; //添加单次测试结束时间(array)
            eatTimeArr.push_back(gametick - digger_eat); // 353对应啃食时刻1
        }
        printf("test num: %d\n", ti + 1);
        // printf("hdt = %d\n", hit_digger_times); //输出结束时的攻击次数
        // printf("gametick = %d\n", gametick);    //输出此时的游戏时间
        printf("fail / total = %d / %d\n", countEat, test_times);
        if (ti < test_times - 1)
            system("CLS");
    }
    test_finish = clock();
    total_time = (double)(test_finish - test_start) / CLOCKS_PER_SEC; //统计n次测试总用时
    double failp = double(countEat) / double(test_times);

    FILE *fpt; //输出测试结果至文本文件
    fpt = fopen(dfName, "w+");
    for (int it = 0; it < eatTimeArr.size(); it++)
    {
        // FIXME !修正啃食时间是4的倍数的伤害值错误
        int eatHP = (eatTimeArr[it] - 1) / 4 * 4 + 4;
        //**需要注意的是当前输出的文本文件中, 啃食时间1现在对应矿工存活时间353, 所以伤害为4
        fprintf(fpt, "%d\t%d\n", eatTimeArr[it], eatHP);
    }
    fclose(fpt);

    printf("total time: %lf (s)\n", total_time);
    printf("In this test(%d quiet, %d active):\n", glq_num, gla_num);
    printf("probability of failure = %lf, (%lf %).\n", failp, failp * 100);
    system("pause");
    return 0;
}
