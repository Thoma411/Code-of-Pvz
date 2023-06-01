'''
Author: Elovi & Crescendo
Date: 2021-04-16 12:49:39
LastEditTime: 2023-06-01 21:44:39
Description: 自用魔改版
'''

rowHeight = 85
colWidth = 80
delayMustFallen = 450
isRoof = False

windPaoDist = [[125, 124,  84],
               [125, 125, 102],
               [125, 125, 114],
               [125, 125, 121],
               [124, 125, 124],
               [124, 125, 124],
               [121, 125, 125],
               [118, 125, 125]]


def scene(pscene, oppress=False):
    global rowHeight
    global isRoof
    if pscene == 'PE' or pscene == 'FE':
        rowHeight = 85
        isRoof = False
        if not oppress:
            print('已设置场地为六行')
    elif pscene == 'DE' or pscene == 'NE':
        rowHeight = 100
        isRoof = False
        if not oppress:
            print('已设置场地为五行')
    elif pscene == 'RE' or pscene == 'ME':
        rowHeight = 85
        if not oppress:
            print('已设置场地为天台')
        isRoof = True
    else:
        if not oppress:
            print('该场地不支持.')


def IntersectCircRect(cirX, cirY, radius, rectX, rectY, rectW, rectH):
    X = rectX if cirX < rectX else (
        rectX + rectW if cirX > rectX + rectW else cirX)
    Y = rectY if cirY < rectY else (
        rectY + rectH if cirY > rectY + rectH else cirY)
    return ((cirX - X) ** 2 + (cirY - Y) ** 2) <= radius ** 2


def calcImp(xg, yg, rnd, dl, stackHigher=False, isIced=False, verbosity=1):
    if isRoof:
        return calcRoofImp(xg, yg, rnd, dl, stackHigher, isIced, verbosity)
    if (xg < 401) or (rnd != 0 and xg < 501):
        if verbosity >= 1:
            print('Invalid parameters.')
        return -1, -1, True, (-1)
    alreadyEat, earliestEatTime, damage = False, -1, 0
    earliestIceTime = -1
    eatLoop = 4 if not isIced else 8
    time = 105 if not isIced else 210
    if time > dl:
        if verbosity >= 2:
            print('Too early.')
        return -1, -1, True, (-1)
    g, vx, vy, x, y, h, state, existTime = -0.05, - \
        3, (xg - 360 - rnd)/120, xg - 133, yg, 88, 71, 0
    if stackHigher:
        vy += g
        x, h, existTime = x + vx, h + vy, existTime + 1
    while time < dl:
        if state == 71:
            vy += g
            x, h, existTime = x + vx, h + vy, existTime + 1
            time += 1
            if int(h) < 0:
                state = 72
                h = 0
                countDown = 25 if not isIced else 50
        elif state == 72:
            countDown -= 1
            existTime += 1
            time += 1
            if countDown == 0:
                state = 0
                alreadyEat = (existTime % eatLoop == 0)
                if alreadyEat:
                    earliestEatTime = time
        elif state == 0:
            existTime += 1
            time += 1
            if earliestIceTime == -1:
                earliestIceTime = time
            if existTime % eatLoop == 0:
                if not alreadyEat:
                    alreadyEat = True
                    earliestEatTime = time
                if alreadyEat:
                    damage = (time - earliestEatTime)/eatLoop * 4 + 4
                if damage >= 300:
                    if verbosity >= 2:
                        print('Damage too large.')
                    break
        else:
            if verbosity >= 1:
                print('Unexpected Error.')
            return -1, -1, True, (-1)
    return int(x), int(y - h), alreadyEat, (earliestEatTime, damage, earliestIceTime, h, eatLoop)


