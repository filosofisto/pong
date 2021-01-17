#pragma once

#include "Actor.h"

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void processInput(const Uint8* state);

	virtual void update(float deltaTime);

	virtual void render();

	int getUpdateOrder() const;

private:
	// Owning actor
	class Actor* mOwner;

	// Update order of component
	int mUpdateOrder;
};

