#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CSnow : public GameEngineActor
{
public:
	// constrcuter destructer
	CSnow();
	~CSnow();

	// delete Function
	CSnow(const CSnow& _Other) = delete;
	CSnow(CSnow&& _Other) noexcept = delete;
	CSnow& operator=(const CSnow& _Other) = delete;
	CSnow& operator=(CSnow&& _Other) noexcept = delete;

protected:
	virtual void Start() override;

private:

};