def calcRoofImp(xg, yg, rnd, dl, stackHigher=False, isIced=False, verbosity=1):
    if (xg < 401) or (rnd != 0 and xg < 501):
        if verbosity >= 1:
            print('Invalid paramters.')
        return -1, -1, True, (-1)
    alreadyEat, earliestEatTime, damage = False, -1, 0
    earliestIceTime = -1
    eatLoop = 4 if not isIced else 8
    time = 105 if not isIced else 210
    if time > dl:
        if verbosity >= 2:
            print('Too early.')
        return -1, -1, True, (-1)
    g, vx, vy, x, y, h, state, existTime = -0.05, - \
        3, (xg - 360 - 180 - rnd)/120, xg - 133, yg, 88, 71, 0
    if stackHigher:
        vy += g
        x, h, existTime = x + vx, h + vy, existTime + 1
        yshift = 0 if x >= 400 else (400 - x) / 4
        real_h = h + yshift
    while time < dl:
        if state == 71:
            vy += g
            x, h, existTime = x + vx, h + vy, existTime + 1
            yshift = 0 if x >= 400 else (400 - x) / 4
            real_h = h + yshift
            time += 1
            if int(real_h) < 0:
                state = 72
                h = 0
                real_h = 0
                countDown = 25 if not isIced else 50
        elif state == 72:
            countDown -= 1
            existTime += 1
            time += 1
            if countDown == 0:
                state = 0
                alreadyEat = (existTime % eatLoop == 0)
                if alreadyEat:
                    earliestEatTime = time
        elif state == 0:
            existTime += 1
            time += 1
            if earliestIceTime == -1:
                earliestIceTime = time
            if existTime % eatLoop == 0:
                if not alreadyEat:
                    alreadyEat = True
                    earliestEatTime = time
                if alreadyEat:
                    damage = (time - earliestEatTime)/eatLoop * 4 + 4
                if damage >= 300:
                    if verbosity >= 2:
                        print('Damage too large.')
                    break
        else:
            if verbosity >= 1:
                print('Unexpected Error.')
            return -1, -1, True, (-1)
    shift = 0 if x >= 400 else (400 - x)/4.0
    return int(x), int(y + shift - real_h), alreadyEat, (earliestEatTime, damage, earliestIceTime, real_h, eatLoop)


def doom(row, col):
    return col * colWidth, 120 + (row-1) * rowHeight, 250


def cob(row, col, paoCol=None, paoRow=None):
    x = int(col * colWidth)
    targetX = (x - 7) if (x >= 7) else x - 6
    if not isRoof:
        return targetX, 120 + (row-1) * rowHeight, 115
    else:
        if paoCol is None:
            print('屋顶场地需指定炮尾所在列.')
            return 0, 0, 0
        y = 209 + (row - 1) * rowHeight
        if x <= 206:
            step1 = 0
        elif x >= 527:
            step1 = 5
        else:
            step1 = (x - 127) // 80
        y -= step1 * 20
        if paoCol == 1:
            leftEdge = 87
            rightEdge = 524
            step2Shift = 0
        elif paoCol >= 7:
            leftEdge = 510
            rightEdge = 523
            step2Shift = 5
        else:
            leftEdge = 80 * paoCol - 13
            rightEdge = 524
            step2Shift = 5
        if x <= leftEdge:
            step2 = 0
        elif x >= rightEdge:
            step2 = (rightEdge - leftEdge + 3) // 4 - step2Shift
        else:
            step2 = (x - leftEdge + 3) // 4 - step2Shift
        y -= step2
        if (x == leftEdge) and (paoCol in (2, 3, 4, 5, 6)):
            if paoRow is None:
                print('特殊落点, 需要指定炮所在行.')
                return 0, 0, 0
            if paoRow in (3, 4, 5):
                y += 5
            if paoRow == 3 and paoCol == 6:
                y -= 5
        y = 0 if y < 0 else y
        return targetX, y, 115


