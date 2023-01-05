#include "JumpKingCore.h"
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
	CreateLevel<CPlayLevel>("Play");
	CreateLevel<CTitleLevel>("Title");
	ChangeLevel("Play");
}

void JumpKingCore::Update()
{
}

void JumpKingCore::End()
{
}
