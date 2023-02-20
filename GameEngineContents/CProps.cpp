#include "CProps.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "EnumHeader.h"

CProps::CProps() 
{
}

CProps::~CProps() 
{
}

void CProps::AnimChange(std::string_view _Name)
{
	AnimationRender->ChangeAnimation(_Name);
}

void CProps::Start()
{

	AnimationRender = CreateRender(RenderOrder::PROPS);
	{
		//AnimationRender = CreateRender(RenderOrder::PROPS);
		//AnimationRender->SetImage("R_Flag.bmp");
		//AnimationRender->GetImage()->Cut(2, 5);
		//AnimationRender->SetScaleToImage();
		//float4 ImgScale = AnimationRender->GetScale();
		//AnimationRender->SetScale(float4(ImgScale.x / 2*2, ImgScale.y / 5*2));
		AnimationRender->CreateAnimation({.AnimationName = "R_Flag",.ImageName = "R_Flag.bmp" ,.Start = 0, .End = 9 , .InterTime = 0.1f });
	}

	{
		//AnimationRender = CreateRender(RenderOrder::PROPS);
		//AnimationRender->SetImage("L_Flag.bmp");
		//AnimationRender->GetImage()->Cut(2, 5);
		//AnimationRender->SetScaleToImage();
		//float4 ImgScale = AnimationRender->GetScale();
		//AnimationRender->SetScale(float4(ImgScale.x / 2 * 2, ImgScale.y / 5 * 2));
		AnimationRender->CreateAnimation({ .AnimationName = "L_Flag",.ImageName = "L_Flag.bmp" ,.Start = 0, .End = 9 , .InterTime = 0.1f });
	}

	{
		//AnimationRender = CreateRender(RenderOrder::PROPS);
		//AnimationRender->SetImage("Bonfire.bmp");
		//AnimationRender->GetImage()->Cut(1, 3);
		//AnimationRender->SetScaleToImage();
		//float4 ImgScale = AnimationRender->GetScale();
		//AnimationRender->SetScale(float4(ImgScale.x / 1 , ImgScale.y / 3 ));
		AnimationRender->CreateAnimation({ .AnimationName = "Bonfire",.ImageName = "Bonfire.bmp" ,.Start = 0, .End = 2 , .InterTime = 0.1f });
	}

	{
		//AnimationRender = CreateRender(RenderOrder::PROPS);
		//AnimationRender->SetImage("Candle.bmp");
		//AnimationRender->GetImage()->Cut(2, 2);
		//AnimationRender->SetScaleToImage();
		//float4 ImgScale = AnimationRender->GetScale();
		//AnimationRender->SetScale(float4(ImgScale.x / 2 , ImgScale.y / 2 ));
		AnimationRender->CreateAnimation({ .AnimationName = "Candle",.ImageName = "Candle.bmp" ,.Start = 0, .End = 3 , .InterTime = 0.1f });
	}
}

void CProps::Update(float _DeltaTime)
{
	size_t CutCount = AnimationRender->GetImage()->GetImageCuttingCount();
	AnimationRender->SetScaleToImage();
	AnimationRender->SetScale({ AnimationRender->GetScale().x / CutCount,AnimationRender->GetScale().y / CutCount });
}

