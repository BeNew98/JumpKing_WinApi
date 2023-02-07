#include "CMidGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"
#include "CPlayLevel.h"


CMidGround::CMidGround() 
{
}

CMidGround::~CMidGround() 
{
}

void CMidGround::Start()
{

	float4 StartPos = GameEngineWindow::GetScreenSize().half();
	//StartPos.y -= GameEngineWindow::GetScreenSize().y;
	{
		m_pRenderMap0 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap0->SetImage("1.Bmp");
		m_pRenderMap0->SetPosition(StartPos);
		m_pRenderMap0->SetScaleToImage();
	}

	/*{
		m_pColMap0 = CreateRender(RenderOrder::DEBUG);
		m_pColMap0->SetImage("1_Col.Bmp");
		m_pColMap0->SetPosition(StartPos);
		m_pColMap0->SetScaleToImage();
	}*/
}

