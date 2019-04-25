#include "Tower.h"

Tower* Tower::createWithTheGame(HelloWorld* _game, Vec2 location)
{
	auto obj = new Tower();
	if (obj && obj->initWithTheGame(_game, location))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}

// on "init" you need to initialize your instance
bool Tower::initWithTheGame(HelloWorld* _game, Vec2 location)
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize();
	theGame = _game;
	attackRange = winSize.width * 70 / 480;
	damage = 10;
	fireRate = 1;
	
	mySprite = Sprite::create("tower-hd.png");
	this->addChild(mySprite);
	mySprite->setPosition(location);
	theGame->addChild(this);

	auto draw = DrawNode::create();
	draw->drawCircle(mySprite->getPosition(),
		attackRange, 360, winSize.width * 30 / 480, false, 1.0f, 1.0f,
		Color4F::WHITE);
	this->addChild(draw);
	this->scheduleUpdate();
	return true;
}

void Tower::update(float delta)
{

}