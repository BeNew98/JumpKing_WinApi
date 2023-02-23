#include "CTitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>

#include "CTitleLogo.h"
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
	Dir.Move("Sound");
	Dir.Move("music");
	Dir.Move("menu loop");

	Intro = GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("menu_intro.wav"));

	
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Title");

	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
	}


	CreateActor<CTitleLogo>();
	
	//GameEngineInput::MouseCursorOff();


	GameEngineInput::CreateKey("Space", ' ');
}

void CTitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Space"))
	{
		GameEngineCore::GetInst()->ChangeLevel("Play");
	}


}

void CTitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("menu_intro.wav");
}

void CTitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

