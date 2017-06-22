#include "PokerRule.h"

/*
PokerRuleError = -1,				//-1 不符合出牌规则
PokerRuleDoubleKing,				//0. 大小王两张最大
PokerRuleSingle,					//1.单张：大小顺序
PokerRuleDouble,					//2.一对：大小顺序
PokerRuleTrouble,				//3.三张：大小顺序
PokerRuleLine,					//4.顺子：（5张）（相同大小比最大）
PokerRuleDoubleLine,				//5.双顺：（3连对）（相同大小比最大 ）
PokerRuleTroubleWithSingle,		//6.三带一张单牌
PokerRuleTroubleWithDouble,		//7.三带一对
PokerRuleUltraWithTwoSingle,		//8.四带二张单牌
PokerRuleUltraWithTwoDouble		//9.四带两队
PokerRulePlane					//10飞机   6  8 10 张牌
*/

//3 4 5 6 7 8 9 10 11(J) 12(Q) 13(K) 14(尖)15(2) 16(小王) 17(大王)
PokerRuleType PokerRule::checkPoker(const vector<Poker> &pokers)
{
	if (pokers.size() <= 0)
	{
		return PokerRuleError;
	}
	if (pokers.size() == 1)
	{
		return PokerRuleSingle;
	}
	if (pokers.size() == 2)
	{
		if ((pokers[0].mNum==17 && pokers[1].mNum==16) || (pokers[0].mNum == 16 && pokers[1].mNum == 17))
		{
			return PokerRuleDoubleKing;
		}
		if (pokers[0].mNum==pokers[1].mNum)
		{
			return PokerRuleDouble;
		}
		return PokerRuleError;
	}
	if (pokers.size() == 3)
	{
		if (pokers[0].mNum == pokers[1].mNum && pokers[0].mNum == pokers[2].mNum)
		{
			return PokerRuleTrouble;
		}
		return PokerRuleError;
	}
	if (pokers.size() == 4)
	{
		if (pokers[0].mNum == pokers[1].mNum && pokers[0].mNum == pokers[2].mNum && pokers[0].mNum == pokers[3].mNum)
		{
			return PokerRuleUltra;
		}
		if ((pokers[0].mNum == pokers[1].mNum && pokers[0].mNum == pokers[2].mNum)||(pokers[1].mNum == pokers[2].mNum && pokers[1].mNum == pokers[3].mNum))
		{
			return PokerRuleTroubleWithSingle;
		}
		return PokerRuleError;
	}
	if (pokers.size() >= 5)
	{
		//PokerRuleUltraWithTwoSingle,		//8.四带二张单牌
		//PokerRulePlane						//10飞机   6  8 10 张牌
		if (pokers.size() == 6)
		{
			if (pokers[0].mNum==pokers[1].mNum&&pokers[0].mNum==pokers[2].mNum&&pokers[0].mNum==pokers[3].mNum)
			{
				return PokerRuleUltraWithTwoSingle;
			}
			if (pokers[1].mNum == pokers[2].mNum&&pokers[1].mNum == pokers[3].mNum&&pokers[1].mNum == pokers[4].mNum)
			{
				return PokerRuleUltraWithTwoSingle;
			}
			if (pokers[2].mNum == pokers[3].mNum&&pokers[2].mNum == pokers[4].mNum&&pokers[2].mNum == pokers[5].mNum)
			{
				return PokerRuleUltraWithTwoSingle;
			}
			if (pokers[0].mNum==pokers[1].mNum&&pokers[0].mNum==pokers[2].mNum&&pokers[2].mNum==(pokers[3].mNum+1) && pokers[3].mNum==pokers[4].mNum&&pokers[3].mNum==pokers[5].mNum)
			{
				if (pokers[5].mNum < 15 && pokers[0].mNum > 2)
				{
					return PokerRulePlane;
				}
			}
		}
		if (pokers[0].mNum != pokers[1].mNum)
		{
			//单顺子
			int idx = 1;
			for (int i = 0; i < pokers.size()-1;++i)
			{
				if (pokers[i].mNum != (pokers[i+1].mNum+1)) 
				{
					idx = -1;
					break;
				}
			}
			if (idx==1)
			{
				if (pokers[0].mNum < 3 || pokers[pokers.size() - 1].mNum > 14)
				{
					return PokerRuleError;
				}
				else
				{
					return PokerRuleLine;
				}
			}
		}
		if (pokers.size()==5)
		{
			//PokerRuleTroubleWithDouble,		//7.三带一对
			if (pokers[0].mNum == pokers[1].mNum && pokers[0].mNum == pokers[2].mNum && pokers[2].mNum != pokers[3].mNum && pokers[3].mNum == pokers[4].mNum)
			{
				return PokerRuleTroubleWithDouble;
			}
			if (pokers[0].mNum == pokers[1].mNum && pokers[1].mNum != pokers[2].mNum && pokers[2].mNum == pokers[3].mNum&&pokers[2].mNum == pokers[4].mNum)
			{
				return PokerRuleTroubleWithDouble;
			}
		}
		if (pokers.size() >= 6 || pokers.size()%2==0)
		{
			int idx = 1;
			for (int i = 0; i < pokers.size(); i+=2)
			{
				if (pokers[i].mNum!=pokers[i+1].mNum)
				{
					idx = -1;
					break;
				}
				if (i+2 < pokers.size())
				{
					if (pokers[i].mNum != pokers[i+2].mNum+1)
					{
						idx = -1;
						break;
					}
				}
			}
			if (idx == 1)
			{
				if (pokers[0].mNum > 14 || pokers[pokers.size() - 1].mNum < 3)
				{
					return PokerRuleError;
				}
				else
				{
					return PokerRuleDoubleLine;
				}
			}
		}
		if (pokers.size() == 8)
		{
			//PokerRuleUltraWithTwoDouble		//9.四带两队 8张
			if ((pokers[0].mNum==pokers[1].mNum&&pokers[0].mNum==pokers[2].mNum&&pokers[0].mNum==pokers[3].mNum && pokers[4].mNum==pokers[5].mNum && pokers[5].mNum!=pokers[6].mNum &&pokers[6].mNum==pokers[7].mNum))
			{
				return PokerRuleUltraWithTwoDouble;
			}
			if ((pokers[0].mNum == pokers[1].mNum&&pokers[2].mNum == pokers[3].mNum&&pokers[2].mNum == pokers[4].mNum && pokers[2].mNum == pokers[5].mNum&&pokers[6].mNum == pokers[7].mNum))
			{
				return PokerRuleUltraWithTwoDouble;
			}
			if ((pokers[0].mNum == pokers[1].mNum && pokers[1].mNum != pokers[2].mNum &&pokers[2].mNum == pokers[3].mNum&&pokers[4].mNum == pokers[5].mNum && pokers[4].mNum == pokers[6].mNum&&pokers[4].mNum == pokers[7].mNum && pokers[1].mNum!=pokers[2].mNum))
			{
				return PokerRuleUltraWithTwoDouble;
			}
			//PokerRulePlane					//10飞机     8  张牌
			if (pokers[0].mNum==pokers[1].mNum && pokers[0].mNum==pokers[2].mNum && pokers[2].mNum==(pokers[3].mNum + 1)&&pokers[3].mNum==pokers[4].mNum&&pokers[3].mNum==pokers[5].mNum&&pokers[6].mNum!=pokers[7].mNum)
			{
				if (pokers[0].mNum<15 && pokers[3].mNum>2)
				{
					return PokerRulePlane;
				}
			}
			if (pokers[0].mNum != pokers[1].mNum && pokers[1].mNum == pokers[2].mNum && pokers[1].mNum == pokers[3].mNum && pokers[3].mNum == (pokers[4].mNum + 1)&&pokers[4].mNum == pokers[5].mNum&&pokers[4].mNum == pokers[6].mNum&&pokers[6].mNum!=pokers[7].mNum)
			{
				if (pokers[1].mNum<15 && pokers[4].mNum>2)
				{
					return PokerRulePlane;
				}
			}
			if (pokers[1].mNum != pokers[2].mNum && pokers[2].mNum == pokers[3].mNum && pokers[2].mNum == pokers[4].mNum && pokers[4].mNum == (pokers[5].mNum + 1) && pokers[5].mNum == pokers[6].mNum&&pokers[5].mNum == pokers[7].mNum)
			{
				if (pokers[2].mNum < 15 && pokers[5].mNum > 2)
				{
					return PokerRulePlane;
				}
			}
		}
		if (pokers.size()==10)
		{
			//PokerRulePlane					//10飞机  10 张牌
			if (pokers[0].mNum == pokers[1].mNum&&pokers[0].mNum == pokers[2].mNum&&pokers[2].mNum == (pokers[3].mNum + 1) && pokers[3].mNum == pokers[4].mNum&&pokers[3].mNum == pokers[5].mNum&&pokers[5].mNum != pokers[6].mNum&&pokers[6].mNum == pokers[7].mNum&&pokers[7].mNum != pokers[8].mNum&&pokers[8].mNum == pokers[9].mNum)
			{
				if (pokers[0].mNum < 15 && pokers[3].mNum > 2)
				{
					return PokerRulePlane;
				}
			}
			if (pokers[0].mNum==pokers[1].mNum && pokers[1].mNum!=pokers[2].mNum && pokers[2].mNum==pokers[3].mNum&&pokers[2].mNum==pokers[4].mNum&&pokers[4].mNum==(pokers[5].mNum + 1)&&pokers[5].mNum==pokers[6].mNum&&pokers[5].mNum==pokers[7].mNum&&pokers[7].mNum!=pokers[8].mNum&&pokers[8].mNum==pokers[9].mNum)
			{
				if (pokers[2].mNum < 15 && pokers[5].mNum > 2)
				{
					return PokerRulePlane;
				}
			}
			if (pokers[0].mNum == pokers[1].mNum && pokers[1].mNum != pokers[2].mNum && pokers[2].mNum == pokers[3].mNum && pokers[3].mNum != pokers[4].mNum && pokers[4].mNum == pokers[5].mNum && pokers[4].mNum == pokers[6].mNum && pokers[6].mNum == (pokers[7].mNum + 1) && pokers[7].mNum == pokers[8].mNum&&pokers[7].mNum == pokers[9].mNum)
			{
				if (pokers[4].mNum < 15 && pokers[7].mNum > 2)
				{
					return PokerRulePlane;
				}
			}
		}
		return PokerRuleError;
	}
}

