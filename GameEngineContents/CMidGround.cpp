#include "CMidGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnumHeader.h"
#include "CPlayLevel.h"



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


	m_pRenderMap0->SetMove(m_pRenderMap0->GetImage()->GetImageScale().half());
	m_pRenderMap1->SetMove(m_pRenderMap1->GetImage()->GetImageScale().half());
	m_pRenderMap2->SetMove(m_pRenderMap2->GetImage()->GetImageScale().half());
	m_pRenderMap3->SetMove(m_pRenderMap3->GetImage()->GetImageScale().half());
	m_pRenderMap4->SetMove(m_pRenderMap4->GetImage()->GetImageScale().half());


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
	m_pRenderMap2->SetMove(float4{ 0,fSize3 + fSize2 });
	m_pRenderMap3->SetMove(float4{ 0,fSize3 });
}

void CMidGround::Update(float _DeltaTime)
{
}

