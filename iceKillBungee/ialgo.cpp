/*
 * @Author: Thoma411
 * @Date: 2023-10-23 18:08:37
 * @LastEditTime: 2024-01-08 19:50:15
 * @Description: 非逐帧冰杀小偷模拟
 */
#include "ialgo.h"

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

// 统计rnd不超过x时times的加和
int cmpLeq(int x)
{
    int sum = 0;
    for (const auto &pair : cntArr)
        if (pair.first <= x)
            sum += pair.second;
    return sum;
}

int jdg_time(int stat)
{
    if (stat == TGT_NI)
        return 300;
    else if (stat == TGT_BF1)
        return getRnd(699, 899);
    else if (stat == TGT_BF2)
        return getRnd(599, 699);
    else if (stat == NTG_NIO)
        return 363;
    else if (stat == NTG_NIS)
        return getRnd(363, 425);
    else if (stat == NTG_BF1)
        return getRnd(824, 1024);
    else if (stat == NTG_BF2)
        return getRnd(724, 824);
    else
        return ERR_FLG;
}

/*
 *动静特判 仅判断当生成的rnd<=攻击间隔(1,200)的第一轮
 *返回时间t=rnd条件下本轮的攻击次数
 *默认停留时间>=200
 */
int QAJ_YYG(int beg_t)
{
    /*
     *对给定的rnd, 划分为确定区间和模糊区间:
     *对落在确定区间内的rnd, 不用模拟就能得出攻击次数;
     *对落在模糊区间内的rnd, 再等概率随机生成一个0/1, 为0取小, 为1取大.
     */
    if (beg_t <= 0 || beg_t > 200) // rnd超出范围
        return ERR_FLG;
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
        return ERR_FLG;
    return hits;
}

/*
 *计算指定时间内曾的输出伤害(单次)
 *parameter: 落地时的攻击倒计时, 滞留时间, 是动是静
 */
