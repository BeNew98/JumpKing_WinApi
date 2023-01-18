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
	
	AnimationRender->SetScale({ 148,148 });

	AnimationRender->CreateAnimation({ .AnimationName = "L_Move",.ImageName = "L_basecut.bmp",.Start = 1,.End = 3, });
	AnimationRender->CreateAnimation({ .AnimationName = "R_Move",.ImageName = "R_basecut.bmp",.Start = 1,.End = 3, });

	AnimationRender->CreateAnimation({ .AnimationName = "L_Idle",.ImageName = "L_basecut.bmp",.Start = 0,.End = 0, });
	AnimationRender->CreateAnimation({ .AnimationName = "R_Idle",.ImageName = "R_basecut.bmp",.Start = 0,.End = 0, });

	ChangeState(PlayerState::IDLE);

}

void CPlayer::Update(float _DeltaTime)
{
	DirCheck();
	UpdateState(_DeltaTime);


	//if (true == GameEngineInput::IsPress("LeftMove"))
	//{
	//	AnimationRender->ChangeAnimation("L_Move");
	//	SetMove(float4::Left * MoveSpeed * _DeltaTime);
	//}
	//
	//if (true == GameEngineInput::IsPress("RightMove"))
	//{
	//	AnimationRender->ChangeAnimation("R_Move");
	//
	//	SetMove(float4::Right * MoveSpeed * _DeltaTime);
	//}
	//
	//if (true == GameEngineInput::IsPress("UpMove"))
	//{
	//	SetMove(float4::Up * MoveSpeed * _DeltaTime);
	//}
	//
	//if (true == GameEngineInput::IsPress("DownMove"))
	//{
	//	SetMove(float4::Down * MoveSpeed * _DeltaTime);
	//}
}

void CPlayer::DirCheck()
{
	if (true)
	{
		if (GameEngineInput::IsPress("LeftMove"))
		{
			DirString = "L_";
		}
		else if (GameEngineInput::IsPress("RightMove"))
		{
			DirString = "R_";
		}
	}
}

void CPlayer::Render(float _DeltaTime)
{
	HDC DoubleDC = GameEngineWindow::GetWindowBackBufferHdc();

	float4 fPos = GetPos();

	Rectangle(DoubleDC,
		fPos.ix() - 5,
		fPos.iy() - 5,
		fPos.ix() + 5,
		fPos.iy() + 5
	);

}