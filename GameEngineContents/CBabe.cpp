#include "CBabe.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>

#include "CPlayer.h"
#include "CJump.h"

CBabe* CBabe::MainBabe = nullptr;

CBabe::CBabe() 
{
}

CBabe::~CBabe() 
{
}

void CBabe::Start()
{
	MainBabe = this;

	m_pAnimationRender = CreateRender(RenderOrder::PLAYER);
	m_pAnimationRender->SetScale({ 256,256 });


	m_pAnimationRender->CreateAnimation({ .AnimationName = "BabeIdle",.ImageName = "Babe.bmp",.Start = 1,.End = 3,.InterTime = 0.15f, });
	m_pAnimationRender->CreateAnimation({ .AnimationName = "BabeJumpReady",.ImageName = "Babe.bmp",.Start = 7,.End = 7,});
	m_pAnimationRender->CreateAnimation({ .AnimationName = "BabeJump",.ImageName = "Babe.bmp",.Start = 4,.End = 6 ,.Loop = false});
	m_pAnimationRender->CreateAnimation({ .AnimationName = "BabeKiss",.ImageName = "Babe.bmp",.Start = 0,.End = 0 });
	m_pAnimationRender->ChangeAnimation("BabeIdle");
	
	{
		m_pBodyCollision = CreateCollision(CollisionOrder::BABE);
		m_pBodyCollision->SetScale({ 30,30 });
		m_pBodyCollision->SetPosition({ 0,-30 });
		m_pBodyCollision->SetDebugRenderType(CT_Rect);
	}
}

void CBabe::Update(float _DeltaTime)
{
	if (m_Ending)
	{
		return;
	}
	if (CPlayer::MainPlayer->IsEnd())
	{
		float4 CamPos = GetLevel()->GetCameraPos();
		m_EndTime += _DeltaTime;		
		if (m_EndTime > 5.f && false== Act.Act0)
		{
			m_EndTime = 0.f;
			ChangeState(BabeState::JUMP_READY);
			Act.Act0 = true;
		}
		if (m_EndTime > 1.f&&m_StateValue == BabeState::JUMP_READY&& Act.Act0)
		{
			m_EndTime = 0.f;
			Act.Act1 = true;
			ChangeState(BabeState::JUMP);
		}
		if (Act.Act1&& Act.Act2 ==false)
		{
			if (m_EndTime > 1.f)
			{
			ChangeState(BabeState::MOVE);
			Act.Act2 = true;
			}
		}

		if (Act.Act2 && m_pBodyCollision->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::PLAYER) }) && Act.Act3 == false)
		{
			ChangeState(BabeState::KISS);
			Act.Act3 = true;
		}

		if (m_StateValue == BabeState::KISS)
		{
			m_KissTime += _DeltaTime;
		}

		if (m_KissTime > 1.f)
		{
			ChangeState(BabeState::IDLE);

			m_MoveDir = float4::Right * m_fMoveSpeed;

			if (GetPos().x >= 720.f)
			{
				ChangeState(BabeState::IDLE);
				m_MoveDir = float4::Zero;
				m_Ending = true;
			}
		}
	}
	Movecalculation(_DeltaTime);

	

}

void CBabe::Render(float _DeltaTime)
{
	if (true == CPlayer::MainPlayer->bAct().Act5)
	{
		m_pAnimationRender->Off();
	}
	if (GameEngineCore::GetInst()->IsDebug())
	{
		ColRender();
	}
}


bool CBabe::ColDown()
{
	return RGB(0,0,0) == m_pColImage->GetPixelColor(GetPos(), RGB(0,0,0));
}

void CBabe::Movecalculation(float _DeltaTime)
{
	m_pColImage = GameEngineResources::GetInst().ImageFind("ColMap.BMP");


	if (nullptr == m_pColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	GravityCalculation(_DeltaTime);

	UpdateState(_DeltaTime);

	SetMove(m_MoveDir * _DeltaTime);
}


void CBabe::GravityCalculation(float _DeltaTime)
{// 중력 을 받을때 안받을때 결정
	if (false == ColDown())
	{
		m_MoveDir += float4::Down * m_fGravity * _DeltaTime;



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
}

void CBabe::ColRender()
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
}


void CBabe::ChangeState(BabeState _State)
{
	BabeState NextState = _State;
	BabeState PrevState = m_StateValue;

	m_StateValue = NextState;

	switch (NextState)
	{
	case BabeState::IDLE:
		IdleStart();
		break;
	case BabeState::MOVE:
		MoveStart();
		break;
	case BabeState::JUMP_READY:
		JumpReadyStart();
		break;
	case BabeState::JUMP:
		JumpStart();
		break;
	case BabeState::KISS:
		KissStart();
		break;
	}

	switch (PrevState)
	{
	case BabeState::IDLE:
		IdleEnd();
		break;
	case BabeState::JUMP:
		JumpEnd();
		break;
	case BabeState::JUMP_READY:
		JumpReadyEnd();
		break;
	}
}

void CBabe::UpdateState(float _Time)
{
	switch (m_StateValue)
	{
	case BabeState::IDLE:
		IdleUpdate(_Time);
		break;
	case BabeState::MOVE:
		MoveUpdate(_Time);
		break;
	case BabeState::JUMP_READY:
		JumpReadyUpdate(_Time);
		break;
	case BabeState::JUMP:
		JumpUpdate(_Time);
		break;
	case BabeState::KISS:
		KissUpdate(_Time);
		break;
	}
}

void CBabe::IdleStart()
{
	m_pAnimationRender->ChangeAnimation("BabeIdle");
}

void CBabe::IdleUpdate(float _Time)
{
}

void CBabe::IdleEnd()
{
}

void CBabe::MoveStart()
{
	m_pAnimationRender->ChangeAnimation("BabeIdle");
	//PlayerPos = CPlayer::MainPlayer->GetPos();

}

void CBabe::MoveUpdate(float _Time)
{
	m_MoveDir += float4::Left * m_fMoveSpeed;

	if (m_MoveDir.x<m_fMoveLimit)
	{
		m_MoveDir.x = -m_fMoveLimit;
	}
}

void CBabe::MoveEnd()
{
}

void CBabe::JumpReadyStart()
{
	m_pAnimationRender->ChangeAnimation("BabeJumpReady");
}

void CBabe::JumpReadyUpdate(float _Time)
{
}

void CBabe::JumpReadyEnd()
{
	float4 PlayerPos = GetPos();
	CJump::JumpParticle->AnimChange("JumpParticle", PlayerPos);
}

void CBabe::JumpStart()
{
	m_pAnimationRender->ChangeAnimation("BabeJump");

	GameEngineResources::GetInst().SoundPlay("babe jump.wav");
 
	m_MoveDir += float4::Up * m_fJumpSpeed ;
}

void CBabe::JumpUpdate(float _Time)
{
	if (ColDown()&&m_MoveDir.y == 0)
	{
		GameEngineResources::GetInst().SoundPlay("king_land.wav");
		ChangeState(BabeState::IDLE);
	}
}

void CBabe::JumpEnd()
{
}

void CBabe::KissStart()
{
	m_pAnimationRender->ChangeAnimation("BabeKiss");
	GameEngineResources::GetInst().SoundPlay("babe kiss.wav");
	m_MoveDir = float4::Zero;
}

void CBabe::KissUpdate(float _Time)
{
}

void CBabe::KissEnd()
{
}

