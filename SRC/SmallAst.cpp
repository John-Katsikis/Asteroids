#include <stdlib.h>
#include "GameUtil.h"
#include "SmallAst.h"
#include "BoundingShape.h"

SmallAst::SmallAst(int xPos, int yPos) : GameObject("Small Asteroid")
{
	mAngle = rand() % 360;
	mRotation = 0; // rand() % 90;
	mPosition.x = xPos;
	mPosition.y = yPos;
	mPosition.z = 0.0;
	mVelocity.x = (rand() % 15) * cos(DEG2RAD * mAngle);
	mVelocity.y = (rand() % 15) * sin(DEG2RAD * mAngle);
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

		else if(objects.front()->GetType() == GameObjectType("Upgrade") || objects.front()->GetType() == GameObjectType("ExtraLife") || objects.front()->GetType() == GameObjectType("Shield")){

		}
	
	}
