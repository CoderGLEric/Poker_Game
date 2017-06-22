#ifndef __POKER_H__
#define __POKER_H__

#include <iostream>
using namespace std;

enum PokerColor
{
	PokerColor_Red,		//ºì
	PokerColor_Black,	//ºÚ
	PokerColor_Flower,	//»¨
	PokerColor_Piece		//¿é
};

class Poker
{
public:
	Poker();
	Poker(int num, PokerColor color);
public:
	int mNum;
	PokerColor mColor;
};



#endif // !__POKER_H__

