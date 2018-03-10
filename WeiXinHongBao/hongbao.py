#encoding utf-8

def getMoney():
    mny = input("input the money: \n")
    if mny - int(mny) >= 1e-10:
        print "please reinput the money and the int !"
        return getMoney()
    else:
        return mny


def getNum():
    num = input("input the num: \n")
    if num - int(num) >= 1e-10:
        print "please reinput and the int!"
        return getNum()
    else:
        return num

def getLucky():
    lucky_string = input("input the lucky num use ',' to split the num")
    luckys = list(lucky_string)
    luckys.sort(reverse=1)
    return luckys

def Basic_search(before_sum,now_step,all_step):
    if before_sum + (all_step - now_step)*luckys[-1] > money:
        return False,[]
    elif before_sum + (all_step - now_step)*luckys[0] < money:
        return False,[]
    elif now_step == all_step and abs(before_sum - money) > 1e-10:
        return False,[]
    elif all_step == now_step and abs(before_sum - money) < 1e-10:
        return True ,[]
    else:
        for mny in luckys:
            sucess, hongbaos = search(before_sum+mny,now_step+1,all_step)
            if sucess:
                hongbaos.append(mny)
                return True, hongbaos
        return False,[]

def binary_search(lucky_index, before_num, )


if __name__ == "__main__":

    """
    we think the lucky num have a ruler for example 
    """

    money = getMoney()
    num = getNum()
    luckys = getLucky()
    hongbaos = []
    sucess, hongbaos = Basic_search(0,0,num)
    print hongbaos
    
    """
    as I see this problem can only be solved by search
    but the problem is too complex, to solve this problem efficently we can use Heuristic alogrithm
    """




