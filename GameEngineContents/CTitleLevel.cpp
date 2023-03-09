#include "CTitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>

#include "CTitleLogo.h"
#include "CBlackScreen.h"
#include "CCompanyLogo.h"
#include "CPressStart.h"

GameEngineSoundPlayer CTitleLevel::BGMPlayer;

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
	Dir.Move("Title");

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().SoundLoad(Files[i].GetFullPath());
	}
	
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Title");

	Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
	}

	Nexile = CreateActor<CCompanyLogo>();
	

	GameEngineInput::CreateKey("Space", ' ');
}

void CTitleLevel::Update(float _DeltaTime)
{
	m_Time += _DeltaTime;
	if (m_Time>2.f&& Act.Act0 == false)
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("menu_intro.wav");
		Nexile->Off();
		m_Time = 0.f;
		CreateActor<CBlackScreen>();
		CreateActor<CTitleLogo>();
		Act.Act0 = true;
	}
}

void CTitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Act = {};
	Nexile->On();
}

void CTitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

