#include "CPressStart.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>

#include "EnumHeader.h"

CPressStart::CPressStart() 
{
}

CPressStart::~CPressStart() 
{
}

void CPressStart::Start()
{
	pStart = CreateRender("Press Start.bmp", RenderOrder::FOREGROUND);
	float4 Pos = GameEngineWindow::GetScreenSize().half();
	Pos.y += 100.f;
	pStart->SetPosition(Pos);
	pStart->SetScaleToImage();
	pStart->SetAlpha(255);
}

void CPressStart::Update(float _DeltaTime)
{
	if (m_bLevelChangeReady)
	{
		m_fTime += _DeltaTime;
		int a = 0;
		if (m_fTime> m_fBlink)
		{
			m_fBlink += 0.05f;
			m_bAlpha = !m_bAlpha;
			int iAlpha = 255 * (int)m_bAlpha;
			pStart->SetAlpha(iAlpha);
			int a = 0;
		}
		if (m_fTime>1.5f)
		{
			GameEngineCore::GetInst()->ChangeLevel("Play");
		}
	}
	else
	{

		if (true == GameEngineInput::IsDown("Space"))
		{
			GameEngineResources::GetInst().SoundPlay("press_start.wav");
			m_bLevelChangeReady = true;
		}
	}
}

