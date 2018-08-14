#pragma once

class AIState
{
public:
	AIState(class AIComponent* owner) : mOwner(owner) {}
	virtual void Update(float deltaTime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual const char* GetName() const = 0;

protected:
	class AIComponent* mOwner;
};

class AIIdle : public AIState
{
public:
	AIIdle(class AIComponent* owner): AIState(owner) {}
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Idle"; }
};

class AIAttack : public AIState
{
public:
	AIAttack(class AIComponent* owner): AIState(owner) {}
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Attack"; }
};

class AIFly : public AIState
{
public:
	AIFly(class AIComponent* owner) : AIState(owner) {}
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Fly"; }
};


class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* owner) : AIState(owner) {}
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Death"; }
};
