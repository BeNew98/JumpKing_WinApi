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

	if (true == GameEngineInput::IsPress("LeftMove")&&true == m_bGround)
	{
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}

	else if (true == GameEngineInput::IsPress("RightMove") && true == m_bGround)
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}

	DirCheck("Move");

}

void CPlayer::MoveEnd() 
{

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

	if (m_fJumpPressTime >= 1.0f)
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
	m_MoveDir += float4::Up * m_fJumpSpeed * m_fJumpPressTime;
}

void  CPlayer::JumpUpdate(float _Time)
{
	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}
}

void  CPlayer::JumpEnd()
{
}

void CPlayer::DownStart()
{
	DirCheck("Down");
}
void CPlayer::DownUpdate(float _Time)
{
	if (m_bGround)
	{
		ChangeState(PlayerState::IDLE);
	}
}
void CPlayer::DownEnd() {}

void CPlayer::CollideStart() {}
void CPlayer::CollideUpdate(float _Time) {}
void CPlayer::CollideEnd() {}