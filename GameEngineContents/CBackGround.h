#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :

class GameEngineCollision;
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
	virtual void Update(float _DeltaTime) override;

private:
	GameEngineRender* EndBG = nullptr;
	GameEngineCollision* m_pBodyCollision = nullptr;
};

