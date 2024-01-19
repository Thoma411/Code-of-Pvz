/*
 * @Author: Thoma411
 * @Date: 2024-01-07 22:10:24
 * @LastEditTime: 2024-01-19 18:17:09
 * @Description:
 */
#include "interlayer.h"

int JDG_TIME(bool isFreeze, bool isTarget)
{
    // TODO:二冰需要另行智能推断
    int stay_t;
    if (isFreeze && isTarget) // 冰冻&被抓
        stay_t = getRnd(699, 899);
    else if (!isFreeze && isTarget) // 原速&被抓
        stay_t = 300;
    else if (isFreeze && !isTarget) // 冰冻&没被抓
        stay_t = getRnd(824, 1024);
    else if (!isFreeze && !isTarget) // 原速&没被抓
        stay_t = 363;
    else
        stay_t = ERR_FLG;
    return stay_t;
}

int TEST_YYG(bool isFreeze, bool isTarget, bool isWork)
{
    int stay_t = JDG_TIME(isFreeze, isTarget);
    int hits = CHT_YYG(getRnd(1, 200), stay_t, isWork);
    return hits;
}

int TEST_DPG(bool isFreeze, bool isTarget, bool isWork)
{
    int stay_t = JDG_TIME(isFreeze, isTarget);
    int hits = CHT_DPG(getRnd(1, 150), stay_t, isWork);
    return hits;
}

int TEST_BG(bool isFreeze, bool isCling, bool isTarget, bool isWork)
{
    int ice_t = -1, stay_t = JDG_TIME(isFreeze, isTarget);
    if (isFreeze) // 若用冰
        ice_t = getRnd(1, 300);
    int hits = CHT_BG(getRnd(1, 300), stay_t, ice_t, isCling, isWork);
    return hits;
}

int TEST_DC(bool isFreeze, bool isDCW, bool isWork)
{
    int stay_t = JDG_TIME(isFreeze, TARGET);
    int hits = CHT_DC(stay_t, isDCW, isWork);
    return hits;
}

int CHT_BG_tmp(int beg_t, int stay_t, int ice_t, bool cling, bool tgt, bool p_stat)
{
    int hits = 0, clg_t = 35; // 攻击次数&贴脸/远离状态下的命中时机
    //*先做可行性判断
    if (!cling) // 远离
        clg_t = 144;

    int fh_t = stay_t - beg_t - clg_t; //? first_hit_time(首次攻击时间) 动冰瓜是否适用
    //*fh_t < 0说明攻击时间晚于蹦极上升时间

    //*1.动静&完整性判定
    if (!p_stat) // *静冰瓜首轮判定
    {
        if (fh_t < 0) // 等价于stay_t - beg_t < clg_t
            return 0; // 还没开始攻击小偷就溜了
    }
    else // *动冰瓜首轮判定(不用冰时贴脸动瓜不论是否被抓一定会命中至少一次,但远离就不一定了)
        hits = QAJ_BG(beg_t, clg_t);

    //*2.状态&冰时长修正(判定)
    if (ice_t == -1) // 不用冰
    {
        if (tgt)          // *被抓
            stay_t = 300; // 修正stay_t为300
        else              // *不被抓
        {
            if (fh_t < stay_t) // *冰瓜命中先于蹦极抓取
                stay_t = 425;
            else                                    // fh_t > stay_t
                stay_t = 425 - (fh_t - stay_t) - 1; //!
        }
    }
    else if (ice_t >= 1 && ice_t <= 300) // 用冰
    {
        if (fh_t < ice_t)  // *冰瓜命中先于冰生效
            stay_t -= 100; // 二冰
        else
            ; // (默认)一冰
    }
    else
        ; // 输入非法

    //*3.伤害计算
    stay_t -= beg_t; // 去掉首轮(因为动静判定的"动"算了伤害, 而"静"没有伤害) 从下一轮开始用while判断hits次数

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
