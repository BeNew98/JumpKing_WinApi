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
	// �ٴڿ� ������ �ø���
	while (ColCur())
	{
		SetPos(GetPos() + float4::Up);
		pPos += float4::Up;
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

	// ����Ű ������ �ʾ����� x�� 0���� �����ؼ� �ٷ� ���߱�
	if (false == GameEngineInput::IsPress("LeftMove") || false == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir.x = 0;
		return;
	}

	//// idle ���¿��� �������� �Ǿ����� down���� ��ȯ
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
	//jump�� �غ����϶� x�� �׻� 0���� ��ȯ
	m_MoveDir.x = 0.0f;

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
		m_MoveDir += float4::Left * m_fMoveSpeed;
	}
	// jump�� ��ȯ�Ǿ����� ������ ����Ű�� ������ �־��ٸ� ���������� �� �����ֱ�.
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir += float4::Right * m_fMoveSpeed;
	}


	//������ �¿� �̵� �ִ�ӵ� ����
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
	//���������� ������ �������� �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -0.475f;
		m_iCollide = true;
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
	}
	//�������� ������ ������ �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -0.475f;
		m_iCollide = true;
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
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
	//���� ���Ҵ� ��ġ ���
	m_HighestPos = GetPos();
}


void CPlayer::DownStart()
{
	//������ �浹���� ������ Down���� �̹��� ��ȯ
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
	//���������� �ϰ��� �������� �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x > 0 && ColRightAll())
	{
		m_MoveDir.x *= -0.475f;
		m_iCollide = true;
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
	}
	//�������� �ϰ��� ������ �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x < 0 && ColLeftAll())
	{
		m_MoveDir.x *= -0.475f;
		m_iCollide = true;
		m_pAnimationRender->ChangeAnimation(m_DirString + "Collide");
	}	

	//�ٴڿ� ������
	if (ColDownAll())
	{
		// (������ �ִ� ���� - �� ���� ����)�� ȭ�� ������ ���ݺ��� ũ�ٸ� Fall�� ��ȯ
		if (fabsf(m_HighestPos.y - GetPos().y) > GameEngineWindow::GetScreenSize().hy())
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
	m_MoveDir.x = 0.f;
	//DirCheck("Fall");
	m_pAnimationRender->ChangeAnimation(m_DirString + "Fall");
}

void CPlayer::FallUpdate(float _Time)
{
	// �ٴڿ� ������ �ø���
	while (ColCur())
	{
		SetPos(GetPos() + float4::Up);
		pPos += float4::Up;
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

