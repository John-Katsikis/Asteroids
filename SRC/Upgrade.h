#ifndef __UPGRADE_H__
#define __UPGRADE_H__

#include "GameObject.h"

class Upgrade : public GameObject
{
public:
	Upgrade(void);
	~Upgrade(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

};

#endif
