#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CTitleLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	CTitleLogo();
	~CTitleLogo();

	// delete Function
	CTitleLogo(const CTitleLogo& _Other) = delete;
	CTitleLogo(CTitleLogo&& _Other) noexcept = delete;
	CTitleLogo& operator=(const CTitleLogo& _Other) = delete;
	CTitleLogo& operator=(CTitleLogo&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _Deltatime) override;

private:
	float MoveSpeed = 10.f;
	GameEngineRender* pLogoRender = nullptr;
	GameEngineRender* pBlackScreenRender = nullptr;
	GameEngineRender* pStartRender = nullptr;
	int Alpha = 0;
	float m_Time = 0.f;
	bool m_bShock = false;
	float m_fShockTime = 0.f;
	float4 ShockPos = float4::Zero;
};

