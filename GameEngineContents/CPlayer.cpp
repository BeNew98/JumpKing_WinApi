#include "CPlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>

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

	Rectangle(
		GameEngineWindow::GetDrawHdc(),
		PlayerPos.ix() - 50,
		PlayerPos.iy() - 50,
		PlayerPos.ix() + 50,
		PlayerPos.iy() + 50
	);

}