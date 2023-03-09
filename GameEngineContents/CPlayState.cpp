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

	// idle ���¿��� �������� �Ǿ����� down���� ��ȯ
	if (m_MoveDir.y > 0)
	{
		ChangeState(PlayerState::DOWN);
		return;
	}

	//����Ű ������ move�� ��ȯ
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}

	// �����̽� ������ jump ready�� ��ȯ
	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP_READY);
		return;
	}

	//������ ��
	if (ColLeftAll() && m_MoveDir.x < 0)
	{
		m_MoveDir.x = 0.f;
	}

	//�������� ��
	if (ColRightAll() && m_MoveDir.x > 0)
	{
		m_MoveDir.x = 0.f;
	}

	// ����Ű ������ �ʾ����� x�� 0���� �����ؼ� �ٷ� ���߱�
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
	// move���� ����Ű�� ������ �ʰ� �Ǿ��ٸ� idle�� ��ȯ
	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// �����̴� ����Ű�� ���ȴٸ� jump ready�� ��ȯ
	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP_READY);
		return;
	}

	//���� ����Ű�� ������ ��������
	if (true == GameEngineInput::IsPress("LeftMove") && true == ColDownAll(m_Sky))
	{
		m_MoveDir += float4::Left * 10.f;
	}
	//������ ����Ű�� ������ ����������
	else if (true == GameEngineInput::IsPress("RightMove")&&true == ColDownAll(m_Sky))
	{
		m_MoveDir += float4::Right * 10.f;
	}


	//���� ����Ű�� ������ ��������
	if (true == GameEngineInput::IsPress("LeftMove") && false == ColDownAll(m_Sky))
	{
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}
	//������ ����Ű�� ������ ����������
	else if (true == GameEngineInput::IsPress("RightMove") && false == ColDownAll(m_Sky))
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}

	//���� ����Ű�� �������鼭 ���� �� üũ�ؼ� true�� x�� 0���� �������ϱ�
	if ((true == GameEngineInput::IsPress("LeftMove") && (ColLeftAll() || ColLeftAll(m_Red) || ColLeftAll(m_Blue)) && m_MoveDir.x < 0))
	{
		m_MoveDir.x = 0.f;
	}
	//������ ����Ű�� �������鼭 ������ �� üũ�ؼ� true�� x�� 0���� �������ϱ�
	if ((true == GameEngineInput::IsPress("RightMove") && (ColRightAll() || ColRightAll(m_Red) || ColRightAll(m_Blue)) && m_MoveDir.x > 0))
	{
		m_MoveDir.x = 0.f;
	}

	// �¿� �̵� �ִ� �ӵ� ����
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

	// move ���¿��� �������� �Ǿ����� down���� ��ȯ
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
	//jump�� �غ����϶� x�� ���� ���� �ƴϸ� �׻� 0���� ��ȯ
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

	//����Ű�� ������������ ����Ű �����ð� üũ
	if (true == GameEngineInput::IsPress("Jump"))
	{
		m_fJumpPressTime = GameEngineInput::GetPressTime("Jump");
	}

	//Ű�� ���� jump�� ��ȯ
	if (true == GameEngineInput::IsUp("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	//Ű�� �����ð��� 0.6���̻��� �� �� ������ jump�� ��ȯ
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

	// ����Ű Ŭ�� �ð��� 6�ܰ�� ����� ������ ����
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

	// ����Ű�� ���� �ð���ŭ�� ����Ͽ� ���� ���ǵ� ����. 0.6�ʰ� �ִ�� ����� �ִ밡 1.0���� ����	 
	m_MoveDir += float4::Up * m_fJumpSpeed * (m_fJumpPressTime / 0.6f);


	// jump�� ��ȯ�Ǿ����� ���� ����Ű�� ������ �־��ٸ� �������� �� �����ֱ�.
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		m_MoveDir += float4::Left * m_fJumpMoveSpeed;
	}
	// jump�� ��ȯ�Ǿ����� ������ ����Ű�� ������ �־��ٸ� ���������� �� �����ֱ�.
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir += float4::Right * m_fJumpMoveSpeed;
	}


	//������ �¿� �̵� �ִ�ӵ� ����
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


	//���������� ������ �������� �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_bCollide = true;
		AnimChange("Collide");
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
		return;
	}
	//�������� ������ ������ �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_bCollide = true;
		AnimChange("Collide");
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
		return;
	}


	//�ٴ��� �缱�Ͻ� x�� 0���� �ؼ� ���߰��ϱ�
	if (ColCurDownAll(m_Red) || ColCurDownAll(m_Blue))
	{
		m_MoveDir.x *= 0.f;
		m_bCollide = true;
		AnimChange("Collide");
		GameEngineResources::GetInst().SoundPlay("king_bump.wav");
	}

	// ���� �缱�϶�

	//���� �ȼ��̸� ���������� 
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
	//�Ķ� �ȼ��̸� ����������
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

	//������ õ�� ����
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

	//�����߿� �Ʒ��� �������� �����ҽ� down���� ��ȯ
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
	//���� ���Ҵ� ��ġ ���
	m_HighestPos = GetPos();

	//������ �浹���� ������ Down���� �̹��� ��ȯ
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

	//���������� �ϰ��� �������� �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_bCollide = true;
		AnimChange("Collide");
		++m_iCollide;

		GameEngineResources::GetInst().SoundPlay("king_bump.wav");		
	}

	//�������� �ϰ��� ������ �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_bCollide = true;
		AnimChange("Collide");
		++m_iCollide;

		GameEngineResources::GetInst().SoundPlay("king_bump.wav");		
	}

	//���� �ȼ��̸� ��������
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
	//�Ķ� �ȼ��̸� ����������
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


	//�ٴڿ� ������
	if ((ColDownAll() || ColDownAll(m_Sky) || ColDownAll(m_Green)) && false == ColUpAll())
	{
		// (������ �ִ� ���� - �� ���� ����)�� ȭ�� ������ ���ݺ��� ũ�ٸ� Fall�� ��ȯ
		if (m_HighestPos.y - GetPos().y < -GameEngineWindow::GetScreenSize().hy())
		{
			m_bCollide = false;
			m_iCollide =0;
			GameEngineResources::GetInst().SoundPlay("king_splat.wav");
			ChangeState(PlayerState::FALL);
			return;
		}

		// �ƴҽ� idle�� ��ȯ
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

	//��ٿ�� 1�ʵڿ� �����̴°��� ����
	m_fKnockTime += _Time;
	if (m_fKnockTime < 1.f)
	{
		return;
	}



	//����Ű ������ move�� ��ȯ
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}

	// �����̽� ������ jump ready�� ��ȯ
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
	// �¿� �̵� �ִ� �ӵ� ����
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

	// ����Ű Ŭ�� �ð��� 6�ܰ�� ����� ������ ����
	m_fJumpPressTime = 0.6f;


	// ����Ű�� ���� �ð���ŭ�� ����Ͽ� ���� ���ǵ� ����. 0.6�ʰ� �ִ�� ����� �ִ밡 1.0���� ����	 
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
	//�ٴڿ� ������
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