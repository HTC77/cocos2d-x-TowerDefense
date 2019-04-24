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
		towerBase->setPosition(Vec2(winSize.width * x / 480, winSize.height * y / 320));
		this->addChild(towerBase);
		towerBases.pushBack(towerBase);
	}
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
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
