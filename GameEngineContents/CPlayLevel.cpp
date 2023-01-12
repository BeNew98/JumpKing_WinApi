#include "CPlayLevel.h"
#include "CPlayer.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineTime.h>

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
	GameEngineImage* pImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("basecut.bmp"));
	pImage->Cut(4, 4);


	CreateActor<CPlayer>();
}

void CPlayLevel::Update()
{

}