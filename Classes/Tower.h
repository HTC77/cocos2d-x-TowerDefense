#ifndef __TowerDefense__Tower__
#define __TowerDefense__Tower__

#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;
#define kTOWER_COST 300
class Tower : public Node
{
public:
	static Tower* createWithTheGame(HelloWorld* _game, Vec2 location);
    virtual bool initWithTheGame(HelloWorld* _game, Vec2 location);
	Size winSize;
	int attackRange;
	int damage;
	float fireRate;
	HelloWorld* theGame;
	Sprite* mySprite;
	void update(float delta) override;
	
	bool attacking;
	Enemy* chosenEnemy;
	void targetKilled();

	void attackEnemy();
	void shootWeapon(float delta);
	void chosenEnemyForAttack(Enemy* enemy);
	void removeBullet(Sprite* bullet);
	void damageEnemy();
	void lostSightOfEnemy();
};

#endif // __TowerDefense__Tower__
