#include "Actor.h"


Actor::Actor(Game* game): 
	mState(EActive),
	mPosition(Vector2::Zero),
	mScale(1.0f),
	mRotation(0.0f),
	mGame(game)
{
	mGame->addActor(this);
}

Actor::~Actor()
{
	mGame->removeActor(this);
	// Need to delete components
	// Because ~Component calls removeComponent, need a different style loop
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

void Actor::update(float deltaTime)
{
	if (mState == EActive) {
		updateComponents(deltaTime);
		updateActor(deltaTime);
	}
}

void Actor::updateComponents(float deltaTime)
{
	for (auto component : mComponents) {
		component->update(deltaTime);
	}
}

void Actor::updateActor(float deltaTime)
{
}

void Actor::processInput(const Uint8* state)
{
	if (mState == EActive) {
		processInputComponents(state);
		processInputActor(state);
	}
}

void Actor::processInputComponents(const Uint8* state)
{
	for (auto component : mComponents) {
		component->processInput(state);
	}
}

void Actor::processInputActor(const Uint8* state)
{
}

void Actor::render()
{
	if (mState == EActive) {
		renderComponents();
		renderActor();
	}
}

void Actor::renderComponents()
{
	for (auto component : mComponents) {
		component->render();
	}
}

void Actor::renderActor()
{
}

void Actor::addComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->getUpdateOrder();
	auto it = mComponents.begin();

	for (; it != mComponents.end(); ++it) {
		if (myOrder < (*it)->getUpdateOrder()) {
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(it, component);
}

void Actor::removeComponent(Component* component)
{
	auto it = find(mComponents.begin(), mComponents.end(), component);
	if (it != mComponents.end()) {
		mComponents.erase(it);
	}
}

const Vector2& Actor::getPosition() const
{
	return mPosition;
}

void Actor::setPosition(const Vector2& position)
{
	mPosition = position;
}

float Actor::getScale() const
{
	return mScale;
}

void Actor::setScale(float scale)
{
	mScale = scale;
}

float Actor::getRotation() const
{
	return mRotation;
}

void Actor::setRotation(float rotation)
{
	mRotation = rotation;
}

Actor::State Actor::getState() const
{
	return mState;
}

void Actor::setState(State state)
{
	mState = state;
}
