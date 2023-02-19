#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CForeGround : public GameEngineActor
{
public:
	// constrcuter destructer
	CForeGround();
	~CForeGround();

	// delete Function
	CForeGround(const CForeGround& _Other) = delete;
	CForeGround(CForeGround&& _Other) noexcept = delete;
	CForeGround& operator=(const CForeGround& _Other) = delete;
	CForeGround& operator=(CForeGround&& _Other) noexcept = delete;

protected:
	virtual void Start() override;

private:

};

