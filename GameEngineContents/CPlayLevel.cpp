#include "CPlayLevel.h"
#include "CPlayer.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>

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

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("base.bmp"));

	CreateActor<CPlayer>();
}

void CPlayLevel::Update()
{

}