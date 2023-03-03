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
	pLogoRender = CreateRender("title_logo.bmp", RenderOrder::MIDGROUND);
	pLogoRender->SetPosition({ GameEngineWindow::GetScreenSize().half() });
	pLogoRender->SetScale({ 784,222 });
	pLogoRender->SetMove({ 0,-pLogoRender->GetScale().hy() });

	pBlackScreenRender = CreateRender("BlackScreen.bmp", RenderOrder::BACKGROUND);
	pBlackScreenRender->SetPosition({ GameEngineWindow::GetScreenSize().half() });
	pBlackScreenRender->SetScaleToImage();
	
	pStartRender = CreateRender("BlackScreen.bmp", RenderOrder::PARTICLE);
	pStartRender->SetPosition({ GameEngineWindow::GetScreenSize().half().x+100,0 });
	pStartRender->SetScale({396,20});
	//pStartRender->Off();


}

void CTitleLogo::Update(float _Deltatime)
{
	if (214 == pLogoRender->GetPosition().iy())
	{
		return;
	}

	if (214 >= pLogoRender->GetPosition().iy())
	{
		MoveSpeed = 0.f;
		pStartRender->On();
	}
	else
	{
		pLogoRender->SetMove(float4::Up * MoveSpeed * _Deltatime);		
	}
}

