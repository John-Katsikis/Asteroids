#include "GameUtil.h"
#include "GameWorld.h"
#include "Bullet.h"
#include "Spaceship.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
Spaceship::Spaceship()
	: GameObject("Spaceship"), mThrust(0)
{
	isUpgraded = false;
	isInvincible = false;
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
Spaceship::Spaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Spaceship", p, v, a, h, r), mThrust(0)
{
}

/** Copy constructor. */
Spaceship::Spaceship(const Spaceship& s)
	: GameObject(s), mThrust(0)
{
}

/** Destructor. */
Spaceship::~Spaceship(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////


void Spaceship::applyUpgrades() {
	isUpgraded = true;
}

void Spaceship::stripUpgrades() {
	isUpgraded = false;
}

void Spaceship::makeInvincible() {
	isInvincible = true;
}

void Spaceship::makeNOT() {
	isInvincible = false;
}

/** Update this spaceship. */
void Spaceship::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);
}

/** Render this spaceship. */
void Spaceship::Render(void)
{
	if (mSpaceshipShape.get() != NULL) mSpaceshipShape->Render();

	// If ship is thrusting
	if ((mThrust > 0) && (mThrusterShape.get() != NULL)) {
		mThrusterShape->Render();
	}

	GameObject::Render();
}

/** Fire the rockets. */
void Spaceship::Thrust(float t)
{
	if (!isUpgraded) {
		mThrust = t;
		// Increase acceleration in the direction of ship
		mAcceleration.x = mThrust * cos(DEG2RAD * mAngle);
		mAcceleration.y = mThrust * sin(DEG2RAD * mAngle);
	}
	else {
		mThrust = t*20;
		// Increase acceleration in the direction of ship
		mAcceleration.x = mThrust * cos(DEG2RAD * mAngle);
		mAcceleration.y = mThrust * sin(DEG2RAD * mAngle);
	}
}

void Spaceship::RightThrust(float t) {
	if (!isUpgraded) {
		mThrust = t;
		// Increase acceleration in the right direction of ship
		mAcceleration.x = mThrust * cos(DEG2RAD * (mAngle - 90));
		mAcceleration.y = mThrust * sin(DEG2RAD * (mAngle - 90));
	}
	else {
		mThrust = t*20;
		// Increase acceleration in the right direction of ship
		mAcceleration.x = mThrust * cos(DEG2RAD * (mAngle - 90));
		mAcceleration.y = mThrust * sin(DEG2RAD * (mAngle - 90));
	}
}


void Spaceship::LeftThrust(float t) {
	if (!isUpgraded) {
		mThrust = t;
		// Increase acceleration in the left direction of ship
		mAcceleration.x = mThrust * cos(DEG2RAD * (mAngle + 90));
		mAcceleration.y = mThrust * sin(DEG2RAD * (mAngle + 90));
	}
	else {
		mThrust = t * 20;
		// Increase acceleration in the right direction of ship
		mAcceleration.x = mThrust * cos(DEG2RAD * (mAngle + 90));
		mAcceleration.y = mThrust * sin(DEG2RAD * (mAngle + 90));
	}
}

void Spaceship::Reverse(float t) {
	if (!isUpgraded) {
		mThrust = t;
		// Increase acceleration in the opposite direction of ship
		mAcceleration.x = -(mThrust * cos(DEG2RAD * mAngle));
		mAcceleration.y = -(mThrust * sin(DEG2RAD * mAngle));
	}
	else {
		mThrust = t*20;
		// Increase acceleration in the opposite direction of ship
		mAcceleration.x = -(mThrust * cos(DEG2RAD * mAngle));
		mAcceleration.y = -(mThrust * sin(DEG2RAD * mAngle));
	}
}

/** Set the rotation. */
void Spaceship::Rotate(float r)
{
	if (!isUpgraded){
		mRotation = r;
	}
	else {
		mRotation = r * 2;
	}

}

/** Shoot a bullet. */
void Spaceship::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;

	shared_ptr<Shape> bullet_shape = make_shared<Shape>("bullet.shape");
	SetBulletShape(bullet_shape);

	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f spaceship_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	spaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (spaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 500;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> bullet
		(new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
	bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 2.0f));
	bullet->SetShape(mBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(bullet);

}

/** Shoot a fastBullet. */
void Spaceship::FastShoot(void)
{
	// Check the world exists
	if (!mWorld) return;

	shared_ptr<Shape> bullet_shape = make_shared<Shape>("fastBullet.shape");
	SetBulletShape(bullet_shape);
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f spaceship_heading(cos(DEG2RAD * mAngle), sin(DEG2RAD * mAngle), 0);
	spaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (spaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 1000;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> bullet
	(new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
	bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 2.0f));
	bullet->SetShape(mBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(bullet);

}

bool Spaceship::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid")) return false;
	if (o->GetType() != GameObjectType("Bullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Spaceship::OnCollision(const GameObjectList &objects)
{
	if (objects.front()->GetType() == GameObjectType("Small Asteroid")) {
		if (!isInvincible) {
			swap(mVelocity.x, objects.front()->mVelocity.x);
			swap(mVelocity.y, objects.front()->mVelocity.y);
		}
		else {
			objects.front()->OrderDestruction();
		}
	}
	else if (objects.front()->GetType() == GameObjectType("Asteroid")) {
		if (!isInvincible) {
			mWorld->FlagForRemoval(GetThisPtr());
			objects.front()->OrderDestruction();
		}
		else {
			objects.front()->OrderDestruction();
		}
	}
	else if (objects.front()->GetType() == GameObjectType("ExtraLife")) {

	}
	else {
		mWorld->FlagForRemoval(GetThisPtr());
	}
	}