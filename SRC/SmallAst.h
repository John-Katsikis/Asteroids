#ifndef __SMALLAST_H__
#define __SMALLAST_H__

#include "GameObject.h"

class SmallAst : public GameObject
{
public:
	SmallAst(int xPos, int yPos);
	~SmallAst(void);

	void OrderDestruction() override;
	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
	
};

#endif