int CHT_YYG(int beg_t, int stay_t, bool p_stat)
{
    /*
     *1.动静判断(默认为静)
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
        hits = QAJ_YYG(beg_t);
    stay_t -= beg_t; // 计算当前剩余攻击时间(去掉首轮 从下一轮开始用while判断hits次数)

    int atck_rnd = getRnd(186, 200);    // 生成下一轮攻击间隔
    while (stay_t - atck_rnd >= YYG_h1) // 如果能完整的攻击完一轮
    {
        stay_t -= atck_rnd;          // 更新剩余时间-=本轮攻击间隔
        rounds++;                    // 完整轮数+1
        atck_rnd = getRnd(186, 200); // 重新生成攻击间隔随机数
    }
    if (stay_t >= YYG_h1 && stay_t < YYG_h2) // 74(衔接L93的判定) <= 剩余时间 < 102
        hits += 1;
    else if (stay_t >= YYG_h2 && stay_t < YYG_h3) // 102 <= 剩余时间 < 130
        hits += 2;
    else if (stay_t >= YYG_h3 && stay_t < YYG_h4) // 130 <= 剩余时间 < 158
        hits += 3;
    else if (stay_t >= YYG_h4) // 158 <= 剩余时间 (<200)
        hits += 4;
    else // 未知错误
        return ERR_FLG;
    return rounds * 4 + hits;
}

/*
 *计算指定时间内曾的输出伤害(单次)
 *parameter: 落地时的攻击倒计时, 滞留时间, 是动是静, 指定rnd总数, rnd1, rnd2, ...
 */
int DBG_YYG(int beg_t, int stay_t, bool p_st, int time_cnt, ...) // 不定参数
{
    va_list rnds; // 指定不定个随机数
    va_start(rnds, time_cnt);
    int *rndArr = new int[time_cnt];
    for (int i = 0; i < time_cnt; i++) // 保存所有指定的攻击间隔rnd到数组
        rndArr[i] = va_arg(rnds, int);
    va_end(rnds);
    int rdi = 0; // rndArr的指针, 指向当前指定的rnd

    int rounds = 0, hits = 0; // 攻击轮数(用于一轮攻击打多发的植物)&攻击次数
    if (!p_st)                // *静曾首轮判定
    {
        if (stay_t - beg_t < YYG_h1) // 还没开始攻击小偷就溜了
            return 0;
    }
    else // *动曾首轮判定
        hits = QAJ_YYG(beg_t);
    stay_t -= beg_t; // 计算当前剩余攻击时间

    int atck_rnd = rndArr[leqt(rdi, time_cnt)]; // 生成下一轮攻击间隔
    while (stay_t - atck_rnd >= YYG_h1)         // 如果能完整的攻击完一轮
    {
        stay_t -= atck_rnd;                     // 更新剩余时间-=本轮攻击间隔
        rounds++;                               // 完整轮数+1
        atck_rnd = rndArr[leqt(rdi, time_cnt)]; // 重新生成攻击间隔随机数
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
        return ERR_FLG;
    delete rndArr; // 释放rndArr占用的内存
    return rounds * 4 + hits;
}

int QAJ_DPG(int beg_t)
{
    if (beg_t <= 0 || beg_t > 150) // rnd超出范围
        return ERR_FLG;
    int hits = 0, ofs = getRnd(0, 1);
    // 确定区间
    if (beg_t > 0 && beg_t < 87) // 0 ~ 136-49
        hits = 0;
    else if (beg_t >= 101 && beg_t <= 150) // 150-49 ~ 150
        hits = 1;
    // 模糊区间
    else if (beg_t >= 87 && beg_t < 101) // 此14cs为rnd波动区间
        hits = 0 + ofs;
    else // 未知错误
        return ERR_FLG;
    return hits;
}

int CHT_DPG(int beg_t, int stay_t, bool p_stat)
{
    int hits = 0; // 攻击次数
    if (!p_stat)  // *静喷首轮判定
    {
        if (stay_t - beg_t < 49) // 还没开始攻击小偷就溜了
            return 0;
    }
    else // *动喷首轮判定
        hits = QAJ_DPG(beg_t);
    stay_t -= beg_t; // 去掉首轮 从下一轮开始用while判断hits次数

    int atck_rnd = getRnd(136, 150); // 生成下一轮攻击间隔
    while (stay_t - atck_rnd >= 49)  // 如果能完整的攻击完一轮
    {
        stay_t -= atck_rnd; // 更新剩余时间-=本轮攻击间隔
        hits++;
        atck_rnd = getRnd(136, 150); // 重新生成攻击间隔随机数
    }
    if (stay_t >= 49) // 接"还没开始攻击小偷就溜了"判定
        hits += 1;
    return hits;
}

int DBG_DPG(int beg_t, int stay_t, bool p_st, int time_cnt, ...)
{
    va_list rnds; // 指定不定个随机数
    va_start(rnds, time_cnt);
    int *rndArr = new int[time_cnt];
    for (int i = 0; i < time_cnt; i++) // 保存所有指定的攻击间隔rnd到数组
        rndArr[i] = va_arg(rnds, int);
    va_end(rnds);
    int rdi = 0; // rndArr的指针, 指向当前指定的rnd

    int rounds = 0, hits = 0; // 攻击轮数(用于一轮攻击打多发的植物)&攻击次数
    if (!p_st)                // *静喷首轮判定
    {
        if (stay_t - beg_t < YYG_h1) // 还没开始攻击小偷就溜了
            return 0;
    }
    else // *动喷首轮判定
        hits = QAJ_DPG(beg_t);
    stay_t -= beg_t; // 计算当前剩余攻击时间

    int atck_rnd = rndArr[leqt(rdi, time_cnt)]; // 生成下一轮攻击间隔
    while (stay_t - atck_rnd >= 49)             // 如果能完整的攻击完一轮
    {
        stay_t -= atck_rnd; // 更新剩余时间-=本轮攻击间隔
        hits++;
        atck_rnd = rndArr[leqt(rdi, time_cnt)]; // 重新生成攻击间隔随机数
    }
    if (stay_t >= 49) // 接"还没开始攻击小偷就溜了"判定
        hits += 1;
    delete rndArr; // 释放rndArr占用的内存
    return hits;
}

int QAJ_BG(int beg_t, int clg_t)
{
    if (beg_t <= 0 || beg_t > 300) // rnd超出范围
        return ERR_FLG;
    int hits = 0, ofs = getRnd(0, 1);
    // 确定区间
    if (beg_t > 0 && beg_t < 286 - clg_t)
        hits = 0;
    else if (beg_t >= 300 - clg_t && beg_t <= 300)
        hits = 4;
    // 模糊区间
    else if (beg_t >= 286 - clg_t && beg_t < 300 - clg_t)
        hits = 0 + ofs * 4;
    else // 未知错误
        return ERR_FLG;
    return hits;
}

/*
 *parameter:
 *ice_t: 冰生效时机, 用冰时取值为1~300, 否则为-1(表示不用冰)
 *cling: 是否贴脸-默认为是
 !p_stat: 是否工作(永动)-默认为是
 deVel: 是否减速(二冰)-默认为否 该项应该由函数自动推断而不是指定状态
 */
int CHT_BG(int beg_t, int stay_t, int ice_t, bool cling, bool p_stat)
{
    // TODO:减速状态的一二次冰冻判定
    /*
     *ideas
     *超过363视为用冰
     *从stay_t入手. 若在冰生效之前命中, 则stay_t-100
     */
    int hits = 0, clg_t = 35; // 攻击次数&贴脸/远离状态下的命中时机
    if (!cling)               // 远离
        clg_t = 144;
    if (!p_stat) // *静冰瓜首轮判定
    {
        if (stay_t - beg_t < clg_t) // 还没开始攻击小偷就溜了
            return 0;
    }
    else // *动冰瓜首轮判定(不论是否被抓, 动瓜一定会命中至少一次)
        hits = QAJ_BG(beg_t, clg_t);
    stay_t -= beg_t; // 去掉首轮 从下一轮开始用while判断hits次数

    int atck_rnd = getRnd(286, 300);   // 生成下一轮攻击间隔
    while (stay_t - atck_rnd >= clg_t) // 如果能完整的攻击完一轮
    {
        stay_t -= atck_rnd; // 更新剩余时间-=本轮攻击间隔
        hits += 4;
        atck_rnd = getRnd(286, 300); // 重新生成攻击间隔随机数
    }
    if (stay_t >= clg_t) // 接"还没开始攻击小偷就溜了"判定
        hits += 4;
    return hits;
}

/*
 *parameter: 滞留时间, 是否为地刺王-默认为是(否则为地刺), 是否工作(永动)
 */
int CHT_DC(int stay_t, bool isDCW, bool p_stat)
{
    // TODO:待考虑特殊情况下的连续工作状态, 如被提前触发导致启动时间不固定
    int rounds = 0, hits = 0, itt = DCW_itv1; // 攻击次数&启动间隔itt = interval_time
    if (!isDCW)                               // 若为地刺
        itt = DC_h;
    while (stay_t - DC_hitv >= DCW_itv1) // 如果能完整的攻击完一轮
    {
        stay_t -= DC_hitv; // 更新剩余时间-=本轮攻击间隔
        rounds++;
    }
    if (isDCW) // 地刺王伤害计算
    {
        if (stay_t >= DCW_itv1 && stay_t < DCW_itv2) // 30(接"还没开始攻击小偷就溜了"判定) <= 剩余时间 < 68
            hits += 1;
        else if (stay_t >= DCW_itv2) // 68 <= 剩余时间 (<101)
            hits += 2;
        else // 未知错误
            return ERR_FLG;
        return rounds * 2 + hits;
    }
    else // 地刺伤害计算
    {
        if (stay_t >= DC_h) // 接"还没开始攻击小偷就溜了"判定
            hits += 1;
        return rounds + hits;
    }
}
