#include "CEndGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"

CEndGround::CEndGround() 
{
}

CEndGround::~CEndGround() 
{
}

void CEndGround::Start()
{
	GameEngineRender* EndImage = CreateRender(RenderOrder::BACKGROUND);
	EndImage->SetImage("imagecrown.bmp");
	EndImage->SetScale(GameEngineWindow::GetScreenSize());

	EndImage->SetMove(EndImage->GetScale().half());
}

