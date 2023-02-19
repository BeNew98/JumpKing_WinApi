#include "CTitleLogo.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "CBackGround.h"
#include "EnumHeader.h"

CTitleLogo::CTitleLogo() 
{
}

CTitleLogo::~CTitleLogo() 
{
}


void CTitleLogo::Start()
{
	GameEngineRender* pRender = CreateRender("title_logo.bmp", RenderOrder::BACKGROUND);
	pRender->SetPosition({ GameEngineWindow::GetScreenSize().half() });
	pRender->SetScale({ 784,222 });
	
}

