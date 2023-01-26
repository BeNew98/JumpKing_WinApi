#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class PlayerState
{
	IDLE,
	MOVE,
	LOOKUP,
	JUMP_READY,
	JUMP,

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

	float AccTime = 0.0f;
	int StartFrame = 0;
	float MoveSpeed = 100.0f;


	std::string DirString = "R_";
	PlayerState StateValue = PlayerState::IDLE;
	float4 MoveDir = float4::Zero;

	GameEngineRender* AnimationRender = nullptr;

	void DirCheck(const std::string_view& _AnimationName);
	

	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void Movecalculation(float _DeltaTime);

};

