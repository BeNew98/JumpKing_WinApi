#include "CFlag.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "EnumHeader.h"

CFlag::CFlag()
{
}

CFlag::~CFlag()
{
}

void CFlag::Start()
{

	AnimationRender = CreateRender(RenderOrder::PROPS);	
	AnimationRender->SetScale({ 192,64 });
	AnimationRender->CreateAnimation({ .AnimationName = "R_Flag",.ImageName = "R_Flag.bmp" ,.Start = 0, .End = 9 , .InterTime = 0.1f});
	AnimationRender->ChangeAnimation("R_Flag");



	AnimationRender->SetPosition(AnimationRender->GetScale().half());
}