bool PokerRule::compare(const vector<Poker> &last, const vector<Poker> &now)
{
	PokerRuleType lastType = checkPoker(last);
	PokerRuleType nowType = checkPoker(now);
	log("last type===%d", lastType);
	log("now type === %d", nowType);
	switch (lastType)
	{
	case PokerRuleError:
	{
		return false;
	}
		break;
	case PokerRuleDoubleKing:
	{
		return false;
	}
		break;
	case PokerRuleSingle:
	{
		if (nowType == PokerRuleSingle)
		{
			return now[0].mNum > last[0].mNum;
		}
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
	}
		break;
	case PokerRuleDouble:
	{
		if (nowType == PokerRuleDouble)
		{
			return now[0].mNum > last[0].mNum;
		}
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
	}
		break;
	case PokerRuleTrouble:
	{
		if (nowType == PokerRuleTrouble)
		{
			return now[0].mNum > last[0].mNum;
		}
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
	}
		break;
	case PokerRuleUltra:
	{
		if (nowType == PokerRuleUltra)
		{
			return now[0].mNum > last[0].mNum;
		}
		if (nowType == PokerRuleDoubleKing)
		{
			return true;
		}
	}
		break;
	case PokerRuleLine:
	{
		if (nowType == PokerRuleLine)
		{
			if (last.size() != now.size())
			{
				return false;
			}
			else
			{
				return now[now.size() - 1].mNum > last[last.size() - 1].mNum;
			}
		}
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
	}
		break;
	case PokerRuleDoubleLine:
	{
		if (nowType == PokerRuleDoubleLine)
		{
			if (last.size() != now.size())
			{
				return false;
			}
			else
			{
				return now[now.size() - 1].mNum > last[last.size() - 1].mNum;
			}
		}
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
	}
		break;
	case PokerRuleTroubleWithSingle:
	{
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
		if (nowType == PokerRuleTroubleWithSingle)
		{
			int lastNum = -1, nowNum = -1;
			if (last[0].mNum == last[1].mNum)
			{
				lastNum = last[0].mNum;
			}
			else
			{
				lastNum = last[last.size() - 1].mNum;
			}
			if (now[0].mNum == now[1].mNum)
			{
				nowNum = now[0].mNum;
			}
			else
			{
				nowNum = now[now.size() - 1].mNum;
			}
			return nowNum > lastNum;
		}
	}
		break;
	case PokerRuleTroubleWithDouble:
	{
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
		if (nowType == PokerRuleTroubleWithDouble)
		{
			int lastNum = -1, nowNum = -1;
			if (last[0].mNum == last[1].mNum && last[0].mNum == last[2].mNum)
			{
				lastNum = last[0].mNum;
			}
			else
			{
				lastNum = last[last.size() - 1].mNum;
			}
			if (now[0].mNum == now[1].mNum && now[0].mNum == now[2].mNum)
			{
				nowNum = now[0].mNum;
			}
			else
			{
				nowNum = now[now.size() - 1].mNum;
			}
			return nowNum > lastNum;
		}
	}
		break;
	case PokerRuleUltraWithTwoSingle:
	{
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
		if (nowType == PokerRuleUltraWithTwoSingle)
		{
			int lastNum = -1, nowNum = -1;
			if (last[0].mNum == last[1].mNum&&last[0].mNum == last[2].mNum&&last[0].mNum == last[3].mNum)
			{
				lastNum = last[0].mNum;
			}
			if (last[1].mNum == last[2].mNum&&last[1].mNum == last[3].mNum&&last[1].mNum == last[4].mNum)
			{
				lastNum = last[1].mNum;
			}
			if (last[2].mNum == last[3].mNum&&last[2].mNum == last[4].mNum&&last[2].mNum == last[5].mNum)
			{
				lastNum = last[2].mNum;
			}
			if (now[0].mNum == now[1].mNum&&now[0].mNum == now[2].mNum&&now[0].mNum == now[3].mNum)
			{
				nowNum = last[0].mNum;
			}
			if (now[1].mNum == now[2].mNum&&now[1].mNum == now[3].mNum&&now[1].mNum == now[4].mNum)
			{
				nowNum = last[1].mNum;
			}
			if (now[2].mNum == now[3].mNum&&now[2].mNum == now[4].mNum&&now[2].mNum == now[5].mNum)
			{
				nowNum = last[2].mNum;
			}
			return nowNum > lastNum;
		}
	}
		break;
	case PokerRuleUltraWithTwoDouble:
	{
		if (nowType == PokerRuleDoubleKing || nowType == PokerRuleUltra)
		{
			return true;
		}
		if (nowType == PokerRuleUltraWithTwoSingle)
		{
			int lastNum = -1, nowNum = -1;
			if ((last[0].mNum == last[1].mNum&&last[0].mNum == last[2].mNum&&last[0].mNum == last[3].mNum && last[4].mNum == last[5].mNum && last[5].mNum != last[6].mNum &&last[6].mNum == last[7].mNum))
			{
				lastNum = last[0].mNum;
			}
			if ((last[0].mNum == last[1].mNum&&last[2].mNum == last[3].mNum&&last[2].mNum == last[4].mNum && last[2].mNum == last[5].mNum&&last[6].mNum == last[7].mNum))
			{
				lastNum = last[2].mNum;
			}
			if ((last[0].mNum == last[1].mNum && last[1].mNum != last[2].mNum &&last[2].mNum == last[3].mNum&&last[4].mNum == last[5].mNum && last[4].mNum == last[6].mNum&&last[4].mNum == last[7].mNum && last[1].mNum != last[2].mNum))
			{
				lastNum = last[5].mNum;
			}

			if ((now[0].mNum == now[1].mNum&&now[0].mNum == now[2].mNum&&now[0].mNum == now[3].mNum && now[4].mNum == now[5].mNum && now[5].mNum != now[6].mNum &&now[6].mNum == now[7].mNum))
			{
				nowNum = now[0].mNum;
			}
			if ((now[0].mNum == now[1].mNum&&now[2].mNum == now[3].mNum&&now[2].mNum == now[4].mNum && now[2].mNum == now[5].mNum&&now[6].mNum == now[7].mNum))
			{
				nowNum = now[2].mNum;
			}
			if ((now[0].mNum == now[1].mNum && now[1].mNum != now[2].mNum &&now[2].mNum == now[3].mNum&&now[4].mNum == now[5].mNum && now[4].mNum == now[6].mNum&&now[4].mNum == now[7].mNum && now[1].mNum != now[2].mNum))
			{
				nowNum = now[5].mNum;
			}
			return nowNum > lastNum;
		}
	}
		break;
	case PokerRulePlane:
	{
		if (last.size()!=now.size())
		{
			return false;
		}
		int lastNum = -1, nowNum = -1;
		if (last.size() == 6 && now.size() == 6)
		{
			lastNum = last[last.size() - 1].mNum;
			nowNum = now[now.size() - 1].mNum;
			return nowNum > lastNum;
		}
		if (last.size() == 8 && now.size() == 8)
		{
			//PokerRulePlane					//10飞机     8  张牌
			if (last[0].mNum == last[1].mNum && last[0].mNum == last[2].mNum && last[2].mNum == (last[3].mNum + 1) && last[3].mNum == last[4].mNum&&last[3].mNum == last[5].mNum&&last[6].mNum != last[7].mNum)
			{
				lastNum = last[3].mNum;
			}
			if (last[0].mNum != last[1].mNum && last[1].mNum == last[2].mNum && last[1].mNum == last[3].mNum && last[3].mNum == (last[4].mNum + 1) && last[4].mNum == last[5].mNum&&last[4].mNum == last[6].mNum&&last[6].mNum != last[7].mNum)
			{
				lastNum = last[4].mNum;
			}
			if (last[1].mNum != last[2].mNum && last[2].mNum == last[3].mNum && last[2].mNum == last[4].mNum && last[4].mNum == (last[5].mNum + 1) && last[5].mNum == last[6].mNum&&last[5].mNum == last[7].mNum)
			{
				lastNum = last[5].mNum;
			}

			if (now[0].mNum == now[1].mNum && now[0].mNum == now[2].mNum && now[2].mNum == (now[3].mNum + 1) && now[3].mNum == now[4].mNum&&now[3].mNum == now[5].mNum&&now[6].mNum != now[7].mNum)
			{
				nowNum = now[3].mNum;
			}
			if (now[0].mNum != now[1].mNum && now[1].mNum == now[2].mNum && now[1].mNum == now[3].mNum && now[3].mNum == (now[4].mNum + 1) && now[4].mNum == now[5].mNum&&now[4].mNum == now[6].mNum&&now[6].mNum != now[7].mNum)
			{
				nowNum = now[4].mNum;
			}
			if (now[1].mNum != now[2].mNum && now[2].mNum == now[3].mNum && now[2].mNum == now[4].mNum && now[4].mNum == (now[5].mNum + 1) && now[5].mNum == now[6].mNum&&now[5].mNum == now[7].mNum)
			{
				nowNum = last[5].mNum;
			}
			return nowNum > lastNum;
		}
		if (last.size() == 10 && now.size() == 10)
		{
			if (last[0].mNum == last[1].mNum&&last[0].mNum == last[2].mNum&&last[2].mNum == (last[3].mNum + 1) && last[3].mNum == last[4].mNum&&last[3].mNum == last[5].mNum&&last[5].mNum != last[6].mNum&&last[6].mNum == last[7].mNum&&last[7].mNum != last[8].mNum&&last[8].mNum == last[9].mNum)
			{
				lastNum = last[3].mNum;
			}
			if (last[0].mNum == last[1].mNum && last[1].mNum != last[2].mNum && last[2].mNum == last[3].mNum&&last[2].mNum == last[4].mNum&&last[4].mNum == (last[5].mNum + 1) && last[5].mNum == last[6].mNum&&last[5].mNum == last[7].mNum&&last[7].mNum != last[8].mNum&&last[8].mNum == last[9].mNum)
			{
				lastNum = last[5].mNum;
			}
			if (last[0].mNum == last[1].mNum && last[1].mNum != last[2].mNum && last[2].mNum == last[3].mNum && last[3].mNum != last[4].mNum && last[4].mNum == last[5].mNum && last[4].mNum == last[6].mNum && last[6].mNum == (last[7].mNum + 1) && last[7].mNum == last[8].mNum&&last[7].mNum == last[9].mNum)
			{
				lastNum = last[7].mNum;
			}

			if (now[0].mNum == now[1].mNum&&now[0].mNum == now[2].mNum&&now[2].mNum == (now[3].mNum + 1) && now[3].mNum == now[4].mNum&&now[3].mNum == now[5].mNum&&now[5].mNum != now[6].mNum&&now[6].mNum == now[7].mNum&&now[7].mNum != now[8].mNum&&now[8].mNum == now[9].mNum)
			{
				lastNum = now[3].mNum;
			}
			if (now[0].mNum == now[1].mNum && now[1].mNum != now[2].mNum && now[2].mNum == now[3].mNum&&now[2].mNum == now[4].mNum&&now[4].mNum == (now[5].mNum + 1) && now[5].mNum == now[6].mNum&&now[5].mNum == now[7].mNum&&now[7].mNum != now[8].mNum&&now[8].mNum == now[9].mNum)
			{
				lastNum = now[5].mNum;
			}
			if (now[0].mNum == now[1].mNum && now[1].mNum != now[2].mNum && now[2].mNum == now[3].mNum && now[3].mNum != now[4].mNum && now[4].mNum == now[5].mNum && now[4].mNum == now[6].mNum && now[6].mNum == (now[7].mNum + 1) && now[7].mNum == now[8].mNum&&now[7].mNum == now[9].mNum)
			{
				lastNum = now[7].mNum;
			}
			return nowNum > lastNum;
		}
	}
		break;
	default:
		break;
	}
	return false;
}
