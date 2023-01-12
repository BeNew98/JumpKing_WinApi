#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"

CPlayer::CPlayer() 
{
}

CPlayer::~CPlayer() 
{
}


void CPlayer::Start()
{
	SetMove(GameEngineWindow::GetScreenSize().half());

	GameEngineRender* pRender = CreateRender("BASECUT.BMP", RenderOrder::PLAYER);
	pRender->SetScale({ 100,100 });
	pRender->SetPosition({ 0,0 });
}

void CPlayer::Update(float _DeltaTime)
{
	//SetMove(float4::Left * 0.001f * _DeltaTime);
}

void CPlayer::Render(float _DeltaTime)
{
	
}