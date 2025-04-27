#ifndef __EXTRALIFE_H__
#define __EXTRALIFE_H__

#include "GameObject.h"

class ExtraLife : public GameObject
{
public:
	ExtraLife(void);
	~ExtraLife(void);

	void OrderDestruction();
	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

};

#endif
