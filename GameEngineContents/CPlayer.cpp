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

	//Jump = GameEngineResources::GetInst().SoundPlayToControl("king_land.wav");
	//Jump.Stop();

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
	if (false==(ColDownAll()|| ColDownAll(m_Sky) || ColDownAll(m_Green)))
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

		if (ColDownAll(m_Sky) && 0 != m_MoveDir.x)
		{
			float4 Friction = -m_MoveDir;
			if (!Friction.IsZero())
			{
				Friction.Normalize();
				Friction *= (m_fMoveSpeed * 2.0f)*_DeltaTime;
			}

			if (m_MoveDir.Size() <= Friction.Size())
			{
				m_MoveDir = float4(0.f, 0.f);
			}
			else
			{
				// 현재 속도 반대방향으로 마찰의 의한 속도 감소
				m_MoveDir += Friction;
			}
		}
		
	}


	UpdateState(_DeltaTime);


	//디버깅용화면 출력 땅에 닿았는지 확인
	if (ColDownAll() || ColDownAll(m_Sky) || ColDownAll(m_Green))
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

	std::string MousePos = "MousePos : ";
	MousePos += GetLevel()->GetMousePosToCamera().ToString();

	GameEngineLevel::DebugTextPush(Ground);
	GameEngineLevel::DebugTextPush(Wall);
	GameEngineLevel::DebugTextPush(Dir);
	GameEngineLevel::DebugTextPush(PlayerPos);
	GameEngineLevel::DebugTextPush(MousePos);
}


bool CPlayer::ColCurDown(Color _Color)
{
	return ColCurDL(_Color) || ColCurDR(_Color);
}

void CPlayer::FloorCalibration()
{
	// 바닥에 박힌거 올리기
	while ((ColCurDownAll()|| ColCurDownAll(m_Sky) || ColCurDownAll(m_Green)) && false == ColCurUpAll())
	{
		SetPos(GetPos() + float4::Up);
		pPosUpdate();
	}
}

void CPlayer::WallCalibration() 
{
	// 벽에 박힌거 빼기
	while (ColCurDL() && false == ColCurDR())
	{
		SetPos(GetPos() + float4::Right);
		pPosUpdate();
	}

	// 벽에 박힌거 빼기
	while (ColCurDR() && false == ColCurDL())
	{
		SetPos(GetPos() + float4::Left);
		pPosUpdate();
	}

	while (ColCurUL() && false == ColCurUR())
	{
		SetPos(GetPos() + float4::Right);
		pPosUpdate();
	}

	// 벽에 박힌거 빼기
	while (ColCurUR() && false == ColCurUL())
	{
		SetPos(GetPos() + float4::Left);
		pPosUpdate();
	}
}

bool CPlayer::ColCurDownAll(Color _Color)
{
	int iStart = pPos.fCurDLPos.ix();
	int iEnd = pPos.fCurDRPos.ix() + 1;
	float YPos = pPos.fCurDLPos.y;
	bool Col = false;

	for (;iStart < iEnd; ++iStart)
	{		
		if (RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(float4{ static_cast<float>(iStart),YPos }, RGB(_Color.R, _Color.G, _Color.B)))
		{
			return true;
		}
	};
	return false;
}

bool CPlayer::ColCurUpAll(Color _Color)
{
	int iStart = pPos.fCurULPos.ix();
	int iEnd = pPos.fCurURPos.ix() + 1;
	float YPos = pPos.fCurULPos.y;
	bool Col = false;

	for (; iStart < iEnd; ++iStart)
	{
		if (RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(float4{ static_cast<float>(iStart),YPos }, RGB(_Color.R, _Color.G, _Color.B)))
		{
			return true;
		}
	};
	return false;
}

bool CPlayer::ColLeftUp(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fLeftUpPos, RGB(_Color.R, _Color.G, _Color.B));
}

bool CPlayer::ColRightUp(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fRightUpPos, RGB(_Color.R, _Color.G, _Color.B));
}

bool CPlayer::ColLeftDown(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fLeftDownPos, RGB(_Color.R, _Color.G, _Color.B));
}

bool CPlayer::ColDownR(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fDownRPos, RGB(_Color.R, _Color.G, _Color.B));
}

bool CPlayer::ColDownL(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fDownLPos, RGB(_Color.R, _Color.G, _Color.B));
}


bool CPlayer::ColCurDR(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fCurDRPos, RGB(_Color.R, _Color.G, _Color.B));

}

bool CPlayer::ColCurDL(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fCurDLPos, RGB(_Color.R, _Color.G, _Color.B));
}


bool CPlayer::ColCurUR(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fCurURPos, RGB(_Color.R, _Color.G, _Color.B));

}

bool CPlayer::ColCurUL(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fCurULPos, RGB(_Color.R, _Color.G, _Color.B));
}


bool CPlayer::ColUpR(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fUpRPos, RGB(_Color.R, _Color.G, _Color.B));
}

bool CPlayer::ColUpL(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fUpLPos, RGB(_Color.R, _Color.G, _Color.B));
}

bool CPlayer::ColRightDown(Color _Color)
{
	return RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(pPos.fRightDownPos, RGB(_Color.R, _Color.G, _Color.B));
}

bool CPlayer::ColLeftAll(Color _Color)
{
	return ColLeftUp(_Color) || ColLeftDown(_Color);
}

bool CPlayer::ColRightAll(Color _Color)
{
	return ColRightUp(_Color) || ColRightDown(_Color);
}

bool CPlayer::ColUpAll(Color _Color)
{
	int iStart = pPos.fUpLPos.ix();
	int iEnd = pPos.fUpRPos.ix() + 1;
	float YPos = pPos.fUpLPos.y;
	bool Col = false;

	for (; iStart < iEnd; ++iStart)
	{
		if (RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(float4{ static_cast<float>(iStart),YPos }, RGB(_Color.R, _Color.G, _Color.B)))
		{
			return true;
		}
	};
	return false;
}

bool CPlayer::ColDownAll(Color _Color)
{
	int iStart = pPos.fDownLPos.ix();
	int iEnd = pPos.fDownRPos.ix() + 1;
	float YPos = pPos.fDownLPos.y;
	bool Col = false;

	for (; iStart < iEnd; ++iStart)
	{
		if (RGB(_Color.R, _Color.G, _Color.B) == m_pColImage->GetPixelColor(float4{ static_cast<float>(iStart),YPos }, RGB(_Color.R, _Color.G, _Color.B)))
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
}