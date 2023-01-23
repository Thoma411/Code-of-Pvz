#include "avz.h"
using namespace AvZ;

#define delP -95
#define norP -95
#define midP -55

void P6()
{
    selectCards({KFD_35, HBG_14, YTZD_2, WG_17, HY_16,
        HP_33, DXG_13, XPG_8, M_XPG_8, YMJNP_47});
    for (int wave = 1; wave < 20; ++wave) {
        setTime(norP, wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        if (wave % 3 == 1) {
            delay(107);
            pao_operator.pao({{1, 9}, {5, 9}});
        }
        // if (wave % 3 == 0) //*有垫测试
        // {
        //     delay(372);
        //     card({{XPG_8, 1, 9}, {M_XPG_8, 2, 9}});
        //     delay(133);
        //     shovel({{1, 9}, {2, 9}});
        // }
        if (wave == 9 || wave == 19) {
            setTime(norP + 601, wave);
            pao_operator.pao({{2, 9}, {5, 9}});
            //*挂机用
            pao_operator.recoverPao({{2, 9}, {5, 9}});
            pao_operator.recoverPao({{2, 9}, {5, 9}});
        }
    }
    setTime(97, 10);
    card({{HBG_14, 5, 7}, {KFD_35, 5, 7}});
}

void P6_N()
{
    selectCards({KFD_35, HBG_14, HMG_15, YTZD_2, HY_16,
        HP_33, DXG_13, YGG_9, XPG_8, M_XPG_8});
    for (int wave = 1; wave < 20; ++wave) {
        if (wave == 6 || wave == 15) {
            setTime(delP + 75, wave);
            card(5, {{3, 9}, {4, 9}});
            card(3, {{3, 9}, {4, 9}});
            card(1, {{3, 9}, {4, 9}});
            delay(32);
        } else {
            if (wave == 10)
                setTime(midP, wave);
            else
                setTime(delP, wave);
            pao_operator.pao({{2, 9}, {5, 9}});
            delay(107);
        }
        if (wave % 2)
            pao_operator.pao(1, 9);
        else
            pao_operator.pao(5, 9);
        if (wave == 9 || wave == 19) {
            setTime(delP + 601, wave);
            pao_operator.pao({{2, 9}, {5, 9}});
            delay(107);
            pao_operator.pao(5, 9);
            delay(601);
            //*挂机用
            pao_operator.recoverPao({{2, 9}, {5, 9}});
        }
    }
    setTime(midP + 180, 10);
    ice3(298);
    card({{HBG_14, 5, 7}, {KFD_35, 5, 7}});
}

void P6_C()
{
    selectCards({KFD_35, HBG_14, YTZD_2, HY_16, XRK_1,
        HP_33, DXG_13, YGG_9, XPG_8, M_XPG_8});
    for (int wave : {1, 4, 7, 10, 13, 16, 19}) {
        if (wave == 10) {
            setTime(midP, wave);
            pao_operator.pao({{2, 9}, {1, 9}, {5, 9}});
            delay(180);
            ice3(298);
            card({{HBG_14, 5, 7}, {KFD_35, 5, 7}});
        } else {
            setTime(-147, wave);
            pao_operator.pao(5, 9);
            setTime(delP, wave);
            pao_operator.pao(2, 9);
            delay(107);
            pao_operator.pao(1, 9);
        }
        if (wave == 19) {
            setTime(delP + 601, wave);
            pao_operator.pao({{2, 9}, {5, 9}});
            delay(107);
            pao_operator.pao(5, 9);
            //*挂机用
            delay(601);
            pao_operator.recoverPao({{1, 9}, {5, 9}});
            break;
        }

        setTime(delP, ++wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        delay(107);
        pao_operator.pao(5, 9);

        setTime(delP, ++wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        delay(372); //*-35->282 若-35发射则delay(317)施垫
        card({{XPG_8, 1, 9}, {M_XPG_8, 2, 9}});
        delay(133);
        shovel({{1, 9}, {2, 9}});
        if (wave == 9) {
            setTime(delP + 601, wave);
            pao_operator.pao({{2, 9}, {5, 9}});
            delay(107);
            pao_operator.recoverPao({{1, 9}, {5, 9}});
            //*挂机用
            delay(601);
            pao_operator.recoverPao({{1, 9}, {5, 9}});
        }
    }
}

void P6_Cplus()
{
    KeyConnect('F', [=]() { MaidCheats::dancing(); });
    KeyConnect('G', [=]() { MaidCheats::stop(); });
    selectCards({KFD_35, HBG_14, YTZD_2, HY_16, XRK_1,
        HP_33, DXG_13, YGG_9, XPG_8, M_XPG_8});
    for (int wave : {1, 4, 7, 11, 14, 17}) {
        setTime(-95, wave);
        pao_operator.pao(2, 9);
        delay(107);
        pao_operator.pao(1, 9);
        setTime(3, wave);
        pao_operator.pao(5, 9);
        setTime(192, wave);
        card({{XPG_8, 5, 9}, {M_XPG_8, 6, 9}});
        delay(90);
        shovel({{5, 9}, {6, 9}});

        setTime(-95, ++wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        delay(107);
        pao_operator.pao(5, 9);

        setTime(-147, ++wave);
        pao_operator.pao(2, 9);
        setTime(-95, wave);
        pao_operator.pao(5, 9);
        setTime(42, wave);
        card({{XPG_8, 1, 9}, {M_XPG_8, 2, 9}});
        delay(257);
        shovel({{1, 9}, {2, 9}});
        if (wave == 9 || wave == 19) {
            setTime(delP + 601, wave);
            pao_operator.pao({{2, 9}, {5, 9}});
            delay(107);
            pao_operator.recoverPao({{1, 9}, {5, 9}});
            //*挂机用
            // delay(601);
            // pao_operator.recoverPao({{1, 9}, {5, 9}});
            // pao_operator.recoverPao({{1, 9}, {5, 9}});
        }
    }
    setTime(midP, 10);
    pao_operator.pao({{2, 9}, {5, 9}});
    delay(180);
    ice3(298);
    card({{HBG_14, 5, 7}, {KFD_35, 5, 7}});
    delay(93);
    card(YTZD_2, 5, 9);
}

void S6()
{
    selectCards({KFD_35, HBG_14, M_HBG_14, YTZD_2, HY_16,
        XRK_1, HP_33, DXG_13, YGG_9, XPG_8});
    ice_filler.start({{3, 9}});
    setTime(-599, 1);
    card(HY_16, 3, 9);
    for (int wave : {1, 6, 10, 15}) { // f1
        if (wave == 10)
            setTime(midP, wave);
        else
            setTime(delP, wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        delay(107);
        pao_operator.pao(1, 9);
        // f2
        setTime(delP, ++wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        delay(107);
        pao_operator.pao(5, 9);
        // f3
        setTime(delP, ++wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        delay(107);
        pao_operator.pao(1, 9);
        // f4
        setTime(delP, ++wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        delay(107);
        pao_operator.pao(5, 9);
        if (wave == 9) {
            setTime(delP + 601, wave);
            pao_operator.pao(2, 9);
            delay(107);
            pao_operator.pao(1, 9);
            //*挂机用
            delay(201);
            pao_operator.recoverPao({{2, 9}, {5, 9}});
            pao_operator.recoverPao(5, 9);
            continue;
        } else {
            setTime(304, wave);
            ice_filler.coffee();
        }
        // f5
        setTime(-140, ++wave);
        pao_operator.pao({{1, 9}, {5, 9}});
        setTime(687, wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        if (wave == 19) {
            delay(219);
            pao_operator.recoverPao({{1, 9}, {5, 9}});
            //*挂机用
            delay(201);
            pao_operator.recoverPao({{2, 9}, {5, 9}});
            pao_operator.recoverPao({{2, 9}, {5, 9}});
        }
    }
    setTime(midP + 180, 10);
    ice3(298);
    ice_filler.coffee();

    setTime(0, 16);
    ice_filler.stop();
}

void ch6()
{
    selectCards({KFD_35, HBG_14, M_HBG_14, YTZD_2, JG_3,
        HY_16, XRK_1, HP_33, DXG_13, XPG_8});
    ice_filler.start({{2, 7}, {1, 7}});
    setTime(-599, 1);
    plant_fixer.start(XRK_1, {{5, 7}, {6, 7}});
    delay(1503);
    plant_fixer.pause();

    setTime(-95, 1);
    pao_operator.pao({{2, 9}, {5, 9}});
    for (int wave : {2, 4, 6, 8, 12, 14, 16, 18}) {
        setTime(-95, wave);
        pao_operator.pao({{2, 9}, {5, 9}});
        delay(108);
        pao_operator.pao({{1, 9}, {5, 9}});
        setTime(304, wave);
        ice_filler.coffee();
        wave++;

        setTime(-190, wave);
        pao_operator.pao({{1, 8.6}, {5, 8.6}});
        insertTimeOperation(1000, wave, [=]() {
            setInsertOperation(false);
            if (isZombieExist(XC_15, 2) && !isZombieExist(XC_15, 5))
                card(XPG_8, 2, 9);
            else
                card(XPG_8, 5, 9);
            setInsertOperation(true);
        });
        setTime(1373, wave);
        shovel({{2, 9}, {5, 9}});
        if (wave == 9 || wave == 19) {
            setTime(1048 - 373, wave);
            pao_operator.recoverPao({{2, 9}, {5, 9}});
        } else {
            setTime(1000, wave);
            pao_operator.pao({{2, 9}, {5, 9}});
        }
    }
    setTime(-55, 10);
    pao_operator.pao({{2, 9}, {5, 9}});
    delay(114);
    pao_operator.pao({{1, 9}, {5, 9}});
    setTime(304, 10);
    ice_filler.coffee();

    setTime(-190, 11);
    pao_operator.pao({{1, 8.6}, {5, 8.6}});
    setTime(1050 - 373, 11);
    pao_operator.pao({{2, 9}, {5, 9}});

    setTime(800, 17);
    ice_filler.stop();
}

void allZ()
{
    SetZombies({LZ_2, CG_3, GL_7,
        BC_12, KG_17, TL_22,
        WW_8, XC_15, FT_21,
        QS_11, HT_14,
        QQ_16, TT_18,
        BY_23, HY_32});
}
void sldZ()
{
    SetZombies({LZ_2, CG_3, BC_12, KG_17,
        WW_8, QS_11, XC_15, QQ_16,
        BY_23, HY_32});
}
void sglZ() { SetZombies({BY_23, HY_32}); }

void Script()
{
    // sglZ();
    // allZ();
    // sldZ();
    // P6
    // for (int wave = 1; wave < 19; ++wave)
    //     if (wave != 9)
    //         setWaveLength({{wave, 601}});
    // S6
    // for (int wave = 1; wave < 19; ++wave)
    //     if (wave != 9)
    //         if (wave == 5 || wave == 14 || wave == 19)
    //             setWaveLength({{wave, 1260}});
    //         else
    //             setWaveLength({{wave, 601}});

    // setGameSpeed(5);
    // SkipTick(0, 20);
    // openMultipleEffective('Q', AvZ::MAIN_UI_OR_FIGHT_UI);
    pao_operator.resetPaoList({{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1},
        {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5},
        {3, 3}, {4, 3}, {3, 7}, {4, 7}});
    // KeyConnect('C', [=]() { setGameSpeed(1); });
    // KeyConnect('V', [=]() { setGameSpeed(2); });
    // KeyConnect('B', [=]() { setGameSpeed(10); });
    // KeyConnect('C', [=]() { card(XPG_8, mouseRow(), mouseCol()); });
    // KeyConnect('V', [=]() { card(M_XPG_8, mouseRow(), mouseCol()); });
    KeyConnect('B', [=]() { pao_operator.recoverPao(2, 8.5); });
    KeyConnect('N', [=]() { pao_operator.recoverPao(5, 8.5); });
    
    /*
    choose the method you want.
    */
    
    setTime(-150, 20);
    pao_operator.pao(4, 7.5875);

    setTime(midP, 20);
    pao_operator.pao({{2, 9}, {5, 9}});
    delay(107);
    pao_operator.pao({{1, 9}, {5, 9}});
    delay(176);
    pao_operator.pao({{1, 6.0625}, {5, 6.0625}});
    delay(30);
    pao_operator.pao({{1, 1}, {5, 1}});
    pao_operator.recoverPao({{2, 8.5}, {5, 8.5}});
    //*挂机用
    // delay(300);
    // pao_operator.recoverPao({{2, 9}, {5, 9}});
}
