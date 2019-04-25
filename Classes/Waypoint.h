#ifndef __TowerDefense__Waypoint__
#define __TowerDefense__Waypoint__

#include "cocos2d.h"
class HelloWorld;
USING_NS_CC;

class Waypoint : public Node
{
public:
	static Waypoint* createWithTheGame(HelloWorld* _game, Vec2 location);
    virtual bool initWithTheGame(HelloWorld* _game, Vec2 location);
    
    Size winSize;
	Vec2 myPosition;
	Waypoint* nextWaypoint;
	HelloWorld* theGame;
	void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;
	CustomCommand _customCommand;
	void onDraw();
	DrawNode* drawNode;
	bool pathExist;
};

#endif // __TowerDefense__Waypoint__
