#include "Tower.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

Tower::Tower(class Game* game) : Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(GetGame()->GetTexture("Assets/Tower.png"));

	mMove = new MoveComponent(this);
	//mMove->SetAngularSpeed(Math::Pi);

	mNextAttack = AttackTime;
}

void Tower::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mNextAttack -= deltaTime;
	if (mNextAttack <= 0)
	{
		Enemy* e = GetGame()->GetNearestEnemy(GetPosition());

		if (e != nullptr)
		{
			Vector2 dir = e->GetPosition() - GetPosition();
			float dist = dir.Length();

			if (dist < AttackRange)
			{
				SetRotation(Math::Atan2(-dir.y, dir.x));
				Bullet* b = new Bullet(GetGame());
				b->SetPosition(GetPosition());
				b->SetRotation(GetRotation());
			}
		}
		mNextAttack = AttackTime;
	}
}