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

	GameEngineInput::CreateKey("LeftMove", VK_LEFT);
	GameEngineInput::CreateKey("RightMove", VK_RIGHT);
	GameEngineInput::CreateKey("Jump", VK_SPACE);


	m_pAnimationRender = CreateRender(RenderOrder::PLAYER);
	
	m_pAnimationRender->SetScale({ 128,128 });

	//move
	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_Move",.ImageName = "L_basecut.bmp",.Start = 1,.End = 3,.InterTime = 0.12f, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_Move",.ImageName = "R_basecut.bmp",.Start = 1,.End = 3,.InterTime = 0.12f });

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

	//fall
	m_pAnimationRender->CreateAnimation({ .AnimationName = "L_Fall",.ImageName = "L_basecut.bmp",.Start = 7,.End = 7, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "R_Fall",.ImageName = "R_basecut.bmp",.Start = 7,.End = 7, });


	//{
	//	m_pBodyCollision = CreateCollision(RenderOrder::PLAYER);
	//	m_pBodyCollision->SetScale({ 40, 40 });
	//	m_pBodyCollision->SetPosition({ 0,-25 });
	//	m_pBodyCollision->SetDebugRenderType(CT_Rect);
	//}

	ChangeState(PlayerState::FALL);

}

void CPlayer::Update(float _DeltaTime)
{
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
	ColRender();

	TestRender();
}

void CPlayer::Movecalculation(float _DeltaTime)
{
	m_pColImage = GameEngineResources::GetInst().ImageFind("ColMap1~6.BMP");

	// �� �Ʒ� ������ ���ʿ� ���� �Ѱ��� �� �ȼ�üũ�� �ʿ��� ��ǥ�� ����
	pPos.fRightUpPos = GetPos() + float4::Right + float4{ 20,-40 };
	pPos.fRightDownPos = GetPos() + float4::Right + float4{ 20,0 };
	pPos.fLeftUpPos = GetPos() + float4::Left + float4{ -20,-40 };
	pPos.fLeftDownPos = GetPos() + float4::Left + float4{ -20,0 };
	pPos.fDownLPos = GetPos() + float4::Down + float4{ -20,0 };
	pPos.fDownRPos = GetPos() + float4::Down + float4{ 20,0 };
	pPos.fUpLPos = GetPos() + float4::Up + float4{ -20,-40 };
	pPos.fUpRPos = GetPos() + float4::Up + float4{ 20,-40 };
	pPos.fCurLPos = GetPos() + float4{ -20,0 };
	pPos.fCurRPos = GetPos() + float4{ 20,0 };

	if (nullptr == m_pColImage)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}

	// �߷� �� ������ �ȹ����� ����
	if (false==ColDownAll())
	{
		m_MoveDir += float4::Down * m_fGravity* _DeltaTime;
		//m_MoveDir += float4::Down * m_fGravity;
		

		//�߷� �ִ� �ӵ� ����
		if (m_MoveDir.y > 850.f)
		{
			m_MoveDir.y = 850.f;
		}
	}
	else
	{
		if (m_MoveDir.y > 0.f)
		{
			m_MoveDir.y = 0.f;
		}
	}

	UpdateState(_DeltaTime);


	//������ȭ�� ��� ���� ��Ҵ��� Ȯ��
	if (ColDownAll())
	{
		m_bGround = true;
	}
	else
	{
		m_bGround = false;
	}

	//������ ���� ��Ҵ��� Ȯ��
	if (ColLeftAll() || ColRightAll() || ColUpAll())
	{
		m_bWall = true;
	}
	else
	{
		m_bWall = false;
	}


	SetMove(m_MoveDir * _DeltaTime);
}

void CPlayer::ColRender()
{
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 fCamPos = GetLevel()->GetCameraPos();
	float4 fPos = GetPos() - fCamPos;

	Rectangle(DoubleDC,
		fPos.ix() - 5,
		fPos.iy() - 5,
		fPos.ix() + 5,
		fPos.iy() + 5
	);

	{
		pPos += -fCamPos;
		Rectangle(DoubleDC,
			pPos.fRightUpPos.ix() - 2,
			pPos.fRightUpPos.iy() - 2,
			pPos.fRightUpPos.ix() + 2,
			pPos.fRightUpPos.iy() + 2);
		Rectangle(DoubleDC,
			pPos.fRightDownPos.ix() - 2,
			pPos.fRightDownPos.iy() - 2,
			pPos.fRightDownPos.ix() + 2,
			pPos.fRightDownPos.iy() + 2);
		Rectangle(DoubleDC,
			pPos.fLeftUpPos.ix() - 2,
			pPos.fLeftUpPos.iy() - 2,
			pPos.fLeftUpPos.ix() + 2,
			pPos.fLeftUpPos.iy() + 2);
		Rectangle(DoubleDC,
			pPos.fLeftDownPos.ix() - 2,
			pPos.fLeftDownPos.iy() - 2,
			pPos.fLeftDownPos.ix() + 2,
			pPos.fLeftDownPos.iy() + 2);

		Rectangle(DoubleDC,
			pPos.fDownLPos.ix() - 2,
			pPos.fDownLPos.iy() - 2,
			pPos.fDownLPos.ix() + 2,
			pPos.fDownLPos.iy() + 2);
		Rectangle(DoubleDC,
			pPos.fDownRPos.ix() - 2,
			pPos.fDownRPos.iy() - 2,
			pPos.fDownRPos.ix() + 2,
			pPos.fDownRPos.iy() + 2);
		Rectangle(DoubleDC,
			pPos.fUpLPos.ix() - 2,
			pPos.fUpLPos.iy() - 2,
			pPos.fUpLPos.ix() + 2,
			pPos.fUpLPos.iy() + 2);
		Rectangle(DoubleDC,
			pPos.fUpRPos.ix() - 2,
			pPos.fUpRPos.iy() - 2,
			pPos.fUpRPos.ix() + 2,
			pPos.fUpRPos.iy() + 2);
	}
}

void CPlayer::TestRender()
{
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

bool CPlayer::ColCur()
{
	return ColCurR() || ColCurR();
}

bool CPlayer::ColLeftUp()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fLeftUpPos, RGB(0, 0, 0));
}

bool CPlayer::ColRightUp()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fRightUpPos, RGB(0, 0, 0));
}

bool CPlayer::ColLeftDown()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fLeftDownPos, RGB(0, 0, 0));
}

bool CPlayer::ColDownR()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fDownRPos, RGB(0, 0, 0));
}

bool CPlayer::ColDownL()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fDownLPos, RGB(0, 0, 0));
}

bool CPlayer::ColCurR()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fCurRPos, RGB(0, 0, 0));

}

bool CPlayer::ColCurL()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fCurLPos, RGB(0, 0, 0));
}

bool CPlayer::ColUpR()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fUpRPos, RGB(0, 0, 0));
}

bool CPlayer::ColUpL()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fUpLPos, RGB(0, 0, 0));
}

bool CPlayer::ColRightDown()
{
	return RGB(0, 0, 0) == m_pColImage->GetPixelColor(pPos.fRightDownPos, RGB(0, 0, 0));
}

bool CPlayer::ColLeftAll()
{
	return ColLeftUp() || ColLeftDown();
}

bool CPlayer::ColRightAll()
{
	return ColRightUp() || ColRightDown();
}

bool CPlayer::ColUpAll()
{
	return ColUpR() || ColUpL();
}

bool CPlayer::ColDownAll()
{
	return ColDownR() || ColDownL();;
}

