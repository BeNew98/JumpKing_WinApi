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
	float4 fCurLPos			= float4::Zero;
	float4 fCurRPos			= float4::Zero;

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
		fCurLPos	 += _Pos;
		fCurRPos	 += _Pos;
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
class CMidGround;
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
	float		m_fGravity			= 1600.f; /*2.2f;*/
									
									
	bool		m_bWall				= false; // 나중에 삭제하기
	bool		m_bGround			= false; // 나중에 삭제하기
									
	bool		m_iCollide			= false;
	float		m_fJumpSpeed		= 1000.f; /* 1090.0f;*/
	float		m_fJumpPressTime	= 0.f;
	float4		m_HighestPos = float4{ 0,99999 };

	std::string m_DirString			= "R_";
	PlayerState m_StateValue		= PlayerState::IDLE;
	float4		m_MoveDir			= float4::Zero;

	GameEngineRender*		m_pAnimationRender	= nullptr;
	GameEngineCollision*	m_pBodyCollision	= nullptr;

	GameEngineImage*		m_pColImage			= nullptr;

	void DirCheck(const std::string_view& _AnimationName);

	void AnimChange(const std::string_view& _AnimationName);

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

	void pPosUpdate();

	bool ColLeftUp		(int _R = 0, int _G=0, int _B=0);
	bool ColRightUp		(int _R=0, int _G=0, int _B=0);
	bool ColLeftDown	(int _R=0, int _G=0, int _B=0);
	bool ColRightDown	(int _R=0, int _G=0, int _B=0);
	bool ColDownR		(int _R=0, int _G=0, int _B=0);
	bool ColDownL		(int _R=0, int _G=0, int _B=0);
	bool ColCurR		(int _R=0, int _G=0, int _B=0);
	bool ColCurL		(int _R=0, int _G=0, int _B=0);
	bool ColUpR			(int _R=0, int _G=0, int _B=0);
	bool ColUpL			(int _R=0, int _G=0, int _B=0);
	bool ColLeftAll		(int _R=0, int _G=0, int _B=0);
	bool ColRightAll	(int _R=0, int _G=0, int _B=0);
	bool ColUpAll		(int _R=0, int _G=0, int _B=0);
	bool ColDownAll		(int _R=0, int _G=0, int _B=0);
	bool ColCur			(int _R=0, int _G=0, int _B=0);
};

