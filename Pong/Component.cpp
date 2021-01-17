#include "Component.h"

Component::Component(class Actor* owner, int updateOrder)
	:mOwner(owner)
	,mUpdateOrder(updateOrder)
{
	mOwner->addComponent(this);
}

Component::~Component()
{
	mOwner->removeComponent(this);
}

void Component::processInput(const Uint8* state)
{
}

void Component::update(float deltaTime)
{
}

void Component::render()
{
}

int Component::getUpdateOrder() const
{
	return mUpdateOrder;
}
