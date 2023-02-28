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
	{
		GameEngineRender* pSnow = CreateRender(RenderOrder::PARTICLE);
		pSnow->SetScale({ 1440,720 });
		pSnow->SetAlpha(200);

		pSnow->CreateAnimation({ .AnimationName = "snow",.ImageName = "snow.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pSnow->ChangeAnimation("snow");
	}


}

void CSnow::Update(float _DeltaTime)
{
}

