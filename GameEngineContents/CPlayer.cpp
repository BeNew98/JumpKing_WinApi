#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>

CPlayer::CPlayer() 
{
}

CPlayer::~CPlayer() 
{
}


void CPlayer::Start()
{
	SetMove(GameEngineWindow::GetScreenSize().half());
}

void CPlayer::Update()
{
	SetMove(float4::Left * 0.0001f);
}

void CPlayer::Render()
{
	float4 PlayerPos = GetPos();

	GameEngineImage* pImage = GameEngineResources::GetInst().ImageFind("base.bmp");
	
	GameEngineWindow::GetBackBufferImage()->BitCopy(pImage, PlayerPos - float4{ 50, 50 }, { 100, 100 });
	

}