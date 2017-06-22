#include "GameStartScene.h"
#include <numeric>
#include <time.h>
#include "PokerRule.h"
#include "AppMicraos.h"

cocos2d::CCScene * GameStartScene::createScene()
{
	CCScene *scene = CCScene::create();
	GameStartScene *layer = GameStartScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameStartScene::init()
{
	startLairShip = 0;
	player1.playerIdx = 1;
	player2.playerIdx = 2;
	player3.playerIdx = 3;

	srand((unsigned int)time(NULL));
	lairtShip = -1;
	createPokers();
	washePokers();
	sendPokers();
	//createPokerUI();//������Ӧ�˿���UI
	startCallLairdShip();
	outPokerBtn();
	noOutPokerBtn();
	return true;
}

//�����˿���
void GameStartScene::createPokers()
{
	PokerColor color;
	for (int i = 0;i< 4; ++i)
	{
		//3 4 5 6 7 8 9 10 11(J) 12(Q) 13(K) 14(��)15(2) 16(С��) 17(����)
		for (int j = 3; j < 16; j++)
		{
			switch (i)
			{
			case 0:
				color = PokerColor_Red;
				break;
			case 1:
				color = PokerColor_Black;
				break;
			case 2:
				color = PokerColor_Flower;
				break;
			case 3:
				color = PokerColor_Piece;
				break;
			}
			Poker poker(j, color);
			mPokers.push_back(poker);
		}
	}
	Poker poker1(16, PokerColor_Black);//С��
	mPokers.push_back(poker1);
	Poker poker2(17, PokerColor_Red);//����
	mPokers.push_back(poker2);
}
//ϴ��
void GameStartScene::washePokers()
{
	random_shuffle(mPokers.begin(), mPokers.end());
}
//����
void GameStartScene::sendPokers()
{
	int idx = 0;
	int distance1 = 20,distance2 = 450,distance3 = 950;
	int w = 45;
	int h = 120;
	int space = 30;
	int y = 300,y2=30;
	for (int i = 0; i < 51; ++i)
	{
		PopkerSpirte *sprite = PopkerSpirte::createSprite(CCSizeMake(w, h), mPokers[i].mNum, mPokers[i].mColor);
		switch (idx)
		{
		case 0:
			player1.catchPoker(sprite);
			break;
		case 1:
			player2.catchPoker(sprite);
			break;
		case 2:
			player3.catchPoker(sprite);
			break;
		}
		++idx;
		if (idx==3)
		{
			idx = 0;
		}
		addChild(sprite);
	}
	player1.refreUI();
	player2.refreUI();
	player3.refreUI();
	mSurplusPokers.push_back(mPokers[51]);
	mSurplusPokers.push_back(mPokers[52]);
	mSurplusPokers.push_back(mPokers[53]);
}
//��ʼ�е���
void GameStartScene::startCallLairdShip()
{
	createCallBtn();
	int idx = rand() % 3;
	if (idx==0)
	{
		btn1->setVisible(true);
	}
	if (idx==1)
	{
		btn2->setVisible(true);
	}
	if (idx==2)
	{
		btn3->setVisible(true);
	}
}

//�е������� ������������
void GameStartScene::endCallLairdShip()
{
	int w = 45;
	int h = 120;
	switch (lairtShip)
	{
	case 1:
	{
		for (vector<Poker>::iterator it = mSurplusPokers.begin(); it != mSurplusPokers.end(); ++it)
		{
			PopkerSpirte *sprite = PopkerSpirte::createSprite(CCSizeMake(w, h), (*it).mNum, (*it).mColor);
			addChild(sprite);
			player1.obtainSurplusPokers(sprite);
		}
	}
		break;
	case 2:
	{
		for (vector<Poker>::iterator it = mSurplusPokers.begin(); it != mSurplusPokers.end(); ++it)
		{
			PopkerSpirte *sprite = PopkerSpirte::createSprite(CCSizeMake(w, h), (*it).mNum, (*it).mColor);
			addChild(sprite);
			player2.obtainSurplusPokers(sprite);
		}
	}
	break;
	case 3:
	{
		for (vector<Poker>::iterator it = mSurplusPokers.begin(); it != mSurplusPokers.end(); ++it)
		{
			PopkerSpirte *sprite = PopkerSpirte::createSprite(CCSizeMake(w, h), (*it).mNum, (*it).mColor);
			addChild(sprite);
			player3.obtainSurplusPokers(sprite);
		}
	}
	break;
	}
	startGame();
}

//��ʼ����  �����ȿ�ʼ
void GameStartScene::startGame()
{
	switch (lairtShip)
	{
	case 1:
		nowPlayer = 1;
		send_btn1->setVisible(true);
		no_btn1->setVisible(false);
		break;
	case 2:
		nowPlayer = 2;
		send_btn2->setVisible(true);
		no_btn2->setVisible(false);
		break;
	case 3:
		nowPlayer = 3;
		send_btn3->setVisible(true);
		no_btn3->setVisible(false);
		break;
	default:
		break;
	}
}
//���ư�ť
void GameStartScene::outPokerBtn()
{
	//��ť����  
	LabelTTF* title = LabelTTF::create(UTEXT("����"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	send_btn1 = ControlButton::create(title, btnNormal);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	send_btn1->setPreferredSize(Size(200, 20));
	send_btn1->setPosition(Point(200, 400));
	send_btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::outPoker1), Control::EventType::TOUCH_UP_INSIDE);
	addChild(send_btn1);
	send_btn1->setVisible(false);

	//��ť����  
	LabelTTF* title2 = LabelTTF::create(UTEXT("����"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal2 = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	send_btn2 = ControlButton::create(title2, btnNormal2);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	send_btn2->setPreferredSize(Size(200, 20));
	send_btn2->setPosition(Point(600, 180));
	send_btn2->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::outPoker2), Control::EventType::TOUCH_UP_INSIDE);
	addChild(send_btn2);
	send_btn2->setVisible(false);

	//��ť����  
	LabelTTF* title3 = LabelTTF::create(UTEXT("����"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal3 = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	send_btn3 = ControlButton::create(title3, btnNormal3);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	send_btn3->setPreferredSize(Size(200, 20));
	send_btn3->setPosition(Point(1200, 400));
	send_btn3->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::outPoker3), Control::EventType::TOUCH_UP_INSIDE);
	addChild(send_btn3);
	send_btn3->setVisible(false);
}

//Ҫ����ť
void GameStartScene::noOutPokerBtn()
{
	//��ť����  
	LabelTTF* title = LabelTTF::create(UTEXT("��Ҫ"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	no_btn1 = ControlButton::create(title, btnNormal);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	no_btn1->setPreferredSize(Size(80, 20));
	no_btn1->setPosition(Point(350, 400));
	no_btn1->setTag(100);
	no_btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::noOutBtnAction), Control::EventType::TOUCH_UP_INSIDE);
	addChild(no_btn1);
	no_btn1->setVisible(false);

	//��ť����  
	LabelTTF* title2 = LabelTTF::create(UTEXT("��Ҫ"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal2 = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	no_btn2 = ControlButton::create(title2, btnNormal2);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	no_btn2->setPreferredSize(Size(80, 20));
	no_btn2->setPosition(Point(800, 180));
	no_btn2->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::noOutBtnAction), Control::EventType::TOUCH_UP_INSIDE);
	addChild(no_btn2);
	no_btn2->setVisible(false);
	no_btn2->setTag(200);

	//��ť����  
	LabelTTF* title3 = LabelTTF::create(UTEXT("��Ҫ"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal3 = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	no_btn3 = ControlButton::create(title3, btnNormal3);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	no_btn3->setPreferredSize(Size(80, 20));
	no_btn3->setPosition(Point(1350, 400));
	no_btn3->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::noOutBtnAction), Control::EventType::TOUCH_UP_INSIDE);
	addChild(no_btn3);
	no_btn3->setTag(300);

	no_btn3->setVisible(false);
}

void GameStartScene::outPoker1(CCObject* sender, Control::EventType controlEvent)
{
	vector<Poker> tmp = player1.outPoker(lastPlayerOutPokers);
	if (tmp.empty())
	{
		return;
	}
	else
	{
		lastPlayerOutPokers = tmp;
	}
	if (player1.mPokers.empty())
	{
		log("game over player3 win");
	}
	send_btn1->setVisible(false);
	send_btn2->setVisible(true);
	no_btn1->setVisible(false);
	no_btn2->setVisible(true);
	nowPlayer = 1;
}

void GameStartScene::outPoker2(CCObject * sender, Control::EventType controlEvent)
{
	log("PAYER 2 OUT");
	vector<Poker> tmp = player2.outPoker(lastPlayerOutPokers);
	if (tmp.empty())
	{
		return;
	}
	else
	{
		lastPlayerOutPokers = tmp;
	}
	if (player2.mPokers.empty())
	{
		log("game over player3 win");
	}

	send_btn2->setVisible(false);
	send_btn3->setVisible(true);
	no_btn2->setVisible(false);
	no_btn3->setVisible(true);
	nowPlayer = 2;
}

void GameStartScene::outPoker3(CCObject* sender, Control::EventType controlEvent)
{
	log("PAYER 3 OUT");
	vector<Poker> tmp = player3.outPoker(lastPlayerOutPokers);
	if (tmp.empty())
	{
		return;
	}
	else
	{
		lastPlayerOutPokers = tmp;
	}
	if (player3.mPokers.empty())
	{
		log("game over player3 win");
	}
	send_btn3->setVisible(false);
	send_btn1->setVisible(true);
	no_btn3->setVisible(false);
	no_btn1->setVisible(true);
	nowPlayer = 3;
}

void GameStartScene::noOutBtnAction(CCObject* sender, Control::EventType controlEvent)
{
	ControlButton *btn = (ControlButton *)sender;
	switch (btn->getTag())
	{
	case 100:
	{
		if (nowPlayer==2)
		{
			no_btn2->setVisible(false);
			lastPlayerOutPokers.clear();
		}
		else
		{
			no_btn2->setVisible(true);
		}
		send_btn2->setVisible(true);
		send_btn1->setVisible(false);
		no_btn1->setVisible(false);
	}
		break;
	case 200:
	{
		if (nowPlayer == 3)
		{
			no_btn3->setVisible(false);
			lastPlayerOutPokers.clear();
		}
		else
		{
			no_btn3->setVisible(true);
		}
		send_btn3->setVisible(true);
		send_btn2->setVisible(false);
		no_btn2->setVisible(false);
	}
	break;
	case 300:
	{
		if (nowPlayer == 1)
		{
			no_btn1->setVisible(false);
			lastPlayerOutPokers.clear();
		}
		else
		{
			no_btn1->setVisible(true);
		}
		send_btn1->setVisible(true);
		send_btn3->setVisible(false);
		no_btn3->setVisible(false);
	}
	break;
	default:
		break;
	}
}

void GameStartScene::createCallBtn()
{
	//��ť����  
	LabelTTF* title = LabelTTF::create(UTEXT("�е���"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	btn1 = ControlButton::create(title, btnNormal);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	btn1->setPreferredSize(Size(200, 20));
	btn1->setPosition(Point(200, 400));
	btn1->setTag(100);
	btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::touchUpInside), Control::EventType::TOUCH_UP_INSIDE);
	addChild(btn1);
	btn1->setVisible(false);

	//��ť����  
	LabelTTF* title2 = LabelTTF::create(UTEXT("�е���"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal2 = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	btn2 = ControlButton::create(title2, btnNormal2);
	btn2->setTag(101);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	btn2->setPreferredSize(Size(200, 20));
	btn2->setPosition(Point(700, 190));
	btn2->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::touchUpInside), Control::EventType::TOUCH_UP_INSIDE);
	addChild(btn2);
	btn2->setVisible(false);

	//��ť����  
	LabelTTF* title3 = LabelTTF::create(UTEXT("�е���"), "Marker Felt", 30);
	//����״̬�µİ�ťͼƬ  
	Scale9Sprite* btnNormal3 = Scale9Sprite::create("CloseSelected.png");
	//������ť����ť�Ĵ�С���ݱ����Զ�����  
	btn3 = ControlButton::create(title3, btnNormal3);
	btn3->setTag(102);
	//ǿ�����ð�ť��С�������ť���������Χ�����Զ�����  
	btn3->setPreferredSize(Size(200, 20));
	btn3->setPosition(Point(1200, 400));
	btn3->addTargetWithActionForControlEvents(this, cccontrol_selector(GameStartScene::touchUpInside), Control::EventType::TOUCH_UP_INSIDE);
	addChild(btn3);
	btn3->setVisible(false);

}

void GameStartScene::touchUpInside(CCObject* sender, Control::EventType controlEvent)
{

	ControlButton *btn = (ControlButton *)sender;
	if (btn->getTag() == 100)
	{
		lairtShip = 1;
		if (startLairShip ==3)
		{
			endCallLairdShip();
			btn1->setVisible(false);
		}
		else
		{
			btn1->setVisible(false);
			btn2->setVisible(true);
		}
	}
	if (btn->getTag() == 101)
	{
		lairtShip = 2;
		if (startLairShip == 3)
		{
			endCallLairdShip();
			btn2->setVisible(false);
		}
		else
		{
			btn2->setVisible(false);
			btn3->setVisible(true);
		}
	}
	if (btn->getTag() == 102)
	{
		lairtShip = 3;
		if (startLairShip == 3)
		{
			endCallLairdShip();
			btn3->setVisible(false);
		}
		else
		{
			btn3->setVisible(false);
			btn1->setVisible(true);
		}
	}
	startLairShip++;
}