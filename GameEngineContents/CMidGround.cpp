#include "CMidGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include "EnumHeader.h"
#include "CPlayLevel.h"


float4 CMidGround::m_MapSize = float4::Zero;

CMidGround::CMidGround() 
{
}

CMidGround::~CMidGround() 
{
}

void CMidGround::Start()
{
	{
		m_pRenderMap1 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap1->SetImageToScaleToImage("AllMap11_20.Bmp");
	}

	{
		m_pRenderMap0 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap0->SetImageToScaleToImage("AllMap1_10.Bmp");
	}


	{
		m_pColMap = CreateRender(RenderOrder::COLLIDEMAP);
		m_pColMap->SetImageToScaleToImage("ColMap.Bmp");
	}

	m_MapSize = m_pColMap->GetImage()->GetImageScale();

	m_pRenderMap0->SetMove(m_pRenderMap0->GetImage()->GetImageScale().half());
	m_pRenderMap1->SetMove(m_pRenderMap1->GetImage()->GetImageScale().half());
	m_pColMap->SetMove(m_pColMap->GetImage()->GetImageScale().half());

	m_pRenderMap0->SetMove(float4{ 0,m_pRenderMap1->GetImage()->GetImageScale().y });
}

void CMidGround::Update(float _DeltaTime)
{
	if (true == GameEngineCore::GetInst()->IsDebug())
	{
		m_pColMap->SetOrder(static_cast<int>(RenderOrder::DEBUG));
	}
	else
	{
		m_pColMap->SetOrder(static_cast<int>(RenderOrder::COLLIDEMAP));
	}
}

