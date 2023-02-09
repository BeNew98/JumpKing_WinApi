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
		m_pRenderMap0->SetImageToScaleToImage("AllMap.Bmp");
	}
	{
		m_pColMap0 = CreateRender(RenderOrder::COLLIDEMAP);
		m_pColMap0->SetImageToScaleToImage("Col.Bmp");
	}
	m_MapSize = m_pRenderMap0->GetImage()->GetImageScale();
	SetMove(m_pRenderMap0->GetImage()->GetImageScale().half());
}

void CMidGround::Update(float _DeltaTime)
{
	if (true == GameEngineCore::GetInst()->IsDebug())
	{
		m_pColMap0->SetOrder(static_cast<int>(RenderOrder::DEBUG));
	}
	else
	{
		m_pColMap0->SetOrder(static_cast<int>(RenderOrder::COLLIDEMAP));
	}
}

