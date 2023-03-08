#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRender;
class CEndGround : public GameEngineActor
{
public:
	// constrcuter destructer
	CEndGround();
	~CEndGround();

	// delete Function
	CEndGround(const CEndGround& _Other) = delete;
	CEndGround(CEndGround&& _Other) noexcept = delete;
	CEndGround& operator=(const CEndGround& _Other) = delete;
	CEndGround& operator=(CEndGround&& _Other) noexcept = delete;

protected:
	virtual void Start() override;

private:

};

