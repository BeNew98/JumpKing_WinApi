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

	AnimationRender->CreateAnimation({ .AnimationName = "L_Move",.ImageName = "L_basecut.bmp",.Start = 1,.End = 3,.InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "R_Move",.ImageName = "R_basecut.bmp",.Start = 1,.End = 3,.InterTime = 0.1f });

	AnimationRender->CreateAnimation({ .AnimationName = "L_Idle",.ImageName = "L_basecut.bmp",.Start = 0,.End = 0, });
	AnimationRender->CreateAnimation({ .AnimationName = "R_Idle",.ImageName = "R_basecut.bmp",.Start = 0,.End = 0, });

	ChangeState(PlayerState::IDLE);

}

void CPlayer::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	Movecalculation(_DeltaTime);
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

void CPlayer::Movecalculation(float _DeltaTime)
{
	if (false == bGround)
	{
		MoveDir += float4::Down * fGravity * _DeltaTime;
	}
	else
	{
		MoveDir = float4::Zero;
	}

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir.x *= 0.01f;
	}

	// ColMap.BMP 이걸 변수로하면 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("1_col.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	// 내 미래의 위치는 여기인데/.
		
	float4 NextPos =GetPos() + MoveDir * _DeltaTime;

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		bGround = true;
		//MoveDir = float4::Zero;
	}	

	SetMove(MoveDir * _DeltaTime);
}