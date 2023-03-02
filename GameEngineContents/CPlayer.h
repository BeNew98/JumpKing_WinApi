#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

struct Color
{
	int R = 0;
	int G = 0;
	int B = 0;
};
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

	float4 fCurDLPos		= float4::Zero;
	float4 fCurDRPos		= float4::Zero;

	float4 fCurULPos		= float4::Zero;
	float4 fCurURPos		= float4::Zero;

	void operator +=(float4 _Pos)
	{
		fRightUpPos		+= _Pos;
		fRightDownPos	+= _Pos;
		fLeftUpPos		+= _Pos;
		fLeftDownPos	+= _Pos;
		fDownLPos		+= _Pos;
		fDownRPos		+= _Pos;
		fUpLPos			+= _Pos;
		fUpRPos			+= _Pos;
		fCurDLPos		+= _Pos;
		fCurDRPos		+= _Pos;
		fCurULPos		+= _Pos;
		fCurURPos		+= _Pos;
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

	void AddMoveDir(float4 _Dir)
	{
		m_MoveDir += _Dir;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	PlayerPos	pPos;

	float		m_fAccTime			= 0.0f;
	int			m_iStartFrame		= 0;
	float		m_fMoveSpeed		= 170.0f;
	float		m_fJumpMoveSpeed	= 400.0f;
	float		m_fGravity			= 1600.f; /*2.2f;*/
	float		m_fGravityLimit		= 850.f;
	float		m_fMoveLimit		= 170.f;
	float		m_fJumpMoveLimit	= 400.f;
	
	float		m_fRecoilCoeff		= 0.475f;
									
	bool		m_bWall				= false; // 나중에 삭제하기
	bool		m_bGround			= false; // 나중에 삭제하기
									
	bool		m_iCollide			= false;
	float		m_fJumpSpeed		= 1000.f; /* 1090.0f;*/
	float		m_fJumpPressTime	= 0.f;
	float		m_fKnockTime		= 0.f;
	float4		m_HighestPos		= float4{ 0,99999 };

	Color m_Red						= { 255,0,0 };
	Color m_Green					= { 0,255,0 };
	Color m_Blue					= { 0,0,255 };
	Color m_Sky						= { 0,255,255 };
	Color m_Black					= { 0,0,0 };

	GameEngineSoundPlayer Jump;


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

	bool ColLeftUp	(Color _Color = {0,0,0});
	bool ColRightUp	(Color _Color = {0,0,0});

	bool ColLeftDown(Color _Color = {0,0,0});
	bool ColRightDown(Color _Color = {0,0,0});

	bool ColDownR(Color _Color = {0,0,0});
	bool ColDownL(Color _Color = {0,0,0});

	bool ColCurDR(Color _Color = {0,0,0});
	bool ColCurDL(Color _Color = {0,0,0});

	bool ColCurUR(Color _Color = {0,0,0});
	bool ColCurUL(Color _Color = {0,0,0});

	bool ColUpR(Color _Color = {0,0,0});
	bool ColUpL(Color _Color = {0,0,0});

	bool ColLeftAll(Color _Color = {0,0,0});
	bool ColRightAll(Color _Color = {0,0,0});
	bool ColUpAll(Color _Color = {0,0,0});
	bool ColDownAll(Color _Color = {0,0,0});
	bool ColCurDownAll(Color _Color = {0,0,0});
	bool ColCurUpAll(Color _Color = {0,0,0});

	bool ColCurDown(Color _Color = {0,0,0});

	void FloorCalibration();
	void WallCalibration();
};

