#include "CForeGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include "CMidGround.h"
#include "EnumHeader.h"

CForeGround::CForeGround() 
{
}

CForeGround::~CForeGround() 
{
}

void CForeGround::Start()
{
	float ImgYSize = 720.f;
	float4 AllMapSize = CMidGround::m_MapSize;

	GameEngineRender* BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg1.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{0,AllMapSize.y- ImgYSize * 1 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg2.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 2 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg3.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 3 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg4.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 4 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg5.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 5 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg6.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 6 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg9.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 9 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg10.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 10 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg16.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 16 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg17.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 17 });

	 BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg18.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 18 });














































}
