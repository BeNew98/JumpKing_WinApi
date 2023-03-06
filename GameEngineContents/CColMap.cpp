#include "CColMap.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRender.h>
#include "CPlayer.h"
#include "EnumHeader.h"

float4 CColMap::m_MapSize = float4::Zero;

CColMap::CColMap() 
{
}

CColMap::~CColMap() 
{
}

void CColMap::Start()
{	
	m_pColMap = CreateRender(RenderOrder::COLLIDEMAP);
	m_pColMap->SetImageToScaleToImage("ColMap2.Bmp");
	m_pColMap->SetImageToScaleToImage("ColMap.Bmp");	

	m_MapSize = m_pColMap->GetImage()->GetImageScale();

	m_pColMap->SetMove(m_pColMap->GetImage()->GetImageScale().half());
}



void CColMap::Update(float _DeltaTime)
{
	if (CPlayer::MainPlayer->bAct().Act8==true&& CPlayer::MainPlayer->bAct().Act9 == false)
	{
		m_pColMap->SetImageToScaleToImage("ColMap2.Bmp");
		m_pColMap->SetMove(m_pColMap->GetImage()->GetImageScale().half());
	}
	if (true == GameEngineCore::GetInst()->IsDebug())
	{
		m_pColMap->SetOrder(static_cast<int>(RenderOrder::DEBUG));
	}
	else
	{
		m_pColMap->SetOrder(static_cast<int>(RenderOrder::COLLIDEMAP));
	}
}
