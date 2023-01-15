#include "CBackGround.h"
#include "EnumHeader.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>


CBackGround::CBackGround() 
{
}

CBackGround::~CBackGround() 
{
}

void CBackGround::Start()
{
	GameEngineRender* pRender = CreateRender("title_logo.bmp", RenderOrder::BACKGROUND);
	pRender->SetPosition({ GameEngineWindow::GetScreenSize().half() });
	pRender->SetScale({ 784,222 });
}