def judge(xgInfo, dl, rows, explodeInfo, isIced=False, verbosity=1):
    count = 0
    eatCount = 0
    notInterceptCount = 0
    totalDamage = 0
    if isinstance(xgInfo, list):
        if len(xgInfo) > 1:
            xgFast, xgSlow = xgInfo
        else:
            xgFast, xgSlow = xgInfo[0], xgInfo[0]
    else:
        xgFast, xgSlow = xgInfo, xgInfo
    explodeX, explodeY, radius = explodeInfo
    for xg in range(xgFast, xgSlow+1):
        if xg <= 400:
            continue
        for rnd in range(0, 101):
            if 401 <= xg <= 500 and rnd != 0:
                continue
            for stackHeight in [True, False]:
                for row in rows:
                    count += 1
                    impX, impY, eat, _ = calcImp(
                        xg, (50 if not isRoof else 40) + (row-1) * rowHeight, rnd, dl, stackHeight, isIced, verbosity)
                    if eat:
                        eatCount += 1
                        totalDamage += _[1]
                        if (verbosity == 1 and eatCount <= 5) or verbosity >= 2:
                            print('Eat: ', end='')
                            print([xg, rnd, dl, stackHeight,
                                  row, impX, impY, eat, _])
                        elif verbosity == 1 and eatCount == 6:
                            print('...')
                    if not IntersectCircRect(explodeX, explodeY, radius, impX + 36, impY, 42, 115):
                        notInterceptCount += 1
                        if (verbosity == 1 and notInterceptCount <= 5) or verbosity >= 2:
                            print('Not Intercepted: ', end='')
                            print([xg, rnd, dl, stackHeight,
                                  row, impX, impY, eat, _])
                        elif verbosity == 1 and notInterceptCount == 6:
                            print('...')
    if verbosity >= 1:
        print(f'Eat/NotIntercept/All: {str(eatCount)}/{str(notInterceptCount)} \
                /{str(count)}; AvgDamage: {str(totalDamage / count)}')
    return notInterceptCount == 0 and eatCount == 0


def iceKill(xgInfo, rows, isIced=True, verbosity=1):
    count = 0
    xgFast, xgSlow = xgInfo
    iceTimes = []
    eatTimes = []
    for xg in range(xgFast, xgSlow+1):
        if xg <= 400:
            continue
        for rnd in range(0, 101):
            if 401 <= xg <= 500 and rnd != 0:
                continue
            for stackHeight in [True, False]:
                for row in rows:
                    count += 1
                    impX, impY, eat, _ = calcImp(
                        xg, 50 + (row-1) * rowHeight, rnd, delayMustFallen, stackHeight, isIced, verbosity)
                    assert eat
                    eatTimes.append(_[0])
                    iceTimes.append(_[2])
    earliestIceTime = max(iceTimes)
    eatLoop = 8 if isIced else 4
    totalDamage = (earliestIceTime * count - sum(eatTimes)) / \
        eatLoop * 4 + count * 4
    avgDamege = totalDamage / count
    if verbosity >= 1:
        print(
            f'IceTime: {str(earliestIceTime)}; All: {str(count)}; AvgDamage: {str(avgDamege)}')
    return earliestIceTime


def findMaxDelay(xRange, rows, pR, paoCol, isIced=False, step=5, roofPaoCol=None):
    if isRoof and roofPaoCol == None:
        print('屋顶场地需要指定炮尾所在列')
        return -1
    xgInfo = []
    if not isinstance(xRange, list):
        xgInfo.append(xRange)
    else:
        xgInfo = xRange[:2]
    xgRows = []
    if not isinstance(rows, list):
        xgRows.append(rows)
    else:
        xgRows = rows
    paoRow = 0
    if isinstance(pR, list):
        paoRow = pR[0]
    else:
        paoRow = pR
    if step <= 0:
        raise Exception()
    dl = 106 if not isIced else 211
    paoLo, paoHi = paoCol
    paoLo = int(paoLo * 80)
    paoHi = int(paoHi * 80)
    resultDelay = -1
    resultX = -1
    paoX = paoLo
    while paoX <= paoHi:
        maxDelay = -1
        start = -1
        for d in range(dl, dl + 100):
            if judge(xgInfo[0], d, xgRows, cob(paoRow, paoX / 80.0, roofPaoCol), isIced, 0) \
                    and (len(xgInfo) == 1 or judge(xgInfo[1], d, xgRows, cob(paoRow, paoX / 80.0, roofPaoCol), isIced, 0)):
                start = d
                break
        if start != -1:
            for d in range(start + 1, start + 100):
                if not judge(xgInfo[0], d, xgRows, cob(paoRow, paoX / 80.0, roofPaoCol), isIced, 0) or \
                        (len(xgInfo) > 1 and not judge(xgInfo[1], d, xgRows, cob(paoRow, paoX / 80.0, roofPaoCol), isIced, 0)):
                    maxDelay = d - 1
                    break
        if maxDelay > resultDelay:
            resultDelay = maxDelay
            resultX = paoX
        paoX += step
    print('最大延迟:', resultDelay)
    print('落点:', str(resultX / 80.0) + '列')
    return resultDelay, resultX / 80.0


