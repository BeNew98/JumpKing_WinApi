#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "EnumHeader.h"

void CPlayer::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = m_StateValue;

	m_StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::IDLE:	
		IdleStart();	
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::JUMP_READY:
		JumpReadyStart();
		break;
	case PlayerState::JUMP:
		JumpStart();
		break;
	case PlayerState::DOWN:
		DownStart();
		break;
	case PlayerState::COLLIDE:
		CollideStart();
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	}
}

void CPlayer::UpdateState(float _Time)
{
	switch (m_StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	case PlayerState::JUMP_READY:
		JumpReadyUpdate(_Time);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_Time);
		break;
	case PlayerState::DOWN:
		DownUpdate(_Time);
		break;
	case PlayerState::COLLIDE:
		CollideUpdate(_Time);
		break;
	}
}

void CPlayer::IdleStart()
{
	// ¹Ù´Ú¿¡ ¹ÚÈù°Å ¿Ã¸®±â
	while (RGB(0, 0, 0) == ColCur())
	{
		SetPos(GetPos() + float4::Up);
		pPos.fMyPos = GetPos();
	}
	DirCheck("Idle");
}

void CPlayer::IdleUpdate(float _Time)
{
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; 
	}

	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP_READY);
		return;
	}

	if (false == GameEngineInput::IsPress("LeftMove") || false == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir.x = 0;
		return;
	}

	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}
}

void CPlayer::IdleEnd()
{

}

void CPlayer::MoveStart()
{
	DirCheck("Move");
}

void CPlayer::MoveUpdate(float _Time)
{
	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove")
		)
	{
		// 
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP_READY);
		return;
	}

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}

	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}

	//º®
	if ((true == GameEngineInput::IsPress("LeftMove") && ColLeft() && m_MoveDir.x < 0))
	{
		m_MoveDir.x = 0.f;
	}

	if ((true == GameEngineInput::IsPress("RightMove") && ColRight() && m_MoveDir.x > 0))
	{
		m_MoveDir.x = 0.f;
	}

	if (170.0f <= abs(m_MoveDir.x))
	{
		if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -170.0f;
		}
		else {
			m_MoveDir.x = 170.0f;
		}
	}

	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}

	DirCheck("Move");


}

void CPlayer::MoveEnd() 
{
	m_MoveDir.x = 0.0f;
}


void CPlayer::JumpReadyStart()
{
	DirCheck("JumpReady");
	m_fJumpPressTime = 0.0f;
}

void CPlayer::JumpReadyUpdate(float _Time)
{	
	if (true == GameEngineInput::IsPress("Jump") && true == m_bGround)
	{
		m_fJumpPressTime = GameEngineInput::GetPressTime("Jump");
	}

	if (true == GameEngineInput::IsUp("Jump") && true == m_bGround)
	{
		ChangeState(PlayerState::JUMP);
	}

	if (m_fJumpPressTime >= 0.6f)
	{
		ChangeState(PlayerState::JUMP);
	}
}
void CPlayer::JumpReadyEnd() {}


void  CPlayer::JumpStart()
{
	DirCheck("Jump");
	if (m_fJumpPressTime < 0.1f)
	{
		m_fJumpPressTime = 0.1f;
	}
	if (true == GameEngineInput::IsPress("LeftMove") && true == m_bGround)
	{
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}
	else if (true == GameEngineInput::IsPress("RightMove") && true == m_bGround)
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}
	m_MoveDir += float4::Up * m_fJumpSpeed * (m_fJumpPressTime/0.6f);

	if (400.0f <= abs(m_MoveDir.x))
	{
		if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -400.0f;
		}
		else 
		{
			m_MoveDir.x = 400.0f;
		}
	}
}

void  CPlayer::JumpUpdate(float _Time)
{
	if (m_bWall&& m_iCollide == 0)
	{
		m_MoveDir.x *= -1;
		++m_iCollide;
	}
	
	if (m_iCollide != 0)
	{
		DirCheck("Collide");
	}

	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}

}

void  CPlayer::JumpEnd()
{
	m_HighestPos = GetPos();
}

void CPlayer::DownStart()
{
	DirCheck("Down");
}
void CPlayer::DownUpdate(float _Time)
{
	if (m_iCollide != 0)
	{
		DirCheck("Collide");
	}

	if (m_bWall)
	{
		m_MoveDir.x *= -1;
	}

	if (m_bGround)
	{	
		//if ((m_HighestPos - GetPos()).Size() > GameEngineWindow::GetScreenSize().hy())
		//{
		//
		//}
		ChangeState(PlayerState::IDLE);
	}
}
void CPlayer::DownEnd() 
{
}

void CPlayer::CollideStart() {}
void CPlayer::CollideUpdate(float _Time) {}
void CPlayer::CollideEnd() {}