#include "CPixelCheck.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"

CPixelCheck::CPixelCheck() 
{
}

CPixelCheck::~CPixelCheck() 
{
}

void CPixelCheck::Start()
{
	//SetMove(float4{ 0, -GameEngineWindow::GetScreenSize().y });


	float4 StartPos = GameEngineWindow::GetScreenSize().half();
	StartPos.y -= GameEngineWindow::GetScreenSize().y;
	

	{
		m_pColMap0 = CreateRender(RenderOrder::DEBUG);
		m_pColMap0->SetImage("1_Col.Bmp");
		m_pColMap0->SetPosition(StartPos);
		m_pColMap0->SetScaleToImage();
	}
}

