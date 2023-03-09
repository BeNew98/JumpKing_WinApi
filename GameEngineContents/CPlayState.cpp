#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "CJump.h"
#include "EnumHeader.h"

void CPlayer::ChangeState(PlayerState _State)
{

	if (m_Ending&& static_cast<int>(_State) < 6)
	{
		_State = static_cast<PlayerState>(static_cast<int>(_State) + 6);
	}
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

	case PlayerState::END_IDLE:
		EndIdleStart();
		break;
	case PlayerState::END_MOVE:
		EndMoveStart();
		break;
	case PlayerState::END_JUMP_READY:
		EndJumpReadyStart();
		break;
	case PlayerState::END_JUMP:
		EndJumpStart();
		break;
	case PlayerState::END_DOWN:
		EndDownStart();
		break;
	case PlayerState::END_FLY:
		EndFlyStart();
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
	case PlayerState::JUMP_READY:
		JumpReadyEnd();
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

	case PlayerState::END_IDLE:
		EndIdleUpdate(_Time);
		break;
	case PlayerState::END_MOVE:
		EndMoveUpdate(_Time);
		break;
	case PlayerState::END_JUMP_READY:
		EndJumpReadyUpdate(_Time);
		break;
	case PlayerState::END_JUMP:
		EndJumpUpdate(_Time);
		break;
	case PlayerState::END_DOWN:
		EndDownUpdate(_Time);
		break;
	case PlayerState::END_FLY:
		EndFlyUpdate(_Time);
		break;
	}
}

void CPlayer::IdleStart()
{
	AnimChange("Idle");
}

void CPlayer::IdleUpdate(float _Time)
{
	FloorCalibration();

	// idle 상태에서 떨어지게 되었을때 down으로 전환
	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
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

	//왼쪽이 벽
	if (ColLeftAll() && m_MoveDir.x < 0)
	{
		m_MoveDir.x = 0.f;
	}

	//오른쪽이 벽
	if (ColRightAll() && m_MoveDir.x > 0)
	{
		m_MoveDir.x = 0.f;
	}

	// 방향키 누르지 않았을때 x값 0으로 변경해서 바로 멈추기
	if ((false == GameEngineInput::IsPress("LeftMove") || false == GameEngineInput::IsPress("RightMove")) && false == ColDownAll(m_Sky))
	{
		m_MoveDir.x = 0;
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
	if (true == GameEngineInput::IsPress("LeftMove") && true == ColDownAll(m_Sky))
	{
		m_MoveDir += float4::Left * 10.f;
	}
	//오른쪽 방향키를 누르면 오른쪽으로
	else if (true == GameEngineInput::IsPress("RightMove")&&true == ColDownAll(m_Sky))
	{
		m_MoveDir += float4::Right * 10.f;
	}


	//왼쪽 방향키를 누르면 왼쪽으로
	if (true == GameEngineInput::IsPress("LeftMove") && false == ColDownAll(m_Sky))
	{
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}
	//오른쪽 방향키를 누르면 오른쪽으로
	else if (true == GameEngineInput::IsPress("RightMove") && false == ColDownAll(m_Sky))
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}

	//왼쪽 방향키를 눌렀으면서 왼쪽 벽 체크해서 true시 x값 0으로 못가게하기
	if ((true == GameEngineInput::IsPress("LeftMove") && (ColLeftAll() || ColLeftAll(m_Red) || ColLeftAll(m_Blue)) && m_MoveDir.x < 0))
	{
		m_MoveDir.x = 0.f;
	}
	//오른쪽 방향키를 눌렀으면서 오른쪽 벽 체크해서 true시 x값 0으로 못가게하기
	if ((true == GameEngineInput::IsPress("RightMove") && (ColRightAll() || ColRightAll(m_Red) || ColRightAll(m_Blue)) && m_MoveDir.x > 0))
	{
		m_MoveDir.x = 0.f;
	}

	// 좌우 이동 최대 속도 제한
	if (m_fMoveLimit <= abs(m_MoveDir.x))
	{
		if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -m_fMoveLimit;
		}
		else {
			m_MoveDir.x = m_fMoveLimit;
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
	//jump가 준비중일때 x는 얼음 맵이 아니면 항상 0으로 전환
	if (false == ColDownAll(m_Sky))
	{
		m_MoveDir.x = 0.0f;
	}

	DirCheck("JumpReady");
	m_fJumpPressTime = 0.0f;
}

void CPlayer::JumpReadyUpdate(float _Time)
{
	if (false == ColDownAll(m_Sky))
	{
		m_MoveDir.x = 0.0f;
	}

	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}

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
	float4 PlayerPos = GetPos();
	CJump::JumpParticle->AnimChange("JumpParticle", PlayerPos);
}


