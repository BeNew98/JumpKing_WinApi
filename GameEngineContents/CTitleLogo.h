#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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
};

