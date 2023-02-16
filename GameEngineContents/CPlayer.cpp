#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
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

void CPlayer::AnimChange(const std::string_view& _AnimationName)
{
	m_pAnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
}

void CPlayer::Render(float _DeltaTime)
{
	ColRender();

	if (GameEngineCore::GetInst()->IsDebug())
	{
	TestRender();
	}
}

void CPlayer::Movecalculation(float _DeltaTime)
{
	m_pColImage = GameEngineResources::GetInst().ImageFind("ColMap.BMP");

	pPosUpdate();

	if (nullptr == m_pColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	// 중력 을 받을때 안받을때 결정
	if (false==ColDownAll())
	{
		m_MoveDir += float4::Down * m_fGravity* _DeltaTime;

		

		//중력 최대 속도 제한
		if (m_MoveDir.y > m_fGravityLimit)
		{
			m_MoveDir.y = m_fGravityLimit;
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


	//디버깅용화면 출력 땅에 닿았는지 확인
	if (ColDownAll())
	{
		m_bGround = true;
	}
	else
	{
		m_bGround = false;
	}

	//디버깅용 벽에 닿았는지 확인
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


bool CPlayer::ColCurDown(int _R, int _G, int _B)
{
	return ColCurDL(_R, _G, _B) || ColCurDR(_R, _G, _B);
}

bool CPlayer::ColCurDownAll(int _R, int _G, int _B)
{
	int iStart = pPos.fCurDLPos.ix();
	int iEnd = pPos.fCurDRPos.ix() + 1;
	float YPos = pPos.fCurDLPos.y;
	bool Col = false;

	for (;iStart < iEnd; ++iStart)
	{		
		if (RGB(_R, _G, _B) == m_pColImage->GetPixelColor(float4{ static_cast<float>(iStart),YPos }, RGB(_R, _G, _B)))
		{
			return true;
		}
	};
	return false;
}

bool CPlayer::ColCurUpAll(int _R, int _G, int _B)
{
	int iStart = pPos.fCurULPos.ix();
	int iEnd = pPos.fCurURPos.ix() + 1;
	float YPos = pPos.fCurULPos.y;
	bool Col = false;

	for (; iStart < iEnd; ++iStart)
	{
		if (RGB(_R, _G, _B) == m_pColImage->GetPixelColor(float4{ static_cast<float>(iStart),YPos }, RGB(_R, _G, _B)))
		{
			return true;
		}
	};
	return false;
}

bool CPlayer::ColLeftUp(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fLeftUpPos, RGB(_R, _G, _B));
}

bool CPlayer::ColRightUp(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fRightUpPos, RGB(_R, _G, _B));
}

bool CPlayer::ColLeftDown(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fLeftDownPos, RGB(_R, _G, _B));
}

bool CPlayer::ColDownR(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fDownRPos, RGB(_R, _G, _B));
}

bool CPlayer::ColDownL(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fDownLPos, RGB(_R, _G, _B));
}


bool CPlayer::ColCurDR(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fCurDRPos, RGB(_R, _G, _B));

}

bool CPlayer::ColCurDL(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fCurDLPos, RGB(_R, _G, _B));
}


bool CPlayer::ColCurUR(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fCurURPos, RGB(_R, _G, _B));

}

bool CPlayer::ColCurUL(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fCurULPos, RGB(_R, _G, _B));
}


bool CPlayer::ColUpR(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fUpRPos, RGB(_R, _G, _B));
}

bool CPlayer::ColUpL(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fUpLPos, RGB(_R, _G, _B));
}

bool CPlayer::ColRightDown(int _R, int _G, int _B)
{
	return RGB(_R, _G, _B) == m_pColImage->GetPixelColor(pPos.fRightDownPos, RGB(_R, _G, _B));
}

bool CPlayer::ColLeftAll(int _R, int _G, int _B)
{
	return ColLeftUp(_R,_G,_B) || ColLeftDown(_R, _G, _B);
}

bool CPlayer::ColRightAll(int _R, int _G, int _B)
{
	return ColRightUp(_R, _G, _B) || ColRightDown(_R, _G, _B);
}

bool CPlayer::ColUpAll(int _R, int _G, int _B)
{
	return ColUpR(_R, _G, _B) || ColUpL(_R, _G, _B);
}

bool CPlayer::ColDownAll(int _R, int _G, int _B)
{
	int iStart = pPos.fDownLPos.ix();
	int iEnd = pPos.fDownRPos.ix() + 1;
	float YPos = pPos.fDownLPos.y;
	bool Col = false;

	for (; iStart < iEnd; ++iStart)
	{
		if (RGB(_R, _G, _B) == m_pColImage->GetPixelColor(float4{ static_cast<float>(iStart),YPos }, RGB(_R, _G, _B)))
		{
			return true;
		}
	};
	return false;
}



void CPlayer::pPosUpdate()
{
	float4 PlayerPos = GetPos();

	// 위 아래 오른쪽 왼쪽에 점을 한개씩 찍어서 픽셀체크에 필요한 좌표를 적용
	pPos.fRightUpPos = PlayerPos + float4::Right + float4{ 20,-40 };
	pPos.fRightDownPos = PlayerPos + float4::Right + float4{ 20,0 };

	pPos.fLeftUpPos = PlayerPos + float4::Left + float4{ -20,-40 };
	pPos.fLeftDownPos = PlayerPos + float4::Left + float4{ -20,0 };

	pPos.fDownLPos = PlayerPos + float4::Down + float4{ -20,0 };
	pPos.fDownRPos = PlayerPos + float4::Down + float4{ 20,0 };

	pPos.fUpLPos = PlayerPos + float4::Up + float4{ -20,-40 };
	pPos.fUpRPos = PlayerPos + float4::Up + float4{ 20,-40 };

	pPos.fCurDLPos = PlayerPos + float4{ -20,0 };
	pPos.fCurDRPos = PlayerPos + float4{ 20,0 };

	pPos.fCurULPos = PlayerPos + float4{ -20,-40 };
	pPos.fCurURPos = PlayerPos + float4{ 20,0 };
