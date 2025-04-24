#ifndef __SHIELD_H__
#define __SAHIELD_H__

#include "GameObject.h"

class Shield : public GameObject
{
public:
	Shield(void);
	~Shield(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

};

#endif
