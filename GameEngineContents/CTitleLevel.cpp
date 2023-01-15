#include "CTitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "CBackGround.h"

CTitleLevel::CTitleLevel() 
{
}

CTitleLevel::~CTitleLevel() 
{
}

void CTitleLevel::Loading()
{
	GameEngineDirectory Dir;

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Title");
	GameEngineImage* pImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("title_logo.bmp"));

	if (false == GameEngineInput::IsKey("LevelChange"))
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}

	CreateActor<CBackGround>();
}

void CTitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChange"))
	{
		GameEngineCore::GetInst()->ChangeLevel("Play");
	}
}

