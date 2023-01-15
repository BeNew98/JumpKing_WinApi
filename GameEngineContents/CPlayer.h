#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CPlayer : public GameEngineActor
{
public:
	static CPlayer* MainPlayer;

	// constrcuter destructer
	CPlayer();
	~CPlayer();

	// delete Function
	CPlayer(const CPlayer& _Other) = delete;
	CPlayer(CPlayer&& _Other) noexcept = delete;
	CPlayer& operator=(const CPlayer& _Other) = delete;
	CPlayer& operator=(CPlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	float AccTime = 0.0f;
	int StartFrame = 0;
	float MoveSpeed = 100.0f;
};

