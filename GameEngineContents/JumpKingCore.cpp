#include "JumpKingCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "CPlayLevel.h"
#include "CTitleLevel.h"

JumpKingCore::JumpKingCore()
{
}

JumpKingCore::~JumpKingCore() 
{
}

void JumpKingCore::Start()
{
	GameEngineWindow::SettingWindowSize({ 960, 720 });

	CreateLevel<CTitleLevel>("Title");
	CreateLevel<CPlayLevel>("Play");
	ChangeLevel("Play");
}

void JumpKingCore::Update()
{
}

void JumpKingCore::End()
{
}
