#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "EnumHeader.h"

CPlayer* CPlayer::MainPlayer;

CPlayer::CPlayer() 
{
}

CPlayer::~CPlayer() 
{
}


void CPlayer::Start()
{
	MainPlayer = this;

	SetMove(GameEngineWindow::GetScreenSize().half());

	GameEngineInput::CreateKey("LeftMove", 'A');
	GameEngineInput::CreateKey("RightMove", 'D');
	GameEngineInput::CreateKey("DownMove", 'S');
	GameEngineInput::CreateKey("UpMove", 'W');

	GameEngineRender* pRender = CreateRender("BASECUT.BMP", RenderOrder::PLAYER);
	pRender->SetScale({ 100,100 });
	pRender->SetPosition({ 0,0 });
}

void CPlayer::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		SetMove(float4::Left * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("RightMove"))
	{
		SetMove(float4::Right * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("UpMove"))
	{
		SetMove(float4::Up * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("DownMove"))
	{
		SetMove(float4::Down * MoveSpeed * _DeltaTime);
	}
}

void CPlayer::Render(float _DeltaTime)
{
	
}