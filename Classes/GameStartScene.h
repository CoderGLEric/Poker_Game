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
	//�����˿���
	void createPokers();
	//ϴ��
	void washePokers();
	//����
	void sendPokers();
	//��ʼ�е���
	void startCallLairdShip();
	//�е������� ������������
	void endCallLairdShip();
	//��ʼ����  �����ȿ�ʼ
	void startGame();
	//UI
	void createCallBtn();
	//���ư�ť
	void outPokerBtn();
	//Ҫ����ť
	void noOutPokerBtn();
	void touchUpInside(CCObject* sender, Control::EventType controlEvent);
	void outPoker1(CCObject* sender, Control::EventType controlEvent);
	void outPoker2(CCObject* sender, Control::EventType controlEvent);
	void outPoker3(CCObject* sender, Control::EventType controlEvent);
	void noOutBtnAction(CCObject* sender, Control::EventType controlEvent);//���� ��һ�����
private:
	Player player1;
	Player player2;
	Player player3;
	ControlButton *btn1;
	ControlButton *btn2;
	ControlButton *btn3;
	vector<Poker> mPokers;
	vector<Poker> mSurplusPokers;//����
	int startLairShip;//�ʼ���
	int lairtShip;//�������
	int nowPlayer;//��ǰ�������
	ControlButton *send_btn1;//������Ҹ��Գ��ư�ť
	ControlButton *send_btn2;
	ControlButton *send_btn3;
	ControlButton *no_btn1;//������Ҹ���Ҫ����ť
	ControlButton *no_btn2;
	ControlButton *no_btn3;
	vector<Poker> lastPlayerOutPokers;//��һ�������������
	list<PopkerSpirte*> lastPlayerpokerUIs;//��һ����������Ƶ�UI
};

#endif // !__GAMESTARTSCENE_H__

