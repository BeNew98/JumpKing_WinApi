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

	GameEngineInput::CreateKey("LeftMove", VK_LEFT);
	GameEngineInput::CreateKey("RightMove", VK_RIGHT);
	GameEngineInput::CreateKey("Jump", VK_SPACE);


	m_pAnimationRender = CreateRender(RenderOrder::PLAYER);
	
	m_pAnimationRender->SetScale({ 148,148 });

	//move
	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_Move",.ImageName = "L_basecut.bmp",.Start = 1,.End = 3,.InterTime = 0.08f, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_Move",.ImageName = "R_basecut.bmp",.Start = 1,.End = 3,.InterTime = 0.08f });

	//idle
	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_Idle",.ImageName = "L_basecut.bmp",.Start = 0,.End = 0, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_Idle",.ImageName = "R_basecut.bmp",.Start = 0,.End = 0, });

	//jumpready
	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_JumpReady",.ImageName = "L_basecut.bmp",.Start = 4,.End = 4, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_JumpReady",.ImageName = "R_basecut.bmp",.Start = 4,.End = 4, });

	//jump
	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_Jump",.ImageName = "L_basecut.bmp",.Start = 5,.End = 5, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_Jump",.ImageName = "R_basecut.bmp",.Start = 5,.End = 5, });

	//down
	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_down",.ImageName = "L_basecut.bmp",.Start = 6,.End = 6, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_down",.ImageName = "R_basecut.bmp",.Start = 6,.End = 6, });

	//Collide
	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_Collide",.ImageName = "L_basecut.bmp",.Start = 8,.End = 8, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_Collide",.ImageName = "R_basecut.bmp",.Start = 8,.End = 8, });


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

	std::string Ground = "Ground : ";
	if (m_bGround)
	{
		Ground += "true";
	}
	else
	{
		Ground += "false";
	}
	
	std::string Wall = "Wall : ";
	if (m_bWall)
	{
		Wall += "true";
	}
	else
	{
		Wall += "false";
	}

	std::string Dir = "Dir : ";
	Dir += m_MoveDir.ToString();

	std::string PlayerPos = "PlayerPos : ";
	PlayerPos += GetPos().ToString();

	std::string CamPos = "CamPos : ";
	CamPos += GetLevel()->GetCameraPos().ToString();

	GameEngineLevel::DebugTextPush(Ground);
	GameEngineLevel::DebugTextPush(Wall);
	GameEngineLevel::DebugTextPush(Dir);
	GameEngineLevel::DebugTextPush(PlayerPos);
	GameEngineLevel::DebugTextPush(CamPos);

}

void CPlayer::Movecalculation(float _DeltaTime)
{
	if (false == m_bGround)
	{
		m_MoveDir += float4::Down * m_fGravity * _DeltaTime;
	}
	else
	{
		if (m_MoveDir.y > 0.f)
		{
			m_MoveDir.y = 0.f;
		}
	}

	if (200.0f <= abs(m_MoveDir.x))
	{
		if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -200.0f;
		}
		else {
			m_MoveDir.x = 200.0f;
		}
	}

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove") && m_bGround)
	{
		m_MoveDir.x = 0.f;
	}

	

	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("1_col.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}

	pPos.NextPos = GetPos() + m_MoveDir;	
	pPos.fDownPos = GetPos() + float4::Down;
	pPos.fUpPos = GetPos() + float4::Up + float4{0,-40};
	pPos.fRightPos = GetPos() + float4::Right+float4{ 20,0 };
	pPos.fLeftPos = GetPos() + float4::Left + float4{ -20,0 };
	pPos.fMyPos = GetPos();

	if (true == GameEngineInput::IsPress("LeftMove") && (RGB(0, 0, 0) == ColImage->GetPixelColor(pPos.fLeftPos, RGB(0, 0, 0) && m_MoveDir.x < 0)) && m_bGround)
	{
		m_MoveDir.x = 0.f;
	}

	if (true == GameEngineInput::IsPress("RightMove") && (RGB(0, 0, 0) == ColImage->GetPixelColor(pPos.fRightPos, RGB(0, 0, 0) && m_MoveDir.x > 0))&&m_bGround)
	{
		m_MoveDir.x = 0.f;
	}

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(pPos.fMyPos, RGB(0, 0, 0)))
	{
		while (RGB(0, 0, 0) == ColImage->GetPixelColor(pPos.fMyPos, RGB(0, 0, 0)))
		{
		SetPos(GetPos()+float4::Up);
		pPos.fMyPos = GetPos();
		}
	}


	//1�ȼ� �Ʒ��� �������̸� ���� ����ִ°�.
	if (RGB(0, 0, 0) == ColImage->GetPixelColor(pPos.fDownPos, RGB(0, 0, 0)))
	{
		m_bGround = true;
		m_iCollide = 0;
	}
	else
	{
		m_bGround = false;
	}

	if ((RGB(0, 0, 0) == ColImage->GetPixelColor(pPos.fRightPos, RGB(0, 0, 0))||
		RGB(0, 0, 0) == ColImage->GetPixelColor(pPos.fLeftPos, RGB(0, 0, 0))||
		RGB(0, 0, 0) == ColImage->GetPixelColor(pPos.fUpPos, RGB(0, 0, 0)))
		&&false == m_bGround)
	{
		m_bWall = true;
	}
	else
	{
		m_bWall = false;
	}

	SetMove(m_MoveDir * _DeltaTime);
}