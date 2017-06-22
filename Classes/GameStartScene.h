#ifndef __GAMESTARTSCENE_H__
#define __GAMESTARTSCENE_H__

#include "cocos2d.h"
USING_NS_CC;
#include "Poker.h"
#include <vector>
#include "Player.h"
#include "PopkerSpirte.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
#include <deque>
#include <list>
#define winSize CCDirector::sharedDirector()->getWinSize() 
class GameStartScene: public CCLayer
{
public:
	static CCScene *createScene();
	virtual bool init();
	CREATE_FUNC(GameStartScene);
private:
	//生成扑克牌
	void createPokers();
	//洗牌
	void washePokers();
	//发牌
	void sendPokers();
	//开始叫地主
	void startCallLairdShip();
	//叫地主结束 给地主发底牌
	void endCallLairdShip();
	//开始打牌  地主先开始
	void startGame();
	//UI
	void createCallBtn();
	//出牌按钮
	void outPokerBtn();
	//要不起按钮
	void noOutPokerBtn();
	void touchUpInside(CCObject* sender, Control::EventType controlEvent);
	void outPoker1(CCObject* sender, Control::EventType controlEvent);
	void outPoker2(CCObject* sender, Control::EventType controlEvent);
	void outPoker3(CCObject* sender, Control::EventType controlEvent);
	void noOutBtnAction(CCObject* sender, Control::EventType controlEvent);//过牌 下一个玩家
private:
	Player player1;
	Player player2;
	Player player3;
	ControlButton *btn1;
	ControlButton *btn2;
	ControlButton *btn3;
	vector<Poker> mPokers;
	vector<Poker> mSurplusPokers;//底牌
	int startLairShip;//最开始玩家
	int lairtShip;//地主编号
	int nowPlayer;//当前出牌玩家
	ControlButton *send_btn1;//三名玩家各自出牌按钮
	ControlButton *send_btn2;
	ControlButton *send_btn3;
	ControlButton *no_btn1;//三名玩家各自要不起按钮
	ControlButton *no_btn2;
	ControlButton *no_btn3;
	vector<Poker> lastPlayerOutPokers;//上一个玩家所出的牌
	list<PopkerSpirte*> lastPlayerpokerUIs;//上一个玩家所出牌的UI
};

#endif // !__GAMESTARTSCENE_H__

