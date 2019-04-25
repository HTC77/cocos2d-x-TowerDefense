#include "Waypoint.h"
#include "HelloWorldScene.h"

Waypoint* Waypoint::createWithTheGame(HelloWorld* _game, Vec2 location)
{
	auto obj = new Waypoint();
	if (obj && obj->initWithTheGame(_game, location))
	{
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return nullptr;
}

// on "init" you need to initialize your instance
bool Waypoint::initWithTheGame(HelloWorld* _game, Vec2 location)
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
	theGame = _game;
	this->setPosition(Point());
	myPosition = location;
	nextWaypoint = nullptr;
	theGame->addChild(this);
    winSize = Director::getInstance()->getWinSize();
	drawNode = DrawNode::create();
	drawNode->drawCircle(myPosition, winSize.width * 6 / 480, 360, 30, false, 1, 1, Color4F::GREEN);
	drawNode->drawCircle(myPosition, winSize.width * 2 / 480, 360, 30, false, 1, 1, Color4F::GREEN);
	this->addChild(drawNode);
	pathExist = false;
    return true;
}

void Waypoint::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	if(pathExist) return;
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Waypoint::onDraw,this);
	renderer->addCommand(&_customCommand);
}

void Waypoint::onDraw()
{
	if (nextWaypoint)
		drawNode->drawLine(myPosition, nextWaypoint->myPosition, Color4F::GREEN);
	pathExist = true;
}


