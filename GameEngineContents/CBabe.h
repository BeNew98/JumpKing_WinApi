#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "EnumHeader.h"

enum class BabeState
{
	IDLE,
	MOVE,
	JUMP_READY,
	JUMP,
	KISS,
};

// Ό³Έν :
class GameEngineRender;
class GameEngineCollision;
class GameEngineImage;
class CBabe : public GameEngineActor
{
public:
	// constrcuter destructer
	CBabe();
	~CBabe();

	static CBabe* MainBabe;

	bool IsEnd()
	{
		return m_Ending;
	}
	// delete Function
	CBabe(const CBabe& _Other) = delete;
	CBabe(CBabe&& _Other) noexcept = delete;
	CBabe& operator=(const CBabe& _Other) = delete;
	CBabe& operator=(CBabe&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	EndingAct	Act;
	bool		m_Ending = false;
	float		m_fMoveSpeed = 10.0f;
	float		m_fGravity = 1600.f;
	float		m_fGravityLimit = 850.f;
	float		m_fMoveLimit = 40.f;
	float		m_fJumpSpeed = 400.f;
	float		m_fJumpPressTime = 0.f;

	float		m_EndTime = 0.f;
	float		m_KissTime = 0.f;

	BabeState m_StateValue = BabeState::IDLE;
	float4		m_MoveDir = float4::Zero;

	GameEngineRender* m_pAnimationRender = nullptr;
	GameEngineCollision* m_pBodyCollision = nullptr;

	GameEngineImage* m_pColImage = nullptr;

	float4 PlayerPos = float4::Zero;
	void ChangeState(BabeState _State);
	void UpdateState(float _Time);

	void ColRender();

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void JumpReadyStart();
	void JumpReadyUpdate(float _Time);
	void JumpReadyEnd();

	void JumpStart();
	void JumpUpdate(float _Time);
	void JumpEnd();

	void KissStart();
	void KissUpdate(float _Time);
	void KissEnd();

	bool ColDown();

	void Movecalculation(float _DeltaTime);
	void GravityCalculation(float _DeltaTime);

};



