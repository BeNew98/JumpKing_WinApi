#include "CAngel.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "CBabe.h"
#include "EnumHeader.h"

CAngel* CAngel::MainAngel = nullptr;

CAngel::CAngel() 
{
}

CAngel::~CAngel() 
{
}

void CAngel::Start()
{
	MainAngel = this;

	m_pAnimationRender = CreateRender(RenderOrder::BABE);
	m_pAnimationRender->SetScale({ 64,22 });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "angelIdle",.ImageName = "angel.bmp",.Start = 0,.End = 1,.InterTime = 0.1f, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "angelMove",.ImageName = "angel.bmp",.Start = 2,.End = 3,.InterTime = 0.1f, });
	m_pAnimationRender->ChangeAnimation("angelidle");


	{
		m_pBodyCollision = CreateCollision(CollisionOrder::ANGEL);
		m_pBodyCollision->SetScale({ 20,20 });
		m_pBodyCollision->SetPosition({ 0,10 });
		m_pBodyCollision->SetDebugRenderType(CT_Rect);
	}
}

void CAngel::Update(float _DeltaTime)
{
	if (CBabe::MainBabe->IsEnd()&& Act.Act0 == false)
	{
		SetMove((float4{ 673,70 } - GetPos())*2.f * _DeltaTime);
		m_EndTime += _DeltaTime;	
		if (m_EndTime>4.f)
		{
			m_EndTime = 0.f;
			Act.Act0 = true;
		}
	}

	if (Act.Act0 && m_pBodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PLAYER) })&& Act.Act1 == false)
	{
		Act.Act1 = true;
				
	}

	if (Act.Act1==true&& Act.Act2 == false)
	{
		m_EndTime += _DeltaTime;
		if (m_EndTime > 0.5f)
		{
			m_pAnimationRender->ChangeAnimation("angelMove");
		}
		if (m_EndTime > 2.f)
		{
			SetMove((float4{ 1200, -300 } - GetPos()) * 2.f * _DeltaTime);
		}
	}
}