def delay(xRange, rows, paoInfo, isIced=False, exact=False):
    xgInfo = []
    if not isinstance(xRange, list):
        xgInfo.append(xRange)
    else:
        xgInfo = xRange[:2]
    return minDelay(xgInfo, rows, paoInfo, isIced, exact), maxDelay(xgInfo, rows, paoInfo, isIced, exact)


def maxDelay(xRange, rows, paoInfo, isIced=False, exact=False):
    xgInfo = []
    if not isinstance(xRange, list):
        xgInfo.append(xRange)
    else:
        xgInfo = xRange[:2]
    if exact and len(xgInfo) == 1:
        xgInfo.append(xgInfo[0])
    xgRows = []
    if not isinstance(rows, list):
        xgRows.append(rows)
    else:
        xgRows = rows
    x, _, rd = paoInfo
    dl = 106 if not isIced else 211
    if x <= 400 and rd <= 115 and not exact and xgInfo[0] >= 600:
        dl += 80
    upper = dl + 200
    if rd <= 115 and not exact:
        upper = dl + 120
    found = False
    for d in range(dl, upper):
        if not exact:
            if not judge(xgInfo[0], d, xgRows, paoInfo, isIced, 0) or\
                    (len(xgInfo) > 1 and not judge(xgInfo[1], d, xgRows, paoInfo, isIced, 0)):
                if found:
                    print(f'最大延迟: {d - 1} ({str(dl)}~{str(upper)})')
                    return d - 1
            else:
                found = True
        else:
            if not judge([xgInfo[0], xgInfo[1]], d, xgRows, paoInfo, isIced, 0):
                if found:
                    print(f'最大延迟(精确): {d - 1} ({str(dl)}~{str(upper)})')
                    return d - 1
            else:
                found = True
    if not exact:
        if not found:
            print(f'最大延迟: 全部失败 ({str(dl)}~{str(upper)})')
        else:
            print(f'最大延迟: 全部成功 ({str(dl)}~{str(upper)})')
    else:
        if not found:
            print(f'最大延迟(精确): 全部失败 ({str(dl)}~{str(upper)})')
        else:
            print(f'最大延迟(精确): 全部成功 ({str(dl)}~{str(upper)})')

    return dl + 99


def minDelay(xRange, rows, paoInfo, isIced=False, exact=False):
    xgInfo = []
    if not isinstance(xRange, list):
        xgInfo.append(xRange)
    else:
        xgInfo = xRange[:2]
    if exact and len(xgInfo) == 1:
        xgInfo.append(xgInfo[0])
    xgRows = []
    if not isinstance(rows, list):
        xgRows.append(rows)
    else:
        xgRows = rows
    x, _, rd = paoInfo
    dl = 106 if not isIced else 211
    if x <= 400 and rd <= 115 and not exact and xgInfo[0] >= 600:
        dl += 80
    upper = dl+200
    if rd <= 115 and not exact:
        upper = dl+100
    for d in range(dl, upper):
        if not exact:
            if judge(xgInfo[0], d, xgRows, paoInfo, isIced, 0) and \
                    (len(xgInfo) == 1 or judge(xgInfo[1], d, xgRows, paoInfo, isIced, 0)):
                print(f'最小延迟: {d} ({str(dl)}~{str(upper)})')
                return d
        else:
            if judge([xgInfo[0], xgInfo[1]], d, xgRows, paoInfo, isIced, 0):
                print(f'最小延迟(精确): {d} ({str(dl)}~{str(upper)})')
                return d
    if not exact:
        print(f'最小延迟: 全部失败 ({str(dl)}~{str(upper)})')
    else:
        print(f'最小延迟(精确): 全部失败 ({str(dl)}~{str(upper)})')
    return -1


gargFast = []
gargSlow = []
with open('gargFast.txt', 'r') as ff:
    for posf in ff:
        gargFast.append(float(posf.strip()))
with open('gargSlow.txt', 'r') as fs:
    for poss in fs:
        gargSlow.append(float(poss.strip()))


def getGargPos(walkTime):
    fastTime, slowTime = walkTime
    return [int(845 - gargFast[int(fastTime)]), int(854 - gargSlow[int(slowTime)])]


