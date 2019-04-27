#include "Enemy.h"
#include "HelloWorldScene.h"
#define HEALTH_BAR_WIDTH 20
#define HEALTH_BAR_ORIGIN -10

Enemy* Enemy::createWithTheGame(HelloWorld* _game)
{
	auto obj = new Enemy();
	if (obj && obj->initWithTheGame(_game))
	{
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return nullptr;
}

// on "init" you need to initialize your instance
bool Enemy::initWithTheGame(HelloWorld* _game)
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

	theGame = _game;
    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();  
	maxHp = winSize.width * 40 / 480;
	currentHp = maxHp;
	active = false;
	walkingSpeed = winSize.width * 0.5 / 480;

	mySprite = Sprite::create("enemy-hd.png");
	this->addChild(mySprite);

	Waypoint * waypoint = theGame->waypoints.at(theGame->waypoints.size() - 1);
	destinationWaypoint = waypoint->nextWaypoint;
	Vec2 pos = waypoint->myPosition;
	myPosition = pos;
	mySprite->setPosition(pos);
	theGame->addChild(this);

	this->retain();

	this->scheduleUpdate();
	drawNode = DrawNode::create();
	this->addChild(drawNode);
	hBarOrigin = winSize.width * HEALTH_BAR_ORIGIN / 480;
	hBarWidth = winSize.width * HEALTH_BAR_WIDTH / 480;
	hBarDist = winSize.width * 16 / 480;
	hBarHeight = winSize.width * 14 / 480;
    return true;
}

void Enemy::doActivate(float delta)
{
	active = true;
}

void Enemy::getRemoved()
{
	theGame->enemies.eraseObject(this);
	////Notify the game that we killed an enemy so we can check if we can send another wave
	theGame->enemyGotKilled();
	this->removeFromParentAndCleanup(true);
}

void Enemy::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Enemy::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void Enemy::update(float delta)
{
	if (!active) return;

	if (theGame->circle(myPosition, 1, destinationWaypoint->myPosition, 1))
	{
		if (destinationWaypoint->nextWaypoint)
		{
			destinationWaypoint = destinationWaypoint->nextWaypoint;
		}
		else
		{
			//Reached the end of the road. Damage the player
			theGame->getHpDamage();
			this->getRemoved();
		}
	}

	Vec2 targetPoint = destinationWaypoint->myPosition;
	float movementSpeed = walkingSpeed;

	Vec2 normalized(targetPoint.x - myPosition.x, targetPoint.y - myPosition.y);
	normalized.normalize();

	mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x)));
	
	myPosition = Vec2(myPosition.x + normalized.x * movementSpeed,
		myPosition.y + normalized.y * movementSpeed);

	mySprite->setPosition(myPosition);
}

void Enemy::onDraw(const Mat4& transform, uint32_t flags)
{
	glPushMatrix();
	glLoadMatrixd((GLdouble*)&transform);
	drawNode->clear();
	drawNode->drawSolidRect(
		Vec2(myPosition.x + hBarOrigin, myPosition.y + hBarDist),
		Vec2(myPosition.x + hBarOrigin + hBarWidth,
			myPosition.y + hBarHeight),
		Color4F::RED);
	drawNode->drawSolidRect(
		Vec2(myPosition.x + hBarOrigin, myPosition.y + hBarDist),
		Vec2(myPosition.x + hBarOrigin + (float)(currentHp * (hBarWidth)) / maxHp,
			myPosition.y + hBarHeight),
		Color4F::GREEN);
	glPopMatrix();
}

