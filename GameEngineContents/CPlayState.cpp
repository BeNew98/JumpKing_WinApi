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
	PlayerState PrevState = StateValue;

	StateValue = NextState;

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
	switch (StateValue)
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
		SetMove(float4::Left * MoveSpeed * _Time);
	}

	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		SetMove(float4::Right * MoveSpeed * _Time);
	}

	DirCheck("Move");

}

void CPlayer::MoveEnd() 
{

}