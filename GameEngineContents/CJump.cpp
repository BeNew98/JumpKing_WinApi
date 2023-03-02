#include "CJump.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "CPlayer.h"
#include "EnumHeader.h"

CJump* CJump::JumpParticle = nullptr;

CJump::CJump() 
{
}

CJump::~CJump() 
{
}

void CJump::AnimChange(const std::string_view& _AnimationName, float4 _Pos)
{
	SetPos({ _Pos.x, _Pos.y - 25});
	m_pJumpParticle->ChangeAnimation(_AnimationName.data());
}

void CJump::Start()
{
	JumpParticle = this;

	m_pJumpParticle = CreateRender(RenderOrder::PARTICLE);
	m_pJumpParticle->SetScale({ 50,50 });

	//Jump_Particle
	m_pJumpParticle->CreateAnimation({ .AnimationName = "IdleParticle",.ImageName = "jump_particle.bmp",.Start = 5,.End = 5,.Loop = true });
	m_pJumpParticle->CreateAnimation({ .AnimationName = "JumpParticle",.ImageName = "jump_particle.bmp",.Start = 0,.End = 5,.InterTime = 0.07f,.Loop = false  });
	m_pJumpParticle->ChangeAnimation("IdleParticle");
}

void CJump::Update(float _DeltaTime)
{
}

