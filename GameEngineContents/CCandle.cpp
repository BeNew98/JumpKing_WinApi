#include "CCandle.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "EnumHeader.h"

CCandle::CCandle() 
{
}

CCandle::~CCandle() 
{
}

void CCandle::Start()
{
	int iRand = GameEngineRandom::MainRandom.RandomInt(0, 3);
	{
		GameEngineRender* pCandle = CreateRender(RenderOrder::PROPS);
		pCandle->SetScale({ 28, 36 });
		pCandle->CreateAnimation({ .AnimationName = "Candle",.ImageName = "Candle.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f  });
		pCandle->ChangeAnimation("Candle");
	}

	{
		GameEngineRender* pCandle = CreateRender(RenderOrder::PROPS);
		pCandle->SetScale({ 28, 36 });
		pCandle->SetAlpha(100);
		pCandle->CreateAnimation({ .AnimationName = "CandleEffect",.ImageName = "CandleEffect.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.2f });
		pCandle->ChangeAnimation("CandleEffect");
	}
}

