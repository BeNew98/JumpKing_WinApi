#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :

class CBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	CBackGround();
	~CBackGround();

	// delete Function
	CBackGround(const CBackGround& _Other) = delete;
	CBackGround(CBackGround&& _Other) noexcept = delete;
	CBackGround& operator=(const CBackGround& _Other) = delete;
	CBackGround& operator=(CBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

