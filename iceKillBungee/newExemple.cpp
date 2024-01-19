/*
 * @Author: Thoma411
 * @Date: 2023-11-13 17:32:45
 * @LastEditTime: 2024-01-19 19:44:22
 * @Description: new samples and tests
 */
#include "interlayer.h"

extern map<int, int> cntArr;

// test1a: 双曾冰杀偷其一
int newTest1a()
{
    int hts = 0;
    hts += TEST_YYG(FREEZE, TARGET);
    hts += TEST_YYG(FREEZE);
    return hts;
}

// test1b: 同1a, 但写法更简单粗暴
int newTest1b()
{
    return TEST_YYG(FREEZE, TARGET) + TEST_YYG(FREEZE);
}

// test2: 六(静)曾原速偷其一
int newTest2()
{
    int hts = 0;
    hts += TEST_YYG(!FREEZE, TARGET);
    hts += TEST_YYG(!FREEZE);
    hts += TEST_YYG(!FREEZE);
    hts += TEST_YYG(!FREEZE);
    hts += TEST_YYG(!FREEZE);
    hts += TEST_YYG(!FREEZE);
    return hts;
}

// test3: 1曾2喷偷曾
int newTest3()
{
    int hts = TEST_YYG(FREEZE, TARGET);
    hts += TEST_DPG(FREEZE);
    hts += TEST_DPG(FREEZE);
    return hts;
}

void ctest(bool isFreeze, int N, bool detail = true)
{
    clock_t test_start, test_finish;
    double total_time = 0; // 模拟测试总时长(计算部分)
    test_start = clock();

    for (int i = 0; i < N; i++)
        //*新建模拟测试需改写此处参数
        statistic_rnd(newTest3());

    if (detail)
        for (const auto &pair : cntArr) // 输出每个随机数及其出现次数
            cout << "rnd: " << pair.first << " times: " << pair.second << endl;
    int fail = 0;
    if (isFreeze) //*若用冰,则IO总伤害<=21为失败; 否则<=22
        fail = cmpLeq(21);
    else
        fail = cmpLeq(22);
    double perct = double(fail) / double(N);

    test_finish = clock();
    total_time = (double)(test_finish - test_start) / CLOCKS_PER_SEC; // 统计n次测试总用时
    printf("N = %d\tfail = %d\tP = %lf\ntotal time: %lf (s)\n", N, fail, perct, total_time);
}

int main(int argc, char *argv[])
{
    //! 若要引用此结果作为概率, 请务必注意检查传入的第一个参数是否指定用冰(FREEZE)(第二个参数照抄即可)!!!
    //* 执行: .\run.bat [测试次数(不填默认为1M)]
    //* e.g. .\run.bat 10000000 (模拟测试10M次)
    ctest(!FREEZE, atoi(argv[1]));
}
