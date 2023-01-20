#include "CPlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "CPlayer.h"
#include "CMidGround.h"

CPlayLevel::CPlayLevel() 
{
}

CPlayLevel::~CPlayLevel() 
{
}

void CPlayLevel::Loading()
{
	GameEngineDirectory Dir;

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	GameEngineImage* pImage_L = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("L_basecut.bmp"));
	pImage_L->Cut(4, 4);


	GameEngineImage* pImage_R = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("R_basecut.bmp"));
	pImage_R->Cut(4, 4);

	GameEngineImage* pMidGround_1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("1.bmp"));


	CPlayer* pActor = CreateActor<CPlayer>();

	CMidGround* pMidGround = CreateActor<CMidGround>();


	if (false == GameEngineInput::IsKey("PlayerOff"))
	{
		GameEngineInput::CreateKey("PlayerOff", 'R');
	}
}

void CPlayLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("PlayerOff"))
	{
		CPlayer::MainPlayer->OnOffSwtich();
	}	
}