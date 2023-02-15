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
		m_pRenderMap0 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap0->SetImageToScaleToImage("AllMap1_10.Bmp");
	}

	{
		m_pRenderMap1 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap1->SetImageToScaleToImage("AllMap11_20.Bmp");
	}

	{
		m_pRenderMap2 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap2->SetImageToScaleToImage("AllMap21_30.Bmp");
	}

	{
		m_pRenderMap3 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap3->SetImageToScaleToImage("AllMap31_40.Bmp");
	}

	{
		m_pRenderMap4 = CreateRender(RenderOrder::MIDGROUND);
		m_pRenderMap4->SetImageToScaleToImage("AllMap41_43.Bmp");
	}

	{
		m_pColMap = CreateRender(RenderOrder::COLLIDEMAP);
		m_pColMap->SetImageToScaleToImage("ColMap.Bmp");
	}

	m_MapSize = m_pColMap->GetImage()->GetImageScale();

	m_pRenderMap0->SetMove(m_pRenderMap0->GetImage()->GetImageScale().half());
	m_pRenderMap1->SetMove(m_pRenderMap1->GetImage()->GetImageScale().half());
	m_pRenderMap2->SetMove(m_pRenderMap2->GetImage()->GetImageScale().half());
	m_pRenderMap3->SetMove(m_pRenderMap3->GetImage()->GetImageScale().half());
	m_pRenderMap4->SetMove(m_pRenderMap4->GetImage()->GetImageScale().half());

	m_pColMap->SetMove(m_pColMap->GetImage()->GetImageScale().half());

	float fSize0 = 0.f;
	float fSize1 = 0.f;
	float fSize2 = 0.f;
	float fSize3 = 0.f;
	fSize0 = m_pRenderMap1->GetImage()->GetImageScale().y;
	fSize1 = m_pRenderMap2->GetImage()->GetImageScale().y;
	fSize2 = m_pRenderMap3->GetImage()->GetImageScale().y;
	fSize3 = m_pRenderMap4->GetImage()->GetImageScale().y;

	m_pRenderMap0->SetMove(float4{ 0,fSize3 + fSize2 + fSize1 + fSize0 });
	m_pRenderMap1->SetMove(float4{ 0,fSize3 + fSize2 + fSize1 });
	m_pRenderMap2->SetMove(float4{ 0,fSize3+ fSize2 });
	m_pRenderMap3->SetMove(float4{ 0,fSize3 });
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

