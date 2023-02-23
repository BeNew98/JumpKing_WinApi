#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CFlag : public GameEngineActor
{
public:
	// constrcuter destructer
	CFlag();
	~CFlag();

	// delete Function
	CFlag(const CFlag& _Other) = delete;
	CFlag(CFlag&& _Other) noexcept = delete;
	CFlag& operator=(const CFlag& _Other) = delete;
	CFlag& operator=(CFlag&& _Other) noexcept = delete;

protected:
	virtual void Start() override;


private:
	GameEngineRender* AnimationRender = nullptr;
};