void  CPlayer::JumpStart()
{
	++JumpCount;
	DirCheck("Jump");
	CJump::JumpParticle->AnimChange("IdleParticle", float4::Zero);

	GameEngineResources::GetInst().SoundPlay("king_Jump.wav");

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
		m_MoveDir += float4::Left * m_fJumpMoveSpeed;
	}
	// jump로 전환되었을때 오른쪽 방향키를 누르고 있었다면 오른쪽으로 힘 더해주기.
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir += float4::Right * m_fJumpMoveSpeed;
	}


	//점프시 좌우 이동 최대속도 제한
	if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
	{
		if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -m_fJumpMoveLimit;
		}
		else
		{
			m_MoveDir.x = m_fJumpMoveLimit;
		}
	}
}

void  CPlayer::JumpUpdate(float _Time)
{
	while (ColCurUpAll() && false == ColCurDownAll())
	{
		SetPos(GetPos() + float4::Down);
		pPosUpdate();
	}

	WallCalibration();	


	//오른쪽으로 점프중 오른쪽이 충돌했을 시 x값 반전해서 튕겨나가기
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_bCollide = true;
		AnimChange("Collide");
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
		return;
	}
	//왼쪽으로 점프중 왼쪽이 충돌했을 시 x값 반전해서 튕겨나가기
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_bCollide = true;
		AnimChange("Collide");
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
		return;
	}


	//바닥이 사선일시 x값 0으로 해서 멈추게하기
	if (ColCurDownAll(m_Red) || ColCurDownAll(m_Blue))
	{
		m_MoveDir.x *= 0.f;
		m_bCollide = true;
		AnimChange("Collide");
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
	}

	// 위가 사선일때

	//빨간 픽셀이면 오른쪽으로 
	if (ColCurUpAll(m_Red)&& m_MoveDir.y<0)
	{
		m_bCollide = true;
		AnimChange("Collide");
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
		m_MoveDir.x += -m_MoveDir.y;
		m_MoveDir.y = 0.f;
		++m_iCollide;
		if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
		{
			m_MoveDir.x = m_fJumpMoveLimit;
		}

		return;
	}
	//파란 픽셀이면 오른쪽으로
	else if (ColCurUpAll(m_Blue) && m_MoveDir.y < 0)
	{
		m_bCollide = true;
		AnimChange("Collide");
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
		m_MoveDir.x += m_MoveDir.y;
		m_MoveDir.y = 0.f;
		++m_iCollide;
		if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
		{
			m_MoveDir.x = -m_fJumpMoveLimit;
		}

		return;
	}

	//점프시 천장 막힘
	if (ColUpAll() && false == ColCurDownAll())
	{
		if (m_MoveDir.y < 0)
		{
			m_MoveDir.y += -m_MoveDir.y;
		}
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
	}

	if (1 == m_iCollide)
	{
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
	}

	//점프중에 아래로 떨어지기 시작할시 down으로 전환
	if (m_MoveDir.y >= 0)
	{
		m_iCollide = 0;
		ChangeState(PlayerState::DOWN);
		return;
	}

}

void  CPlayer::JumpEnd()
{
}


void CPlayer::DownStart()
{
	//가장 높았던 위치 기록
	m_HighestPos = GetPos();

	//이전에 충돌한적 없으면 Down으로 이미지 전환
	if (m_bCollide)
	{
		AnimChange("Collide");
	}
	else
	{
		AnimChange("Down");
	}
}

