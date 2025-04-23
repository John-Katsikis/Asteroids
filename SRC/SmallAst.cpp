#include <stdlib.h>
#include "GameUtil.h"
#include "SmallAst.h"
#include "BoundingShape.h"

SmallAst::SmallAst(void) : GameObject("Small Asteroid")
{
	mAngle = rand() % 360;
	mRotation = 0; // rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD * mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD * mAngle);
	mVelocity.z = 0.0;
}

SmallAst::~SmallAst(void)
{
}

void SmallAst::OrderDestruction() {
	mWorld->FlagForRemoval(GetThisPtr());
}

bool SmallAst::CollisionTest(shared_ptr<GameObject> o)
{
//	if (GetType() == o->GetType()) return false;
	if (o->GetType() == GameObjectType("Bullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void SmallAst::OnCollision(const GameObjectList& objects)
{
	if (objects.front()->GetType() == GameObjectType("Small Asteroid")) {

			if (id < objects.front()->id) {
			//	mWorld->FlagForRemoval(GetThisPtr());
				swap(mVelocity.x, objects.front()->mVelocity.x);
				swap(mVelocity.y, objects.front()->mVelocity.y);
				
			}
		}
		else if (objects.front()->GetType() == GameObjectType("Spaceship")) {
			
		}
		else if (objects.front()->GetType() == GameObjectType("Asteroid")) {
			swap(mVelocity.x, objects.front()->mVelocity.x);
			swap(mVelocity.y, objects.front()->mVelocity.y);
			//	mVelocity.x *= 2;
				//mVelocity.y *= 2;
	}
	//	else {   
	//		mWorld->FlagForRemoval(GetThisPtr());
	//	}
	
	}
