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

	static CSnow* MainSnow;
	float4 m_MoveDir = float4::Zero;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	float4 m_StartPos = { 480,8280 };

	GameEngineRender* pSnow0 = nullptr;
	GameEngineRender* pSnow1 = nullptr;
	GameEngineRender* pSnow2 = nullptr;
	GameEngineRender* pSnow3 = nullptr;
	GameEngineRender* pSnow4 = nullptr;
	GameEngineRender* pSnow5 = nullptr;
	GameEngineRender* pSnow6 = nullptr;

	void SetSnow();
};