void CPlayer::DownUpdate(float _Time)
{
	FloorCalibration();

	WallCalibration();

	//오른쪽으로 하강중 오른쪽이 충돌했을 시 x값 반전해서 튕겨나가기
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_bCollide = true;
		AnimChange("Collide");
		++m_iCollide;

		GameEngineResources::GetInst().SoundPlay("king_bump.wav");		
	}

	//왼쪽으로 하강중 왼쪽이 충돌했을 시 x값 반전해서 튕겨나가기
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_bCollide = true;
		AnimChange("Collide");
		++m_iCollide;

		GameEngineResources::GetInst().SoundPlay("king_bump.wav");		
	}

	//빨간 픽셀이면 왼쪽으로
	if (ColCurDownAll(m_Red))
	{
		m_MoveDir.x *= 0.f;
		m_bCollide = true;
		AnimChange("Collide");
		++m_iCollide;

		m_MoveDir.x += float4::Left.x * m_fJumpMoveLimit;

		if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
		{
			m_MoveDir.x = -m_fJumpMoveLimit;
		}
		m_MoveDir.y = -m_MoveDir.x;

		if (1 == m_iCollide)
		{
			GameEngineResources::GetInst().SoundPlay("king_bump.wav");
		}

		return;
	}
	//파란 픽셀이면 오른쪽으로
	else if (ColCurDownAll(m_Blue))
	{
		m_MoveDir.x *= 0.f;
		m_bCollide = true;
		AnimChange("Collide");

		m_MoveDir.x += float4::Right.x * m_fJumpMoveLimit;

		if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
		{
			m_MoveDir.x = m_fJumpMoveLimit;
		}
		m_MoveDir.y = m_MoveDir.x;
		++m_iCollide;

		if (1 == m_iCollide)
		{
			GameEngineResources::GetInst().SoundPlay("king_bump.wav");
		}

		return;
	}


	//바닥에 안착시
	if ((ColDownAll() || ColDownAll(m_Sky) || ColDownAll(m_Green)) && false == ColUpAll())
	{
		// (점프시 최대 높이 - 내 현재 높이)가 화면 사이즈 절반보다 크다면 Fall로 전환
		if (m_HighestPos.y - GetPos().y < -GameEngineWindow::GetScreenSize().hy())
		{
			m_bCollide = false;
			m_iCollide =0;
			GameEngineResources::GetInst().SoundPlay("king_splat.wav");
			ChangeState(PlayerState::FALL);
			return;
		}

		// 아닐시 idle로 전환
		else
		{
			m_bCollide = false;
			m_iCollide = 0;
			GameEngineResources::GetInst().SoundPlay("king_land.wav");
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
	++FallCount;
	m_fKnockTime = 0;
	m_MoveDir.x = 0.f;
	AnimChange("Fall");
}

void CPlayer::FallUpdate(float _Time)
{
	FloorCalibration();

	m_MoveDir.x = 0;


	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}

	//녹다운시 1초뒤에 움직이는것이 가능
	m_fKnockTime += _Time;
	if (m_fKnockTime < 1.f)
	{
		return;
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















void CPlayer::EndIdleStart() 
{
}
void CPlayer::EndIdleUpdate(float _Time) 
{
	m_MoveDir = float4::Zero;
}
void CPlayer::EndIdleEnd() {}

void CPlayer::EndMoveStart() 
{
	DirCheck("KBM");
}
void CPlayer::EndMoveUpdate(float _Time) 
{
	// 좌우 이동 최대 속도 제한
	if (m_fMoveLimit <= abs(m_MoveDir.x))
	{
		if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -m_fMoveLimit;
		}
		else {
			m_MoveDir.x = m_fMoveLimit;
		}
	}

	if (m_MoveDir.x == 0.f)
	{
		return;
	}

	DirCheck("KBM");
}
void CPlayer::EndMoveEnd() {}
void CPlayer::EndJumpReadyStart() 
{
	m_MoveDir = float4::Zero;
}
void CPlayer::EndJumpReadyUpdate(float _Time) {}
void CPlayer::EndJumpReadyEnd() {}
void CPlayer::EndJumpStart() 
{
	GameEngineResources::GetInst().SoundPlay("king_Jump.wav");

	// 점프키 클릭 시간을 6단계로 나누어서 점프력 보정
	m_fJumpPressTime = 0.6f;


	// 점프키를 누른 시간만큼에 비례하여 점프 스피드 결정. 0.6초가 최대고 나누어서 최대가 1.0으로 만듦	 
	m_MoveDir += float4::Up * m_fJumpSpeed * (m_fJumpPressTime / 0.6f);
}
void CPlayer::EndJumpUpdate(float _Time) 
{
	if (m_MoveDir.y >= 0)
	{
		ChangeState(PlayerState::END_DOWN);
		return;
	}
}
void CPlayer::EndJumpEnd() {}
void CPlayer::EndDownStart() {}
void CPlayer::EndDownUpdate(float _Time) 
{
	//바닥에 안착시
	if (ColDownAll())
	{
		GameEngineResources::GetInst().SoundPlay("king_land.wav");
		ChangeState(PlayerState::END_IDLE);
		return;
	}
}
void CPlayer::EndDownEnd() {}
void CPlayer::EndFlyStart()
{
	EndAnimChange("FlyIdle");
}
void CPlayer::EndFlyUpdate(float _Time) 
{
	
}
void CPlayer::EndFlyEnd() {}