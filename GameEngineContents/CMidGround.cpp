#include "CMidGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"

CMidGround::CMidGround() 
{
}

CMidGround::~CMidGround() 
{
}

void CMidGround::Start()
{
	GameEngineRender* AnimationRender = CreateRender(RenderOrder::MIDGROUND);
	AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half());
	//AnimationRender->SetScale(GameEngineWindow::GetScreenSize());
	AnimationRender->SetImage("1.Bmp");
}

