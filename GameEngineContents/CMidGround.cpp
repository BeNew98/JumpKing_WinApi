#include "CMidGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"




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
	int ImageNum = 0;
	std::string Name = "0";
	std::string BMP = ".Bmp";
	BGPos.y += GameEngineWindow::GetScreenSize().y;


	//나중에 전부 로드하기
	pBGRender = CreateRender(RenderOrder::MIDGROUND);
	BGPos.y -= GameEngineWindow::GetScreenSize().y;
	pBGRender->SetPosition(BGPos);
	ImageNum += 49;
	Name = ImageNum;
	std::string FullName = Name + BMP;
	pBGRender->SetImage(FullName);
}

