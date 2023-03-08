#include "CEndLevel.h"
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>

#include "CPlayLevel.h"
#include "CEndGround.h"
#include "CBlackScreen.h"

CEndLevel::CEndLevel() 
{
}

CEndLevel::~CEndLevel() 
{
}

void CEndLevel::Loading()
{
	GameEngineDirectory Dir;

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("End");

	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
	}
	SetCameraPos(float4::Zero);

	CEndGround* pEndGround = CreateActor<CEndGround>();
}

void CEndLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("space"))
	{
		CPlayLevel::BGMPlayer.Stop();
		GameEngineCore::GetInst()->ChangeLevel("Title");
	}
}

void CEndLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	CBlackScreen* BS = CreateActor<CBlackScreen>();
	BS->SetFadeIn();
}

