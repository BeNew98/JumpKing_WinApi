#include "CSnow.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "EnumHeader.h"

CSnow::CSnow() 
{
}

CSnow::~CSnow() 
{
}

void CSnow::Start()
{
	GameEngineRender* pSnow = CreateRender(RenderOrder::PARTICLE);
	pSnow->SetScale({ 480, 480 });
	pSnow->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 1, .End = 1 , .InterTime = 1.f });
	pSnow->ChangeAnimation("snow");



	//pSnow->SetPosition(pSnow->GetScale().half());
}

