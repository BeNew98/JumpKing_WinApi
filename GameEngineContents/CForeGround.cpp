#include "CForeGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include "CColMap.h"
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
	float4 AllMapSize = CColMap::m_MapSize;

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

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg21.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 21 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg22.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 22 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg25.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 25 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg26.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 26 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg27.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 27 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg28.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 28 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg29.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 29 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg30.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 30 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg31.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 31 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg32.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 32 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg36.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 36 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg37.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 37 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg38.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 38 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg39.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 39 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg40.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 40 });

	BG = CreateRender(RenderOrder::FOREGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("fg43.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 43 });
}
