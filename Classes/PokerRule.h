#ifndef __POKERRULE_H__
#define __POKERRULE_H__

/*
打牌规则:
-1 不符合出牌规则
0. 大小王两张最大
1.单张：大小顺序
2.一对：大小顺序
3.三张：大小顺序
4.顺子：（5张）（相同大小比最大）
5.双顺：（3连对）（相同大小比最大 ）
6.三带一张单牌  三带一对
7.四带二张单牌  四带两队

*/

#include <vector>
#include "Poker.h"
#include "cocos2d.h"
USING_NS_CC;

enum PokerRuleType
{
	PokerRuleError = -1,				//-1 不符合出牌规则
	PokerRuleDoubleKing,				//0. 大小王两张最大
	PokerRuleSingle,					//1.单张：大小顺序
	PokerRuleDouble,					//2.一对：大小顺序
	PokerRuleTrouble,				//3.三张：大小顺序
	PokerRuleUltra,					//4.四张相同  炸弹
	PokerRuleLine,					//5.顺子：（5张）（相同大小比最大）
	PokerRuleDoubleLine,				//6.双顺：（3连对）（相同大小比最大 ）
	PokerRuleTroubleWithSingle,		//7.三带一张单牌
	PokerRuleTroubleWithDouble,		//8.三带一对                             
	PokerRuleUltraWithTwoSingle,		//9.四带二张单牌  
	PokerRuleUltraWithTwoDouble,		//10.四带两队
	PokerRulePlane					//11飞机   6  8 10 张牌
};

class PokerRule
{
public:
	//判断所选的牌属于那种类型
	static PokerRuleType checkPoker(const vector<Poker> &pokers);
	//比较牌的大小
	static bool compare(const vector<Poker> &last, const vector<Poker> &now);

private:

};





#endif // !__POKERRULE_H__

