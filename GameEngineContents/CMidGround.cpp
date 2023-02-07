#include "CMidGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"
#include "CPlayLevel.h"

#define BGRender pBGRender = CreateRender(RenderOrder::MIDGROUND);	 \
BGPos.y -= GameEngineWindow::GetScreenSize().y;		 \
pBGRender->SetPosition(BGPos);						 \
ImageNum += 1;										 \
Name = ImageNum;									 \
FullName = Name + BMP;					 \
pBGRender->SetImage(FullName);


CMidGround::CMidGround() 
{
}

CMidGround::~CMidGround() 
{
}

void CMidGround::Start()
{
	//GameEngineRender* pBGRender = nullptr;
	//float4 BGPos = GameEngineWindow::GetScreenSize().half();
	//int ImageNum = 48;
	//std::string Name = "0";
	//std::string BMP = ".Bmp";
	//std::string FullName;
	//BGPos.y += GameEngineWindow::GetScreenSize().y;
	//
	//BGRender;
	//BGRender;
	//BGRender;
	//BGRender;
	//BGRender;
	//BGRender;

	float4 StartPos = GameEngineWindow::GetScreenSize().half();
	StartPos.y -= GameEngineWindow::GetScreenSize().y;
	{
		m_pRenderMap0 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap0->SetImage("1.Bmp");
		m_pRenderMap0->SetPosition(StartPos);
		m_pRenderMap0->SetScaleToImage();
	}

	{
		m_pColMap0 = CreateRender(RenderOrder::DEBUG);
		m_pColMap0->SetImage("1_Col.Bmp");
		m_pColMap0->SetPosition(StartPos);
		m_pColMap0->SetScaleToImage();
	}
}

