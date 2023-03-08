#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRender;
class CBlackScreen : public GameEngineActor

{
public:
	// constrcuter destructer
	CBlackScreen();
	~CBlackScreen();

	// delete Function
	CBlackScreen(const CBlackScreen& _Other) = delete;
	CBlackScreen(CBlackScreen&& _Other) noexcept = delete;
	CBlackScreen& operator=(const CBlackScreen& _Other) = delete;
	CBlackScreen& operator=(CBlackScreen&& _Other) noexcept = delete;

	void SetFadeIn()
	{
		m_bFadeIn = true;
	}

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	GameEngineRender* pBlackScreenRender = nullptr;
	bool m_bFadeIn = false;
	float m_fTime = 0.f;
	int m_iAlpha = 255;


	void FadeIn(float _DeltaTime);
};

