#ifndef __TowerDefense__Enemy__
#define __TowerDefense__Enemy__

#include "cocos2d.h"
#include "Waypoint.h"
USING_NS_CC;
class Tower;
class Enemy : public Node
{
public:    
    Size visibleSize;
    Size winSize;
    Vec2 origin;
	Vec2 myPosition;
	int maxHp;
	int currentHp;
	float walkingSpeed;
	Waypoint* destinationWaypoint;
	bool active;

	HelloWorld* theGame;
	Sprite *mySprite;
	static Enemy* createWithTheGame(HelloWorld* _game);
	virtual bool initWithTheGame(HelloWorld* _game);

	void doActivate(float delta);
	void getRemoved();
	void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;
	void update(float delta) override;
	void onDraw(const Mat4& transform, uint32_t flags);
	DrawNode* drawNode;
	CustomCommand _customCommand;
	int hBarOrigin, hBarWidth, hBarHeight, hBarDist;
	Vector<Tower*> attackedBy;
	void getAttacked(Tower* attacker);
	void gotLostSight(Tower* attacker);
	void getDamaged(int damage);
};

#endif // __TowerDefense__Enemy__
