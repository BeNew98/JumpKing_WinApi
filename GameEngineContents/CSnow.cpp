#include "CSnow.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "CPlayer.h"
#include "EnumHeader.h"

CSnow* CSnow::MainSnow = nullptr;

CSnow::CSnow() 
{
}

CSnow::~CSnow() 
{
}

void CSnow::Start()
{
	MainSnow = this;
	SetSnow();
	SetPos(float4::Zero);
}

void CSnow::Update(float _DeltaTime)
{
	float4 PlayerPos = CPlayer::MainPlayer->GetPos();
	float4 SnowPos = GetPos();
	if (false == (PlayerPos.y > 7920.f && PlayerPos.y < 12960.f))
	{
		SetPos(float4::Zero);
		return;
	}
	
	if (PlayerPos.y > 7920.f && PlayerPos.y < 12960.f)
	{
	}
}

void CSnow::SetSnow()
{
	{
		float4 PlusPos = m_StartPos;

		pSnow0 = CreateRender(RenderOrder::PARTICLE);
		pSnow0->SetScale({ 1440,720 });
		pSnow0->SetPosition(PlusPos);
		pSnow0->SetAlpha(150);
		pSnow0->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pSnow0->ChangeAnimation("snow");
		PlusPos.y += 720.f;

		pSnow1 = CreateRender(RenderOrder::PARTICLE);
		pSnow1->SetScale({ 1440,720 });
		pSnow1->SetPosition(PlusPos);
		pSnow1->SetAlpha(150);
		pSnow1->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pSnow1->ChangeAnimation("snow");
		PlusPos.y += 720.f;

		pSnow2 = CreateRender(RenderOrder::PARTICLE);
		pSnow2->SetScale({ 1440,720 });
		pSnow2->SetPosition(PlusPos);
		pSnow2->SetAlpha(150);
		pSnow2->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pSnow2->ChangeAnimation("snow");
		PlusPos.y += 720.f;

		pSnow3 = CreateRender(RenderOrder::PARTICLE);
		pSnow3->SetScale({ 1440,720 });
		pSnow3->SetPosition(PlusPos);
		pSnow3->SetAlpha(150);
		pSnow3->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pSnow3->ChangeAnimation("snow");
		PlusPos.y += 720.f;

		pSnow4 = CreateRender(RenderOrder::PARTICLE);
		pSnow4->SetScale({ 1440,720 });
		pSnow4->SetPosition(PlusPos);
		pSnow4->SetAlpha(150);
		pSnow4->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pSnow4->ChangeAnimation("snow");
		PlusPos.y += 720.f;

		pSnow5 = CreateRender(RenderOrder::PARTICLE);
		pSnow5->SetScale({ 1440,720 });
		pSnow5->SetPosition(PlusPos);
		pSnow5->SetAlpha(150);
		pSnow5->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pSnow5->ChangeAnimation("snow");
		PlusPos.y += 720.f;

		pSnow6 = CreateRender(RenderOrder::PARTICLE);
		pSnow6->SetScale({ 1440,720 });
		pSnow6->SetPosition(PlusPos);
		pSnow6->SetAlpha(150);
		pSnow6->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pSnow6->ChangeAnimation("snow");
		PlusPos.y += 720.f;
	}
}