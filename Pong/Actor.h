#pragma once

#include <vector>
#include <algorithm>
#include "Game.h"
#include "Component.h"
#include "Common.h"
#include "Vector2.h"

using namespace std;

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update method called from Game (not overridable)
	void update(float deltaTime);

	// Update all the components attached to the actor (not overridable)
	void updateComponents(float deltaTime);

	// Any actor-specific update code (overridable)
	virtual void updateActor(float deltaTime);

	// Process input for actor
	void processInput(const Uint8* state);

	// Process input for components of actor
	void processInputComponents(const Uint8* state);

	// Process input custom behavior for actor
	virtual void processInputActor(const Uint8* state);

	void render();

	void renderComponents();

	virtual void renderActor();

	// Add component
	void addComponent(class Component* component);
	
	// Remove component
	void removeComponent(class Component* component);

	// Get/Set Position
	const Vector2& getPosition() const;
	void setPosition(const Vector2& position);

	// Get/Set Scale
	float getScale() const;
	void setScale(float scale);

	// Get/Set Rotation
	float getRotation() const;
	void setRotation(float rotation);

	// Get/Set State
	State getState() const;
	void setState(State state);

protected:
	// Actor state
	State mState;

	// Transform
	// Center position of actor
	Vector2 mPosition; 

	// Uniforms scale of actor (1.0f for 100%)
	float mScale;

	// Rotation angle (in radians)
	float mRotation;

	// Components held by this actor
	vector<class Component*> mComponents;

	class Game* mGame;
};

