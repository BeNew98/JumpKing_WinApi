#include "CBackGround.h"
#include "EnumHeader.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "CMidGround.h"


CBackGround::CBackGround() 
{
}

CBackGround::~CBackGround() 
{
}

void CBackGround::Start()
{
	float ImgYSize = 720.f;
	float4 AllMapSize = CMidGround::m_MapSize;

	GameEngineRender* BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg4.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 4 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg5.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 5 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg6.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 6 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg14.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 14 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg15.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 15 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg16.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 16 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg17.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 17 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg18.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 18 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg19.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 19 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg20.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 20 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg21.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 21 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg22.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 22 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg23.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 23 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg24.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 24 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg25.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 25 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg26.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 26 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg27.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 27 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg28.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 28 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg29.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 29 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg30.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 30 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg31.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 31 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg32.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 32 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg36.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 36 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg37.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 37 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg38.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 38 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg39.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 39 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg40.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 40 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg41.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 41 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg42.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 42 });

	BG = CreateRender(RenderOrder::BACKGROUND);
	BG->GameEngineRender::SetImageToScaleToImage("bg43.bmp");
	BG->SetMove(BG->GetScale().half());
	BG->SetMove(float4{ 0,AllMapSize.y - ImgYSize * 43 });
}

