#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "EnumHeader.h"

// Ό³Έν :
class GameEngineRender;
class GameEngineCollision;
class CAngel : public GameEngineActor
{
public:
	// constrcuter destructer
	CAngel();
	~CAngel();

	static CAngel* MainAngel;

	bool IsEnd()
	{
		return Act.Act0;
	}
	// delete Function
	CAngel(const CAngel& _Other) = delete;
	CAngel(CAngel&& _Other) noexcept = delete;
	CAngel& operator=(const CAngel& _Other) = delete;
	CAngel& operator=(CAngel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	EndingAct Act;
	float		m_EndTime = 0.f;
	GameEngineRender* m_pAnimationRender = nullptr;
	GameEngineCollision* m_pBodyCollision = nullptr;
};

