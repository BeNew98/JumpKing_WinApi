#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
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
	GameEngineInput::CreateKey("Jump", ' ');


	m_pAnimationRender = CreateRender(RenderOrder::PLAYER);
	
	m_pAnimationRender->SetScale({ 148,148 });

	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_Move",.ImageName = "L_basecut.bmp",.Start = 1,.End = 3,.InterTime = 0.1f });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_Move",.ImageName = "R_basecut.bmp",.Start = 1,.End = 3,.InterTime = 0.1f });

	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_Idle",.ImageName = "L_basecut.bmp",.Start = 0,.End = 0, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_Idle",.ImageName = "R_basecut.bmp",.Start = 0,.End = 0, });


	{
		m_pBodyCollision = CreateCollision(RenderOrder::PLAYER);
		m_pBodyCollision->SetScale({ 40, 40 });
		m_pBodyCollision->SetPosition({ 0,-25 });
		m_pBodyCollision->SetDebugRenderType(CT_Rect);
	}

	ChangeState(PlayerState::IDLE);

}

void CPlayer::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	Movecalculation(_DeltaTime);
}

void CPlayer::DirCheck(const std::string_view& _AnimationName)
{
	std::string sPrevDir = m_DirString;

	m_pAnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());

	if (GameEngineInput::IsPress("LeftMove"))
	{
		m_DirString = "L_";
	}
	else if (GameEngineInput::IsPress("RightMove"))
	{
		m_DirString = "R_";
	}

	if (sPrevDir != m_DirString)
	{
		m_pAnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
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
	if (false == m_bGround)
	{
		m_MoveDir += float4::Down * m_fGravity * _DeltaTime;
	}
	else
	{
		m_MoveDir = float4::Zero;
	}

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir.x *= 0.01f;
	}

	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("1_col.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	//예상위치
	float4 NextPos =GetPos() + m_MoveDir * _DeltaTime;

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		m_bGround = true;
	}	

	SetMove(m_MoveDir * _DeltaTime);
}