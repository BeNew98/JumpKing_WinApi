#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CMidGround : public GameEngineActor
{
public:
	// constrcuter destructer
	CMidGround();
	~CMidGround();
	

	// delete Function
	CMidGround(const CMidGround& _Other) = delete;
	CMidGround(CMidGround&& _Other) noexcept = delete;
	CMidGround& operator=(const CMidGround& _Other) = delete;
	CMidGround& operator=(CMidGround&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	GameEngineRender* m_pRenderMap0 = nullptr;
	GameEngineRender* m_pRenderMap1 = nullptr;
	GameEngineRender* m_pRenderMap2 = nullptr;
	GameEngineRender* m_pRenderMap3 = nullptr;
	GameEngineRender* m_pRenderMap4 = nullptr;


};