def pos(iT, paoTime):
    iceTime = []
    if not isinstance(iT, list):
        iceTime.append(iT)
    else:
        iceTime = iT
    iceTime.sort()
    for t in iceTime:
        if t <= 0:
            iceTime.remove(t)
        elif t > paoTime:
            raise Exception()
    if len(iceTime) == 0:
        walkTime = [paoTime, paoTime]
    else:
        slowTotal = 0
        fastTotal = 0
        lastTick = -1
        doubleIce = False
        iceTime.append(paoTime)
        for t in iceTime:
            if lastTick == -1:
                slowTotal += t
                fastTotal += t
            else:
                diff = t - lastTick
                if diff <= 2000:
                    slowTotal += max(diff -
                                     (600 if not doubleIce else 400), 0) / 2.0
                    fastTotal += max(diff -
                                     (400 if not doubleIce else 300), 0) / 2.0
                else:
                    slowTotal += (2000 - (600 if not doubleIce else 400)
                                  )/2.0 + diff - 2000
                    fastTotal += (2000 - (400 if not doubleIce else 300)
                                  )/2.0 + diff - 2000
                doubleIce = True if diff <= 2000 else False
            lastTick = t
            print(slowTotal, fastTotal)
        walkTime = [int(fastTotal), int(slowTotal)]
    print(getGargPos(walkTime))
    print('''巨人举锤坐标参考: 
8普通 - 680
8炮 - 670
7普通 - 600
7炮 - 590
6普通 - 520
6炮 - 510
(高坚果为普通+20, 南瓜则再+10)''')
    return getGargPos(walkTime)


def walk(wt=None):
    if wt != None:
        walkTime = []
        if not isinstance(wt, list):
            walkTime.append(wt)
        else:
            walkTime = wt
        fast = 845
        slow = 854
        for w in walkTime:
            fast -= gargFast[int(w)]
            slow -= gargSlow[int(w)]
        print([int(fast), int(slow)])
    print('''巨人举锤坐标参考: 
8普通 - 680
8炮 - 670
7普通 - 600
7炮 - 590
6普通 - 520
6炮 - 510
(高坚果为普通+20, 南瓜则再+10)''')
    if wt != None:
        return [int(fast), int(slow)]
    else:
        return None


