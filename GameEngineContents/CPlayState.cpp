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
	AnimChange("Idle");
}

void CPlayer::IdleUpdate(float _Time)
{
	FloorCalibration();

	// move ���¿��� �������� �Ǿ����� down���� ��ȯ
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
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}
	//������ ����Ű�� ������ ����������
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}

	//���� ����Ű�� �������鼭 ���� �� üũ�ؼ� true�� x�� 0���� �������ϱ�
	if ((true == GameEngineInput::IsPress("LeftMove") && ColLeftAll() && m_MoveDir.x < 0))
	{
		m_MoveDir.x = 0.f;
	}
	//������ ����Ű�� �������鼭 ������ �� üũ�ؼ� true�� x�� 0���� �������ϱ�
	if ((true == GameEngineInput::IsPress("RightMove") && ColRightAll() && m_MoveDir.x > 0))
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
}


void  CPlayer::JumpStart()
{
	DirCheck("Jump");

	//Jump.PauseOff();

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
	//���������� ������ �������� �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_iCollide = true;
		AnimChange("Collide");
		return;
	}
	//�������� ������ ������ �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_iCollide = true;
		AnimChange("Collide");
		return;
	}

	//�ٴ��� �缱�Ͻ� x�� 0���� �ؼ� ���߰��ϱ�
	if (ColCurDownAll(m_Red) || ColCurDownAll(m_Blue))
	{
		m_MoveDir.x *= 0.f;
		m_iCollide = true;
		AnimChange("Collide");
	}

	// ���� �缱�϶�

	//���� �ȼ��̸� ���������� 
	if (ColCurUpAll(m_Red))
	{
		m_iCollide = true;
		AnimChange("Collide");
		m_MoveDir.x += -m_MoveDir.y;

		if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
		{
			m_MoveDir.x = m_fJumpMoveLimit;
		}

		return;
	}
	//�Ķ� �ȼ��̸� ����������
	else if (ColCurUpAll(m_Blue))
	{
		m_iCollide = true;
		AnimChange("Collide");
		m_MoveDir.x += m_MoveDir.y;

		if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
		{
			m_MoveDir.x = -m_fJumpMoveLimit;
		}

		return;
	}


	//������ �浹���� �� y�� 0���� ���� �ٷ� ����߸���
	if (ColUpAll())
	{
		m_MoveDir.y = 0.f;
	}

	//�����߿� �Ʒ��� �������� �����ҽ� down���� ��ȯ
	if (m_MoveDir.y >= 0)
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
	//���� ���Ҵ� ��ġ ���
	m_HighestPos = GetPos();

	//������ �浹���� ������ Down���� �̹��� ��ȯ
	if (m_iCollide)
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

	//���� �ȼ��̸� ��������
	if (ColCurDownAll(m_Red))
	{
		m_MoveDir.x *= 0.f;
		m_iCollide = true;
		AnimChange("Collide");

		m_MoveDir.x += float4::Left.x * m_fJumpMoveLimit;

		if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
		{
			m_MoveDir.x = -m_fJumpMoveLimit;
		}
		m_MoveDir.y = -m_MoveDir.x;

		return;
	}
	//�Ķ� �ȼ��̸� ����������
	else if (ColCurDownAll(m_Blue))
	{
		m_MoveDir.x *= 0.f;
		m_iCollide = true;
		AnimChange("Collide");

		m_MoveDir.x += float4::Right.x * m_fJumpMoveLimit;

		if (m_fJumpMoveLimit <= abs(m_MoveDir.x))
		{
			m_MoveDir.x = m_fJumpMoveLimit;
		}
		m_MoveDir.y = m_MoveDir.x;

		return;
	}


	FloorCalibration();

	// ���� ������ ����
	while (ColCurDL() && false == ColCurDR())
	{
		SetPos(GetPos() + float4::Right);
		pPosUpdate();
	}

	// ���� ������ ����
	while (ColCurDR() && false == ColCurDL())
	{
		SetPos(GetPos() + float4::Left);
		pPosUpdate();
	}

	//���������� �ϰ��� �������� �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_iCollide = true;
		AnimChange("Collide");
	}

	//�������� �ϰ��� ������ �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -m_fRecoilCoeff;
		m_iCollide = true;
		AnimChange("Collide");
	}



	//�ٴڿ� ������
	if (ColDownAll() || ColDownAll(m_Sky) || ColDownAll(m_Green))
	{
		// (������ �ִ� ���� - �� ���� ����)�� ȭ�� ������ ���ݺ��� ũ�ٸ� Fall�� ��ȯ
		if (m_HighestPos.y - GetPos().y < -GameEngineWindow::GetScreenSize().hy())
		{
			m_iCollide = false;
			ChangeState(PlayerState::FALL);
			return;
		}

		// �ƴҽ� idle�� ��ȯ
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
	m_fKnockTime = 0;
	m_MoveDir.x = 0.f;
	AnimChange("Fall");
}

void CPlayer::FallUpdate(float _Time)
{
	FloorCalibration();

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

