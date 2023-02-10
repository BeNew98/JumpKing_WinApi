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
	case PlayerState::FALL:
		FallStart();
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::JUMP:
		JumpEnd();
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
	case PlayerState::FALL:
		FallUpdate(_Time);
		break;
	}
}

void CPlayer::IdleStart()
{
	DirCheck("Idle");

}

void CPlayer::IdleUpdate(float _Time)
{
	// 바닥에 박힌거 올리기
	while (ColCur())
	{
		SetPos(GetPos() + float4::Up);
		pPos += float4::Up;
	}


	//방향키 누르면 move로 전환
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; 
	}

	// 스페이스 누르면 jump ready로 전환
	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP_READY);
		return;
	}

	// 방향키 누르지 않았을때 x값 0으로 변경해서 바로 멈추기
	if (false == GameEngineInput::IsPress("LeftMove") || false == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir.x = 0;
		return;
	}

	//// idle 상태에서 떨어지게 되었을때 down으로 전환
	//if (false == ColCur())
	//{
	//	ChangeState(PlayerState::DOWN);
	//	return;
	//}
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
	// move에서 방향키가 눌리지 않게 되었다면 idle로 전환
	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 움직이다 점프키가 눌렸다면 jump ready로 전환
	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP_READY);
		return;
	}

	//왼쪽 방향키를 누르면 왼쪽으로
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}
	//오른쪽 방향키를 누르면 오른쪽으로
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}

	//왼쪽 방향키를 눌렀으면서 왼쪽 벽 체크해서 true시 x값 0으로 못가게하기
	if ((true == GameEngineInput::IsPress("LeftMove") && ColLeftAll() && m_MoveDir.x < 0))
	{
		m_MoveDir.x = 0.f;
	}
	//오른쪽 방향키를 눌렀으면서 오른쪽 벽 체크해서 true시 x값 0으로 못가게하기
	if ((true == GameEngineInput::IsPress("RightMove") && ColRightAll() && m_MoveDir.x > 0))
	{
		m_MoveDir.x = 0.f;
	}

	// 좌우 이동 최대 속도 제한
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

	// move 상태에서 떨어지게 되었을때 down으로 전환
	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}

	DirCheck("Move");
}

void CPlayer::MoveEnd() 
{
}


void CPlayer::JumpReadyStart()
{
	//jump가 준비중일때 x는 항상 0으로 전환
	m_MoveDir.x = 0.0f;

	DirCheck("JumpReady");
	m_fJumpPressTime = 0.0f;
}

void CPlayer::JumpReadyUpdate(float _Time)
{	
	//점프키를 누르고있을때 점프키 누른시간 체크
	if (true == GameEngineInput::IsPress("Jump"))
	{
		m_fJumpPressTime = GameEngineInput::GetPressTime("Jump");
	}

	//키를 떼면 jump로 전환
	if (true == GameEngineInput::IsUp("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	//키를 누른시간이 0.6초이상이 될 시 강제로 jump로 전환
	if (m_fJumpPressTime >= 0.6f)
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
}
void CPlayer::JumpReadyEnd() 
{
}


void  CPlayer::JumpStart()
{
	DirCheck("Jump");

	// 점프키 클릭 시간을 6단계로 나누어서 점프력 보정
	if (m_fJumpPressTime <= 0.1f)
	{
		m_fJumpPressTime = 0.1f;
	}
	else if (m_fJumpPressTime <= 0.2f)
	{
		m_fJumpPressTime = 0.2f;
	}
	else if (m_fJumpPressTime <= 0.3f)
	{
		m_fJumpPressTime = 0.3f;
	}
	else if (m_fJumpPressTime <= 0.4f)
	{
		m_fJumpPressTime = 0.4f;
	}
	else if (m_fJumpPressTime <= 0.5f)
	{
		m_fJumpPressTime = 0.5f;
	}
	else if (m_fJumpPressTime <= 0.6f)
	{
		m_fJumpPressTime = 0.6f;
	}
	else
	{
		m_fJumpPressTime = 0.6f;
	}

	// 점프키를 누른 시간만큼에 비례하여 점프 스피드 결정. 0.6초가 최대고 나누어서 최대가 1.0으로 만듦	 
	m_MoveDir += float4::Up * m_fJumpSpeed * (m_fJumpPressTime / 0.6f);


	// jump로 전환되었을때 왼쪽 방향키를 누르고 있었다면 왼쪽으로 힘 더해주기.
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}
	// jump로 전환되었을때 오른쪽 방향키를 누르고 있었다면 오른쪽으로 힘 더해주기.
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}


	//점프시 좌우 이동 최대속도 제한
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
	//오른쪽으로 점프중 오른쪽이 충돌했을 시 x값 반전해서 튕겨나가기
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -0.475f;
		m_iCollide = true;
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
	}
	//왼쪽으로 점프중 왼쪽이 충돌했을 시 x값 반전해서 튕겨나가기
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -0.475f;
		m_iCollide = true;
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
	}

	//위쪽이 충돌했을 시 y값 0으로 만들어서 바로 떨어뜨리기
	if (ColUpAll())
	{
		m_MoveDir.y = 0.f;
	}
	
	//점프중에 아래로 떨어지기 시작할시 down으로 전환
	if (m_MoveDir.y >= 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}

}

void  CPlayer::JumpEnd()
{
	//가장 높았던 위치 기록
	m_HighestPos = GetPos();
}


void CPlayer::DownStart()
{
	//이전에 충돌한적 없으면 Down으로 이미지 전환
	if (m_iCollide)
	{
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
	}
	else
	{
		m_pAnimationRender->ChangeAnimation(m_DirString + "Down");
	}

}

void CPlayer::DownUpdate(float _Time)
{
	//오른쪽으로 하강중 오른쪽이 충돌했을 시 x값 반전해서 튕겨나가기
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -0.475f;
		m_iCollide = true;
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
	}
	//왼쪽으로 하강중 왼쪽이 충돌했을 시 x값 반전해서 튕겨나가기
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -0.475f;
		m_iCollide = true;
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
	}	

	//바닥에 안착시
	if (ColDownAll())
	{
		// (점프시 최대 높이 - 내 현재 높이)가 화면 사이즈 절반보다 크다면 Fall로 전환
		if (fabsf(m_HighestPos.y - GetPos().y) > GameEngineWindow::GetScreenSize().hy())
		{
			m_iCollide = false;
			ChangeState(PlayerState::FALL);
			return;
		}

		// 아닐시 idle로 전환
		else
		{
		m_iCollide = false;
		ChangeState(PlayerState::IDLE);
		return;
		}
	}
}
void CPlayer::DownEnd() 
{
}



void CPlayer::FallStart()
{
	m_MoveDir.x = 0.f;
	//DirCheck("Fall");
	m_pAnimationRender->ChangeAnimation(m_DirString + "Fall");
}

void CPlayer::FallUpdate(float _Time)
{
	// 바닥에 박힌거 올리기
	while (ColCur())
	{
		SetPos(GetPos() + float4::Up);
		pPos += float4::Up;
	}

	//방향키 누르면 move로 전환
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}

	// 스페이스 누르면 jump ready로 전환
	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP_READY);
		return;
	}
}

void CPlayer::FallEnd()
{
}

