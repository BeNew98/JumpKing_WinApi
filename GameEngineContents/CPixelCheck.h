#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CPixelCheck : public GameEngineActor
{
public:
	// constrcuter destructer
	CPixelCheck();
	~CPixelCheck();

	// delete Function
	CPixelCheck(const CPixelCheck& _Other) = delete;
	CPixelCheck(CPixelCheck&& _Other) noexcept = delete;
	CPixelCheck& operator=(const CPixelCheck& _Other) = delete;
	CPixelCheck& operator=(CPixelCheck&& _Other) noexcept = delete;

	void Start() override;

protected:

private:

	GameEngineRender* m_pColMap0 = nullptr;

};

