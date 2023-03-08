#include "CCompanyLogo.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"

CCompanyLogo::CCompanyLogo() 
{
}

CCompanyLogo::~CCompanyLogo() 
{
}

void CCompanyLogo::Start()
{
	GameEngineRender* pLogo = CreateRender("JK_Nexile_Logo.bmp", RenderOrder::BACKGROUND);
	pLogo->SetPosition({ GameEngineWindow::GetScreenSize().half() });
	pLogo->SetScaleToImage();
}

