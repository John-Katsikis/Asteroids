#include "GameWorld.h"
#include "GameObject.h"

bool GameObject::mRenderDebug = true;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Default constructor. */
GameObject::GameObject(char const * const type_name)
	: mType(type_name),
	  mWorld(NULL),
	  mPosition(0,0,0),
	  mVelocity(0,0,0),
	  mAcceleration(0,0,0),
	  mAngle(0),
	  mRotation(0),
	  mScale(1)
{
}

/** Construct game object with given position, velocity, acceleration, angle and rotation. */
GameObject::GameObject(char const * const type_name, GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: mType(type_name),
	  mWorld(NULL),
	  mPosition(p),
	  mVelocity(v),
	  mAcceleration(a),
	  mAngle(h),
	  mRotation(r),
	  mScale(1)
{
}

/** Copy constructor. */
GameObject::GameObject(const GameObject& o)
	: mType(o.mType.GetTypeName()),
	  mWorld(o.mWorld),
	  mPosition(o.mPosition),
	  mVelocity(o.mVelocity),
	  mAcceleration(o.mAcceleration),
	  mAngle(o.mAngle),
	  mRotation(o.mRotation),
	  mScale(o.mScale)
{
}

/** Destructor. */
GameObject::~GameObject(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Reset this game object back to the center of the game world. */
void GameObject::Reset()
{
	SetPosition(GLVector3f(0,0,0));
	SetVelocity(GLVector3f(0,0,0));
	SetAcceleration(GLVector3f(0,0,0));
	SetAngle(0);
	SetRotation(0);
}

void GameObject::OrderDestruction() {
	//mWorld->FlagForRemoval(GetThisPtr());
}

/** Update this game object by updating position, velocity and angle of object. */
void GameObject::Update(int t)
{
	// Calculate seconds since last update
	float dt = t / 1000.0f;
	// Update angle
	AddAngle(mRotation * dt);
	// Update position
	AddPosition(mVelocity * dt);
	// Update velocity
	AddVelocity(mAcceleration * dt);
	// Update sprite if one exists
	if (mSprite.get() != NULL) mSprite->Update(t);
	// If in world, wrap position
	if (mWorld) { mWorld->WrapXY(mPosition.x, mPosition.y); }
}

/** Set up rendering system ready to render object. */
void GameObject::PreRender(void)
{
	// Push current transformation matrix onto stack
	glPushMatrix();
	// Translate drawing position to ship's position
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	// Rotate drawing around Z-axis to ship's angle
	glRotatef(mAngle,0,0,1);
	// Scale drawing to scale
	glScalef(mScale, mScale, mScale);
}

/** Render debug graphics if required. */
void GameObject::Render(void)
{
	if (mShape.get() != NULL) mShape->Render();
	if (mSprite.get() != NULL) mSprite->Render();
}


/** Clear up after rendering game object. */
void GameObject::PostRender(void)
{
	// Restore projection matrix from stack
	glPopMatrix();
}