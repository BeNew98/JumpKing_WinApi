#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "EnumHeader.h"

CPlayer* CPlayer::MainPlayer = nullptr;

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
	UpdateState(_DeltaTime);
}

void CPlayer::DirCheck(const std::string_view& _AnimationName)
{
	std::string sPrevDir = DirString;

	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());

	if (GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "L_";
	}
	else if (GameEngineInput::IsPress("RightMove"))
	{
		DirString = "R_";
	}

	if (sPrevDir != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
	
}

void CPlayer::Render(float _DeltaTime)
{
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	
	float4 fPos = GetPos() - GetLevel()->GetCameraPos();
	
	Rectangle(DoubleDC,
		fPos.ix() - 5,
		fPos.iy() - 5,
		fPos.ix() + 5,
		fPos.iy() + 5
	);

}