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

	// idle ���¿��� �������� �Ǿ����� down���� ��ȯ
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
	if ((true == GameEngineInput::IsPress("LeftMove") && ColLeft() && m_MoveDir.x < 0))
	{
		m_MoveDir.x = 0.f;
	}
	//������ ����Ű�� �������鼭 ������ �� üũ�ؼ� true�� x�� 0���� �������ϱ�
	if ((true == GameEngineInput::IsPress("RightMove") && ColRight() && m_MoveDir.x > 0))
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
	}

	//Ű�� �����ð��� 0.6���̻��� �� �� ������ jump�� ��ȯ
	if (m_fJumpPressTime >= 0.6f)
	{
		ChangeState(PlayerState::JUMP);
	}
}
void CPlayer::JumpReadyEnd() {}


void  CPlayer::JumpStart()
{
	DirCheck("Jump");

	// ����Ű Ŭ�� �ð��� 0.1�� �����ϰ�� 0.1�ʵ��� ���������� ����
	if (m_fJumpPressTime < 0.1f)
	{
		m_fJumpPressTime = 0.1f;
	}

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

	// ����Ű�� ���� �ð���ŭ�� ����Ͽ� ���� ���ǵ� ����. 0.6�ʰ� �ִ�� ����� �ִ밡 1.0���� ����
	 
	//////////////////////////////////////////////////////////////////////////////////////////////
	//����ŷ ���� �ܰ�� 6�ܰ�� �������� �ִٰ� �� 0.1�ʸ��� ���� �ٸ��� �������� Ȯ���� �ؾ��� �ʿ� ����//
	//////////////////////////////////////////////////////////////////////////////////////////////
	m_MoveDir += float4::Up * m_fJumpSpeed * (m_fJumpPressTime/0.6f);

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
	if (m_MoveDir.x > 0 && ColRight())
	{
		m_MoveDir.x *= -1;

		DirCheck("Collide");
	}
	//�������� ������ ������ �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x < 0 && ColLeft())
	{
		m_MoveDir.x *= -1;

		DirCheck("Collide");
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
	DirCheck("Down");
}

void CPlayer::DownUpdate(float _Time)
{
	//���������� �ϰ��� �������� �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x > 0 && ColRight())
	{
		m_MoveDir.x *= -1;

		DirCheck("Collide");
	}
	//�������� �ϰ��� ������ �浹���� �� x�� �����ؼ� ƨ�ܳ�����
	if (m_MoveDir.x < 0 && ColLeft())
	{
		m_MoveDir.x *= -1;

		DirCheck("Collide");
	}

		//�ٴڿ� ������ idle�� ��ȯ
	if (ColDown())
	{	
		ChangeState(PlayerState::IDLE);
	}
}
void CPlayer::DownEnd() 
{
}

void CPlayer::CollideStart() {}
void CPlayer::CollideUpdate(float _Time) {}
void CPlayer::CollideEnd() {}