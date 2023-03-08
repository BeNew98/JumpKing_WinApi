#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CPressStart :public GameEngineActor
{
public:
	// constrcuter destructer
	CPressStart();
	~CPressStart();

	// delete Function
	CPressStart(const CPressStart& _Other) = delete;
	CPressStart(CPressStart&& _Other) noexcept = delete;
	CPressStart& operator=(const CPressStart& _Other) = delete;
	CPressStart& operator=(CPressStart&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	float m_fBlink = 0.f;
	float m_fTime = 0.f;
	bool m_bAlpha = false;
	bool m_bLevelChangeReady = false;
	GameEngineRender* pStart = nullptr;
};

