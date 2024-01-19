/*
 * @Author: Thoma411
 * @Date: 2024-01-07 22:08:28
 * @LastEditTime: 2024-01-08 17:44:54
 * @Description: 中间层
 */
#ifndef _INTERLAYER_H_
#define _INTERLAYER_H_

#include "ialgo.h"

#define FREEZE true
#define TARGET true
#define ALWORK true // always_work
#define SPKROC true // is_spikerock

/*
 *封装植物类
 *(由于不同植物特性不同,
 *不可能把所有植物都封进一个TEST函数中,
 *但可以为每种植物创一个struct,然后把TEST函数分为几个大类)
 ?后续可以考虑把每种植物的CHT函数纳入对应struct的成员函数
 */
struct GL_SHROOM
{
    int itv_min = 186, itv_max = 200;
};

struct SHOOTER
{
    int itv_min = 136, itv_max = 150;
};

struct PULT
{
    int itv_min = 286, itv_max = 300;
};

int JDG_TIME(bool isFreeze, bool isTarget); // 根据状态判断时间

//*测试封装函数集, 对下列函数, 调一次加一个对应的植物
int TEST_YYG(bool isFreeze, bool isTarget = false, bool isWork = false);
int TEST_DPG(bool isFreeze, bool isTarget = false, bool isWork = false);
int TEST_BG(bool isFreeze, bool isCling, bool isTarget = false, bool isWork = true);
int TEST_DC(bool isFreeze, bool isDCW = true, bool isWork = false); // 地刺默认为目标

#endif