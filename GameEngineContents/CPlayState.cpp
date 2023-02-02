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
	case PlayerState::LOOKUP:
		break;
	case PlayerState::JUMP_READY:
		break;
	case PlayerState::JUMP:
		JumpStart();
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
	case PlayerState::LOOKUP:
		break;
	case PlayerState::JUMP_READY:
		break;
	case PlayerState::JUMP:
		JumpUpdate(_Time);
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

	if (GameEngineInput::IsPress("Jump"))
	{
		ChangeState(PlayerState::JUMP);
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

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		SetMove(float4::Left * m_fMoveSpeed * _Time);
	}

	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		SetMove(float4::Right * m_fMoveSpeed * _Time);
	}

	DirCheck("Move");

}

void CPlayer::MoveEnd() 
{

}


void  CPlayer::JumpStart()
{
}

void  CPlayer::JumpUpdate(float _Time)
{
	if (true==GameEngineInput::IsUp("Jump"))
	{
		SetMove(float4::Up * m_fJumpSpeed);
	}
}

void  CPlayer::JumpEnd()
{

}