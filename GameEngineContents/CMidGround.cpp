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
	GameEngineRender* pBGRender = nullptr;
	float4 BGPos = GameEngineWindow::GetScreenSize().half();
	int ImageNum = 48;
	std::string Name = "0";
	std::string BMP = ".Bmp";
	std::string FullName;
	BGPos.y -= GameEngineWindow::GetScreenSize().y;

	//나중에 전부 로드하기
	BGRender;
	BGRender;

	//{
	//	GameEngineRender* pBGRender = nullptr;
	//	float4 BGPos = GameEngineWindow::GetScreenSize().half();
	//	int ImageNum = 48;
	//	std::string Name = "0";
	//	std::string BMP = "_COL.Bmp";
	//	std::string FullName;
	//	BGPos.y += GameEngineWindow::GetScreenSize().y;
	//
	//	//나중에 전부 로드하기
	//	BGRender;
	//	BGRender;
	//
	//}
}

