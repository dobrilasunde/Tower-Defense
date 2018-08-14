#include "AIState.hpp"
#include "AIComponent.hpp"
#include <SDL_log.h>

void AIIdle::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());
}

void AIIdle::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIIdle::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}

void AIAttack::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());
}

void AIAttack::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIAttack::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}

void AIFly::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());
}

void AIFly::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIFly::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}

void AIDeath::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());
}

void AIDeath::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIDeath::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}