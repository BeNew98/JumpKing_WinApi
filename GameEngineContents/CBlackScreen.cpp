#include "CBlackScreen.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"

CBlackScreen::CBlackScreen() 
{
}

CBlackScreen::~CBlackScreen() 
{
}

void CBlackScreen::FadeIn(float _DeltaTime)
{
	pBlackScreenRender->SetOrder(static_cast<int>(RenderOrder::FOREGROUND));
	m_fTime += _DeltaTime;

	if (m_fTime > 0.5f && m_iAlpha > 0)
	{
		m_fTime = 0.f;
		m_iAlpha -= 51;
		pBlackScreenRender->SetAlpha(m_iAlpha);;
	}
	if (m_iAlpha==0)
	{
		pBlackScreenRender->Off();
	}
}

void CBlackScreen::Start()
{
	pBlackScreenRender = CreateRender("BlackScreen.bmp", RenderOrder::BACKGROUND);
	pBlackScreenRender->SetPosition({ GameEngineWindow::GetScreenSize().half() });
	pBlackScreenRender->SetScaleToImage();
	pBlackScreenRender->SetAlpha(m_iAlpha);
}

void CBlackScreen::Update(float _DeltaTime)
{
	if (m_bFadeIn)
	{
		FadeIn(_DeltaTime);
		if (m_iAlpha==0)
		{
			m_bFadeIn = false;
		}
	}
}

