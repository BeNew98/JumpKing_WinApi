#include "JumpKingCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "CPlayLevel.h"
#include "CTitleLevel.h"
#include "CEndLevel.h"

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
	CreateLevel<CEndLevel>("End");
	ChangeLevel("Title");
}

void JumpKingCore::Update()
{
}

void JumpKingCore::End()
{
}
