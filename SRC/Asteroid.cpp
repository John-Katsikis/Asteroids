#include <stdlib.h>
#include "GameUtil.h"
#include "Asteroid.h"
#include "BoundingShape.h"
#include <memory>    // For std::shared_ptr
#include <vector>    // Or <list> or appropriate header for GameObjectList
#include <algorithm> // For std::swap
#include <iostream>  // For potential debug output


using namespace std;

Asteroid::Asteroid(void) : GameObject("Asteroid")
{
	mAngle = rand() % 360;
	mRotation = 0; // rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}

Asteroid::~Asteroid(void)
{
}

bool Asteroid::CollisionTest(shared_ptr<GameObject> o)
{
	//if (GetType() == o->GetType()) return false;
	if (o->GetType() == GameObjectType("Bullet"))
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Asteroid::OnCollision(const GameObjectList& objects)
{
	//if (objects.front()->GetType() == GameObjectType("Bullet")) {
	//	mVelocity.y = 30;
	//}
	//else{
	
	if (objects.front()->GetType() == GameObjectType("Asteroid")){
		if (this < objects.front().get()) {
			swap(mVelocity.x, objects.front()->mVelocity.x);
			swap(mVelocity.y, objects.front()->mVelocity.y);
		}
	}
	else if (objects.front()->GetType() == GameObjectType("Small Asteroid")){
		swap(mVelocity.x, objects.front()->mVelocity.x);
		swap(mVelocity.y, objects.front()->mVelocity.y);
			mVelocity.x /= 2;
			mVelocity.y /= 2;
	}
	else if (objects.front()->GetType() == GameObjectType("Spaceship")){
		mWorld->FlagForRemoval(GetThisPtr());
	}
	
	else {
		mWorld->FlagForRemoval(GetThisPtr());
	}

		
	//}
}

