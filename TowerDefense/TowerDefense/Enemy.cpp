#include "Enemy.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "CircleComponent.hpp"

Enemy::Enemy(class Game* game) : Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Airplane.png"));

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.0f);
}