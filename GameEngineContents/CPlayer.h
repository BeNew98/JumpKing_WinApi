#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <GameEnginePlatform/GameEngineImage.h>
struct PlayerPos
{
	float4 fRightUpPos		= float4::Zero;
	float4 fRightDownPos	= float4::Zero;
	float4 fLeftUpPos		= float4::Zero;
	float4 fLeftDownPos		= float4::Zero;
	float4 fDownLPos		= float4::Zero;
	float4 fDownRPos		= float4::Zero;
	float4 fUpLPos			= float4::Zero;
	float4 fUpRPos			= float4::Zero;

	void operator +=(float4 _Pos)
	{
		fRightUpPos		+=_Pos;
		fRightDownPos	+=_Pos;
		fLeftUpPos		+=_Pos;
		fLeftDownPos	+=_Pos;
		fDownLPos		+=_Pos;
		fDownRPos		+=_Pos;
		fUpLPos			+=_Pos;
		fUpRPos			+=_Pos;
	}
};

enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP_READY,
	JUMP,
	DOWN,
	FALL
};
// 설명 :
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
	PlayerPos	pPos;

	float		m_fAccTime			= 0.0f;
	int			m_iStartFrame		= 0;
	float		m_fMoveSpeed		= 800.0f;
	float		m_fGravity			= 2.2f;
									
									
	bool		m_bWall				= false; // 나중에 삭제하기
	bool		m_bGround			= false; // 나중에 삭제하기
									
	bool		m_iCollide			= false;
	float		m_fJumpSpeed		= 1090.0f;
	float		m_fJumpPressTime	= 0.f;
	float4		m_HighestPos		= float4::Zero;

	std::string m_DirString			= "R_";
	PlayerState m_StateValue		= PlayerState::IDLE;
	float4		m_MoveDir			= float4::Zero;

	GameEngineRender*		m_pAnimationRender	= nullptr;
	GameEngineCollision*	m_pBodyCollision	= nullptr;

	GameEngineImage*		m_pColImage			= nullptr;

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

	void FallStart();
	void FallUpdate(float _Time);
	void FallEnd();

	void Movecalculation(float _DeltaTime);


	void TestRender();
	void ColRender();

	bool ColLeftUp();
	bool ColRightUp();
	bool ColLeftDown();
	bool ColRightDown();
	bool ColDownR();
	bool ColDownL();
	bool ColUpR();
	bool ColUpL();
	bool ColLeftAll();
	bool ColRightAll();
	bool ColUpAll();
	bool ColDownAll();
	bool ColCur();
};

