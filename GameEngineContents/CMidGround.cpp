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
	{
		m_pRenderMap0 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap0->SetImage("1_Col.Bmp");
		m_pRenderMap0->SetPosition(m_pRenderMap0->GetImage()->GetImageScale().half());
		m_pRenderMap0->SetScaleToImage();
	}
}

