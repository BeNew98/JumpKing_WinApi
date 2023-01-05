#include "CPlayLevel.h"
#include "CPlayer.h"


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