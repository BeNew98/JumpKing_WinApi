#include "CTitleLogo.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

#include "CPressStart.h"
#include "CBackGround.h"
#include "EnumHeader.h"

CTitleLogo::CTitleLogo() 
{
}

CTitleLogo::~CTitleLogo() 
{
}


void CTitleLogo::Start()
{
	pLogoRender = CreateRender("title_logo.bmp", RenderOrder::MIDGROUND);
	pLogoRender->SetPosition({ GameEngineWindow::GetScreenSize().half() });
	pLogoRender->SetScale({ 784,222 });
	pLogoRender->SetMove({ 0,-pLogoRender->GetScale().hy() });
	pLogoRender->SetAlpha(Alpha);
}

void CTitleLogo::Update(float _Deltatime)
{
	if (m_bShock)
	{
		if (m_Time > 0.5f)
		{
			return;
		}
		m_Time += _Deltatime;
		if (m_Time>m_fShockTime)
		{
			m_fShockTime += 0.05f;
			ShockPos.y *= -1;
			SetPos(ShockPos);
		}
		return;
	}
	if (214 > pLogoRender->GetPosition().iy())
	{
		GetLevel()->CreateActor<CPressStart>();
		GameEngineResources::GetInst().SoundPlay("title_hit.wav");
		m_bShock = true; 
		m_Time = 0.f;
		ShockPos += GetPos()+(float4::Up * 3.f);
	}
	else
	{
		m_Time += _Deltatime;
		pLogoRender->SetMove(float4::Up * MoveSpeed * _Deltatime);

		if (m_Time>0.5f&& Alpha<255)
		{
			m_Time = 0.f;
			Alpha += 51; 
			pLogoRender->SetAlpha(Alpha);;
		}
		
	}
}

