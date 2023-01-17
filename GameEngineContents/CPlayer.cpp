#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
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

	AnimationRender = CreateRender(RenderOrder::PLAYER);
	AnimationRender->SetScale({ 100,100 });

	AnimationRender->CreateAnimation({ .AnimationName = "test0",.ImageName ="basecut.bmp",.Start = 0,.End = 5});
	AnimationRender->CreateAnimation({ .AnimationName = "test1",.ImageName = "basecut.bmp",.Start = 6,.End = 10 });

	AnimationRender->ChangeAnimation("test0");

}

void CPlayer::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		AnimationRender->ChangeAnimation("test1");
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