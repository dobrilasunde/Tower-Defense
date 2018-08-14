#include "Enemy.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "CircleComponent.hpp"
#include "Grid.hpp"
#include "Tile.hpp"
#include "NavComponent.hpp"
#include<algorithm>
#include "AIComponent.hpp"
#include "AIState.hpp"

Enemy::Enemy(class Game* game) : Actor(game)
{
	game->GetEnemies().emplace_back(this);

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Enemy.png"));

	SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());

	NavComponent* nc = new NavComponent(this);
	nc->SetForwardSpeed(150.0f);
	nc->StartPath(GetGame()->GetGrid()->GetStartTile());

	mAI = new AIComponent(this);
	mAI->RegisterState(new AIFly(mAI));
	mAI->RegisterState(new AIDeath(mAI));

	mAI->ChangeState("Fly");

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(), GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Length(), 10.0f))
	{
		mAI->ChangeState("Death");
		SetState(EDead);
	}
}