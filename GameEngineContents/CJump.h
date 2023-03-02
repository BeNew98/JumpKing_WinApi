#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CJump : public GameEngineActor
{
public:
	// constrcuter destructer
	CJump();
	~CJump();
	
	static CJump* JumpParticle;

	// delete Function
	CJump(const CJump& _Other) = delete;
	CJump(CJump&& _Other) noexcept = delete;
	CJump& operator=(const CJump& _Other) = delete;
	CJump& operator=(CJump&& _Other) noexcept = delete;

	void AnimChange(const std::string_view& _AnimationName , float4 _Pos);

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	GameEngineRender* m_pJumpParticle = nullptr;
};

