#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP_READY,
	JUMP,
	DOWN,
	COLLIDE

};
// Ό³Έν :
class CPlayer : public GameEngineActor
{
public:
	static CPlayer* MainPlayer;

	// constrcuter destructer
	CPlayer();
	~CPlayer();

	// delete Function
	CPlayer(const CPlayer& _Other) = delete;
	CPlayer(CPlayer&& _Other) noexcept = delete;
	CPlayer& operator=(const CPlayer& _Other) = delete;
	CPlayer& operator=(CPlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float m_fAccTime = 0.0f;
	int m_iStartFrame = 0;
	float m_fMoveSpeed = 500.0f;

	bool m_bGround = false;
	float m_fGravity = 700.0f;

	bool m_bWall = false;

	float m_fJumpSpeed = 600.0f;
	float m_fJumpPressTime = 0.f;;

	std::string m_DirString = "R_";
	PlayerState m_StateValue = PlayerState::IDLE;
	float4 m_MoveDir = float4::Zero;

	GameEngineRender* m_pAnimationRender = nullptr;
	GameEngineCollision* m_pBodyCollision = nullptr;

	void DirCheck(const std::string_view& _AnimationName);
	

	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

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

	void DownStart();
	void DownUpdate(float _Time);
	void DownEnd();

	void CollideStart();
	void CollideUpdate(float _Time);
	void CollideEnd();

	void Movecalculation(float _DeltaTime);

};

