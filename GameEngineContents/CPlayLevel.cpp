#include "CPlayLevel.h"
#include "CPlayer.h"
#include <GameEngineBase/ga>

CPlayLevel::CPlayLevel() 
{
}

CPlayLevel::~CPlayLevel() 
{
}

void CPlayLevel::Loading()
{
	CreateActor<CPlayer>();
}

void CPlayLevel::Update()
{

}