/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Tower.h"

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

void HelloWorld::loadTowerPositions()
{
	towerBases = Vector<Sprite*>(12);
	auto fileUtils = FileUtils::getInstance();
	int x, y;
	ValueMap tempMap;
	ValueVector arrayTPos = fileUtils->getValueVectorFromFile(
		"TowersPosition.plist");
	for (int i = 0; i < arrayTPos.size(); ++i)
	{
		tempMap = arrayTPos.at(i).asValueMap();
		x = tempMap["x"].asInt();
		y = tempMap["y"].asInt();
		auto towerBase = Sprite::create("open_spot-hd.png");
		towerBase->setPosition(Vec2(winSize.width * x / 480,
			winSize.height * y / 320));
		this->addChild(towerBase);
		towerBases.pushBack(towerBase);
	}
}

bool HelloWorld::canBuyTower()
{
	return true;
}

void HelloWorld::addWaypoints()
{
	Waypoint * waypoint1 = Waypoint::createWithTheGame(
		this, Vec2(winSize.width * 420 / 480, winSize.height * 35 / 320));
	waypoints.pushBack(waypoint1);

	Waypoint * waypoint2 = Waypoint::createWithTheGame(
		this, Vec2(winSize.width * 35 / 480, winSize.height * 35 / 320));
	waypoints.pushBack(waypoint2);
	waypoint2->nextWaypoint = waypoint1;

	Waypoint * waypoint3 = Waypoint::createWithTheGame(
		this, Vec2(winSize.width * 35 / 480, winSize.height * 130 / 320));
	waypoints.pushBack(waypoint3);
	waypoint3->nextWaypoint = waypoint2;

	Waypoint * waypoint4 = Waypoint::createWithTheGame(
		this, Vec2(winSize.width * 445 / 480, winSize.height * 130 / 320));
	waypoints.pushBack(waypoint4);
	waypoint4->nextWaypoint = waypoint3;

	Waypoint * waypoint5 = Waypoint::createWithTheGame(
		this, Vec2(winSize.width * 445 / 480, winSize.height * 220 / 320));
	waypoints.pushBack(waypoint5);
	waypoint5->nextWaypoint = waypoint4;

	Waypoint * waypoint6 = Waypoint::createWithTheGame(
		this, Vec2(winSize.width * -40 / 480, winSize.height * 220 / 320));
	waypoints.pushBack(waypoint6);
	waypoint6->nextWaypoint = waypoint5;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();

	// 1 - Initialize
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	// 2 - Set background   
	auto background = Sprite::create("bg-hd.png");
	background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(background);

	// 3 - Load tower positions
	this->loadTowerPositions();

	// 4 - Add waypoints
	this->addWaypoints();

	//this->setScale(0.5);
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 location = Director::getInstance()->convertToGL(touch->getLocationInView());
	for (int i = 0; i < towerBases.size(); ++i)
	{
		Node* tb = towerBases.at(i);
		if(tb->getBoundingBox().containsPoint(location) && this->canBuyTower() && tb->getUserData() == NULL)
		{
			//We will spend our gold later.
			Tower* tower = Tower::createWithTheGame(this, tb->getPosition());
			towers.pushBack(tower);
			tb->setUserData(tower);
		}
	}
	return true;
}
