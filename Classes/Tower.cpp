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
	damage = winSize.width * 10 / 480;
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
	chosenEnemy = NULL;
	return true;
}

void Tower::update(float delta)
{
	if (chosenEnemy) {
		//We make it turn to target the enemy chosen
		Vec2 normalized = Vec2(chosenEnemy->mySprite->getPositionX() - mySprite->getPositionX(),
			chosenEnemy->mySprite->getPositionY() - mySprite->getPositionY()).getNormalized();
		mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x)) + 90);

		if (!theGame->circle(mySprite->getPosition(), attackRange,
			chosenEnemy->mySprite->getPosition(), 1))
		{
			this->lostSightOfEnemy();
		}
	}
	else {
		for (auto enemy : theGame->enemies)
		{
			if (theGame->circle(mySprite->getPosition(),attackRange,
				enemy->mySprite->getPosition(), 1))
			{
				this->chosenEnemyForAttack(enemy);
				break;	
			}
		}
	}
}

void Tower::attackEnemy()
{
	this->schedule(schedule_selector(Tower::shootWeapon), fireRate);
}

void Tower::chosenEnemyForAttack(Enemy* enemy)
{
	chosenEnemy = NULL;
	chosenEnemy = enemy;
	this->attackEnemy();
	enemy->getAttacked(this);
}

void Tower::shootWeapon(float delta)
{
	Sprite* bullet = Sprite::create("bullet-hd.png");
	theGame->addChild(bullet);
	bullet->setPosition(mySprite->getPosition());
	bullet->runAction(Sequence::create(
		MoveTo::create(0.1f, chosenEnemy->mySprite->getPosition()),
		CallFunc::create(CC_CALLBACK_0(Tower::damageEnemy,this)),
		CallFuncN::create(CC_CALLBACK_0(Tower::removeBullet,this, bullet)), NULL));
}

void Tower::removeBullet(Sprite *bullet)
{
	bullet->removeFromParentAndCleanup(true);
}

void Tower::damageEnemy()
{
	if(chosenEnemy) chosenEnemy->getDamaged(damage);
}

void Tower::targetKilled()
{
	if (chosenEnemy)
		chosenEnemy = NULL;
	this->unschedule(schedule_selector(Tower::shootWeapon));
}

void Tower::lostSightOfEnemy()
{
	chosenEnemy->gotLostSight(this);
	if (chosenEnemy)
		chosenEnemy = NULL;
	this->unschedule(schedule_selector(Tower::shootWeapon));
}