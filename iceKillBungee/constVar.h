/*
 * @Author: Thoma411
 * @Date: 2023-10-23 19:22:12
 * @LastEditTime: 2024-01-07 21:15:19
 * @Description:
 */
#ifndef _CONSTVAR_H_
#define _CONSTVAR_H_

// 植物状态标志(初值任意)
const int TGT_NI = 301;  // target_noIce
const int TGT_BF1 = 311; // target_base_freeze_once
const int TGT_BF2 = 312; // target_base_freeze_twice

const int NTG_NIO = 501; // not_target_noIce_ori
const int NTG_NIS = 502; // not_target_noIce_slow
const int NTG_BF1 = 511; // not_target_base_freeze_once
const int NTG_BF2 = 512; // not_target_base_freeze_twice

const int ERR_FLG = -999; // 未知错误

const int hitt_HP = 23; // 蹦极HP=450, /20上取整为23

const int baseTime = 300;    // 原速滞留时间/目标可攻击时间
const int freezeTime1 = 399; // 一次冰冻时间
const int freezeTime2 = 299; // 二次冰冻时间
const int baseCatch = 63;    // 原速抓取时间
const int freezeCatch = 125; // 减速抓取时间

const int obj_ice_atkt1 = baseTime + freezeTime1; // 699目标一冰可攻击时间
const int obj_ice_atkt2 = baseTime + freezeTime2; // 599目标二冰可攻击时间

const int nobj_norm_atkt = baseTime + baseCatch;        // 363非目标原速可攻击时间
const int nobj_slow_atkt = baseTime + freezeCatch;      // 425非目标减速可攻击时间
const int nobj_ice_atkt1 = obj_ice_atkt1 + freezeCatch; // 824非目标一冰可攻击时间
const int nobj_ice_atkt2 = obj_ice_atkt2 + freezeCatch; // 724非目标二冰可攻击时间

const int YYG_rnd_min = 186, YYG_rnd_max = 200;
const int YYG_itv = 28, YYG_h1 = 74, YYG_h2 = 102, YYG_h3 = 130, YYG_h4 = 158; // 曾的每发间隔&相对命中时机(倒数)

const int DC_hitv = 101, DC_h = 25, DCW_itv1 = 30, DCW_itv2 = 38; // 地刺类攻击间隔 / 地刺/地刺王相对命中时机

#endif