def icm_main():
    print('欢迎使用拦截计算器 by Elovi, Crescendo\n当前场景: PE\n输入helpfull查看帮助.')
    print('计算结果默认为[植物激活→炮拦截]的情况. 若为[炮激活→炮拦截], 需额外+1; 若为[炮激活→植物拦截], 需额外+2.')
    scene('PE', True)
    iceTime = 0
    paoTime = 278
    walkTime = [278, 278]
    while True:
        print()
        print('>>', end=' ')
        line = input()
        try:
            if line == 'q' or line == 'exit' or line == 'quit':
                break
            elif line == 'help':
                print('''====================
    基础指令: 
        DE/PE/RE                - 设置场景
        w/wave                    - 查看当前波长, 并显示巨人坐标范围
        w/wave [冰时机] [激活时机] - 设置冰时机、激活时机(冰时机可不填)
        hit (炮列数)              - 求正好全伤的落点
        nohit (炮列数)            - 求正好不伤的落点
        hit (炮列数) [延迟]       - 求延迟炮正好全伤的落点
        nohit (炮列数) [延迟]     - 求延迟炮正好不伤的落点
        delay (炮列数) [落点] [拦截行数] - 求最早、最晚拦截(尾炸)时机
            --程序会智能推测行数. 默认前院/天台尾炸三行, 后院尾炸两行. 若不符, 可自行输入拦截行数.
            --风炮需指定炮尾所在列

    其他: 
        help        - 查看帮助
        hf/helpfull    - 查看详细帮助
        v/version     - 查看版本
        q/quit/exit   - 退出
    ====================''')
            elif line == 'hf' or line == 'helpfull':
                print('''====================
    基础指令: 
        DE/PE/RE                - 设置场景
        w/wave                    - 查看当前波长, 并显示巨人坐标范围
        w/wave [冰时机] [激活时机] - 设置冰时机、激活时机(冰时机可不填)
        hit (炮列数)              - 求正好全伤的落点(风炮需指定炮尾所在列)
        nohit (炮列数)            - 求正好不伤的落点(风炮需指定炮尾所在列)
        hit (炮列数) [延迟]       - 求延迟炮正好全伤的落点(风炮需指定炮尾所在列)
        nohit (炮列数) [延迟]     - 求延迟炮正好不伤的落点(风炮需指定炮尾所在列)
        delay (炮列数) [落点] [拦截行数] - 求最早、最晚拦截(尾炸)时机
            --程序会智能推测行数. 默认前院/天台尾炸三行, 后院尾炸两行. 若不符, 可自行输入拦截行数.
            --风炮需指定炮尾所在列

    高级指令: 
        doom(r, c) - 表示用r行c列的核弹
        cob(r, c, (paoCol, paoRow))  - 表示发炮落点r行c列
            --屋顶场地需指定炮尾所在列; 特殊落点需要指定炮所在行

        delay(xgInfo, rows, explodeInfo, isIced=False, exact=False) - 求最早/最晚拦截时机
            --为简化计算, 计算时只考虑最左、最右巨人
            --可以单独使用minDelay或maxDelay; xgInfo接受单数也接受范围
                --例如, minDelay(806, [1, 2, 5, 6], doom(3, 3)) 表示1、2、5、6路原速巨人x坐标806, 3-3核武最早何时能尾炸; delay([788, 806], [1, 2, 5, 6], doom(3, 3))则可以求出最早和最晚时机
            --如果认为结果有问题, 请尝试将exact设为True(开销较大); 程序会遍历每个坐标的巨人并分别计算

        pos(iceTime, paoTime) - 输入冰时机、激活时机, 求巨人坐标范围
            --可以输入多个冰时机, paoTime也可以大于2300.

        walk([walkTime1, walkTime2, ...]) - 输入行走时间, 求巨人坐标范围(支持输入多段)
            --巨人举锤/投掷后相位会重置(受冰不会), 需分多段输入.

        findMaxDelay(xgInfo, xgRows, dropRow, dropColRange, isIced=False, step=5, paoCol=None) - 求最大可能延迟的拦截落点(开销较大)
            --例如, findMaxDelay([788, 817], [2], 1, [8, 8.5]) 表示2路原速巨人x坐标范围[788~817], 炮落点1路[8~8.5]列, 每5个px遍历一次, 寻找最大可能延迟的拦截落点.
            --屋顶场地需指定炮尾所在列

    原生函数: 
        judge(xgInfo, delay, xgRows, explodeInfo, isIced=False, verbosity=1) - 拦截计算
            --例如, judge([788, 817], 107, [1, 2, 5, 6], doom(3, 9)) 表示原速巨人x坐标范围[788~817], 延时107, 只考虑1256行巨人, 使用3-9核弹, 计算是否可以全部拦截. 因为可以全部拦截, 故输出 True, [].

        iceKill(xgInfo, xgRows, isIced=True, verbosity=1) - 冰杀小鬼计算
            --例如, iceKill([734, 789], [3], True) 表示减速巨人x坐标范围[724~789], 只考虑3路巨人(实际上每一路都一样), 计算冰冻全部小鬼的最早时机.
            --judge和iceKill都会给出一个AvgDamege, 但这仅为平均值, 实际伤害概率分布并不为此, 仅可作为参考, 不可视为伤害的期望值.

        calcImp(xg, yg, rnd, dl, stackHigher=False, isIced=False, verbosity=1) - 小鬼坐标计算
            --例如, calcImp(700,50,100,400) 表示求x=700的一列(y=50)巨人以最小力气扔出小鬼(rnd=100), 延迟400后小鬼的坐标, 以及是否受冰和开始啃食等.
            --输出的参数依次是小鬼的x与y坐标, 是否开始啃食, (最早啃食时间, 啃食伤害, 最早可受冰时间, 高度, 啃食结算周期)

        注意: 原生函数需要结合print()使用.

    其他: 
        help        - 查看帮助
        hf/helpfull    - 查看详细帮助
        v/version     - 查看版本
        q/quit/exit   - 退出
    ====================''')
            elif line in ['DE', 'NE', 'PE', 'FE', 'RE', 'ME', 'de', 'ne', 'pe', 'fe', 're', 'me']:
                scene(line.upper())
            elif line.startswith('w'):
                params = line.split()
                if len(params) == 1:
                    print('当前设置:', '不用冰' if iceTime <= 0 else str(
                        iceTime) + '冰', str(paoTime) + '激活')
                    print('巨人坐标范围:', getGargPos(walkTime))
                elif len(params) == 2:
                    if int(params[1]) >= 2300:
                        print('意外的输入. 激活时机太晚.')
                        continue
                    if int(params[1]) <= 0:
                        print('意外的输入. 激活时机太早.')
                        continue
                    iceTime = 0
                    paoTime = int(params[1])
                    walkTime = [paoTime, paoTime]
                    if paoTime <= 224:
                        print('警告: 此时机无法全伤巨人.')
                    print('修改完毕. 当前设置:', '不用冰' if iceTime <=
                          0 else str(iceTime) + '冰', str(paoTime) + '激活')
                    print('巨人坐标范围:', getGargPos(walkTime))
                elif len(params) >= 3:
                    if int(params[1]) > 0:
                        if int(params[1]) >= int(params[2]):
                            print('意外的输入. 激活时机不能早于冰时机.')
                            continue
                        if int(params[2]) >= 3500:
                            print('意外的输入. 激活时机太晚.')
                            continue
                    if int(params[2]) <= 0:
                        print('意外的输入. 激活时机太早.')
                        continue
                    iceTime = int(params[1])
                    paoTime = int(params[2])
                    if iceTime <= 0:
                        if paoTime <= 224:
                            print('警告: 此时机无法全伤巨人.')
                    elif iceTime + paoTime < 1049:
                        print('警告: 此时机无法全伤巨人.')
                    if iceTime <= 0:
                        walkTime = [paoTime, paoTime]
                    else:
                        if paoTime <= iceTime + 400:
                            walkTime = [iceTime, iceTime]
                        elif paoTime <= iceTime + 600:
                            walkTime = [iceTime + int((paoTime - 400 - iceTime) / 2),
                                        iceTime]
                        elif paoTime <= iceTime + 2000:
                            walkTime = [iceTime + int((paoTime - 400 - iceTime) / 2),
                                        iceTime + int((paoTime - 600 - iceTime) / 2)]
                        else:
                            walkTime = [iceTime + 800 + int(paoTime - iceTime - 2000),
                                        iceTime + 700 + int(paoTime - iceTime - 2000)]
                    print('修改完毕. 当前设置:', '不用冰' if iceTime <=
                          0 else str(iceTime)+'冰', str(paoTime)+'激活')
                    print('巨人坐标范围:', getGargPos(walkTime))
            elif line.startswith('hit'):
                params = line.split()
                if isRoof:
                    if len(params) < 2:
                        print('意外的输入. 屋顶场地需要指定炮尾所在列.')
                        continue
                    paoCol = int(params[1])
                    if paoCol < 1 or paoCol > 8:
                        print('意外的输入. 炮尾所在列只能输入1~8.')
                        continue
                if (isRoof and len(params) >= 3) or (not isRoof and len(params) >= 2):
                    extra = int(params[2]) if isRoof else int(params[1])
                    if extra <= 0:
                        print('意外的输入. 延迟必须为正数.')
                        continue
                    if extra + paoTime >= 2300:
                        print('意外的输入. 延迟太长.')
                        continue
                    if iceTime <= 0:
                        delayedWalkTime = [paoTime + extra, paoTime + extra]
                    else:
                        delayedWalkTime = [iceTime + int((paoTime + extra - 400 - iceTime)/2),
                                           iceTime + int((paoTime + extra - 600 - iceTime)/2)]
                    print('延迟炮生效时机:', extra + paoTime)
                else:
                    delayedWalkTime = walkTime
                if isRoof:
                    dist = windPaoDist[paoCol - 1]
                else:
                    dist = [118, 125] if rowHeight == 85 else [111, 125]
                gargPos = getGargPos(delayedWalkTime)
                print(f'巨人坐标范围: {str(gargPos)}')
                if not isRoof:
                    print('全伤本行&下行: {} ({}列)'.format(
                        str(gargPos[1]-dist[1]), str((gargPos[1]-dist[1])/80.0)))
                    print('全伤三行: {} ({}列)'.format(
                        str(gargPos[1]-dist[0]), str((gargPos[1]-dist[0])/80.0)))
                else:
                    print('全伤上行: {} ({}列)'.format(
                        str(gargPos[1]-dist[0]), str((gargPos[1]-dist[0])/80.0)))
                    print('全伤本行: {} ({}列)'.format(
                        str(gargPos[1]-dist[1]), str((gargPos[1]-dist[1])/80.0)))
                    print('全伤下行: {} ({}列)'.format(
                        str(gargPos[1]-dist[2]), str((gargPos[1]-dist[2])/80.0)))
            elif line.startswith('nohit'):
                params = line.split()
                if isRoof:
                    if len(params) < 2:
                        print('意外的输入. 屋顶场地需要指定炮尾所在列.')
                        continue
                    paoCol = int(params[1])
                    if paoCol < 1 or paoCol > 8:
                        print('意外的输入. 炮尾所在列只能输入1~8.')
                        continue
                if (isRoof and len(params) >= 3) or (not isRoof and len(params) >= 2):
                    extra = int(params[2]) if isRoof else int(params[1])
                    if extra <= 0:
                        print('意外的输入. 延迟必须为正数.')
                        continue
                    if extra + paoTime >= 2300:
                        print('意外的输入. 延迟太长.')
                        continue
                    if iceTime <= 0:
                        delayedWalkTime = [paoTime + extra, paoTime + extra]
                    else:
                        delayedWalkTime = [
                            iceTime + int((paoTime + extra - 400 - iceTime)/2), iceTime + int((paoTime + extra - 600 - iceTime)/2)]
                    print('延迟炮生效时机:', extra + paoTime)
                else:
                    delayedWalkTime = walkTime
                if isRoof:
                    dist = windPaoDist[paoCol - 1]
                else:
                    dist = [118, 125] if rowHeight == 85 else [111, 125]
                gargPos = getGargPos(delayedWalkTime)
                print('巨人坐标范围:', str(gargPos))
                if not isRoof:
                    print('不伤本行&下行: {} ({}列)'.format(
                        str(gargPos[0]-dist[1]-1), str((gargPos[0]-dist[1]-1)/80.0)))
                    print('不伤上行: {} ({}列)'.format(
                        str(gargPos[0]-dist[0]-1), str((gargPos[0]-dist[0]-1)/80.0)))
                else:
                    print('不伤上行: {} ({}列)'.format(
                        str(gargPos[0]-dist[0]-1), str((gargPos[0]-dist[0]-1)/80.0)))
                    print('不伤本行: {} ({}列)'.format(
                        str(gargPos[0]-dist[1]-1), str((gargPos[0]-dist[1]-1)/80.0)))
                    print('不伤下行: {} ({}列)'.format(
                        str(gargPos[0]-dist[2]-1), str((gargPos[0]-dist[2]-1)/80.0)))
            elif line.startswith('delay '):
                params = line.split()
                paoCol = None
                if isRoof:
                    if len(params) <= 2:
                        print('意外的输入. 屋顶场地需要指定炮尾所在列.')
                        continue
                    paoCol = int(params[1])
                    if paoCol < 1 or paoCol > 8:
                        print('意外的输入. 炮尾所在列只能输入1~8.')
                        continue
                    params.pop(1)
                if len(params) == 1:
                    print('意外的输入. 需要指定落点.')
                    continue
                if len(params) >= 2:
                    paoX = float(params[1])
                    if paoX < 0 or paoX >= 10:
                        print('意外的输入. 落点超出有效范围(0-9列).')
                        continue
                    if len(params) >= 3:
                        rows = int(params[2])
                        if not rows in [2, 3]:
                            print('意外的输入. 拦截行数应为2或3.')
                            continue
                    else:
                        if not isRoof:
                            rows = 3 if rowHeight == 100 and paoX <= 5 else 2
                        else:
                            if paoX <= 5:
                                rows = 3
                            elif paoCol <= 4:
                                rows = 3
                            else:
                                rows = 2
                    isIced = True if iceTime > 0 and paoTime <= iceTime + 2000 else False
                    paoRow = 3
                    xgRow = [2, 3, 4] if rows == 3 else [3, 4]
                    gargPos = getGargPos(walkTime)
                    delay(gargPos, xgRow, cob(paoRow, paoX, paoCol), isIced)
            elif line == 'v' or line == 'version':
                print(
                    'BrainVsZombies General Interception Calculator ver 1.1 by Elovi, Crescendo')
            else:
                eval(line)
        except:
            print('意外的输入. 输入help查看帮助.')

# pyinstaller -F interception_calculator.py


if __name__ == '__main__':
    icm_main()
