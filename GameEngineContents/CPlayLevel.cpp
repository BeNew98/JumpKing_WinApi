#include "CPlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include "CPlayer.h"
#include "CMidGround.h"
#include "EnumHeader.h"

CPlayLevel::CPlayLevel() 
{
}

CPlayLevel::~CPlayLevel() 
{
}

void CPlayLevel::Loading()
{	
	GameEngineDirectory Dir;

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	GameEngineImage* pImage_L = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("L_basecut.bmp"));
	pImage_L->Cut(4, 4);


	GameEngineImage* pImage_R = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("R_basecut.bmp"));
	pImage_R->Cut(4, 4);

	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Col.bmp"));
	}
	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AllMap.bmp"));
	}
	/* {
		GameEngineImage* pMidGround = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("1.bmp"));
	} 
	{
		GameEngineImage* pMidGround = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("2.bmp"));
	}
	{
		GameEngineImage* pMidGround = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("3.bmp"));
	}
	{
		GameEngineImage* pMidGround = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("4.bmp"));
	}
	{
		GameEngineImage* pMidGround = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("5.bmp"));
	}
	{
		GameEngineImage* pMidGround = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("6.bmp"));
	}

	
	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("1_col.bmp"));
	}
	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("2_col.bmp"));
	}
	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("3_col.bmp"));
	}
	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("4_col.bmp"));
	}
	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("5_col.bmp"));
	}
	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("6_col.bmp"));
	}*/



	CMidGround* pMidGround = CreateActor<CMidGround>();
	CPlayer* pActor = CreateActor<CPlayer>();
	pActor->SetPos(float4{ CMidGround::m_MapSize.hx(),CMidGround::m_MapSize.y - 70 });

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}

	if (false == GameEngineInput::IsKey("PlayerSetOn"))
	{
		GameEngineInput::CreateKey("PlayerSetOn", 'Q');
	}

	if (false == GameEngineInput::IsKey("UpArrow"))
	{
		GameEngineInput::CreateKey("UpArrow", 'W');
	}

	if (false == GameEngineInput::IsKey("DownArrow"))
	{
		GameEngineInput::CreateKey("DownArrow", 'S');
	}

	if (false == GameEngineInput::IsKey("LeftArrow"))
	{
		GameEngineInput::CreateKey("LeftArrow", 'A');
	}

	if (false == GameEngineInput::IsKey("RightArrow"))
	{
		GameEngineInput::CreateKey("RightArrow", 'D');
	}

}

void CPlayLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch(); 
		GameEngineCore::GetInst()->DebugSwitch();
	}	
	if (GameEngineCore::GetInst()->IsDebug())
	{
		if (GameEngineInput::IsDown("PlayerSetOn"))
		{
			CPlayer::MainPlayer->SetPos(GetMousePosToCamera());
		}

		if (GameEngineInput::IsPress("UpArrow"))
		{
			SetCameraMove(float4{ 0.f,-300.f }*_DeltaTime);
		}

		if (GameEngineInput::IsPress("DownArrow"))
		{			
			SetCameraMove(float4{ 0,300.f }*_DeltaTime);
		}

		//if (GameEngineInput::IsPress("LeftArrow"))
		//{
		//	SetCameraMove(float4{ -300.f,0.f }*_DeltaTime);
		//}
		//
		//if (GameEngineInput::IsPress("RightArrow"))
		//{
		//	SetCameraMove(float4{ 300.f,0.f }*_DeltaTime);
		//}
	}
	else
	{
		float4 fPlayerPos = CPlayer::MainPlayer->GetPos();
		float4 fMapSize = CMidGround::m_MapSize;
		int PlayerCamera = fPlayerPos.iy()/ GameEngineWindow::GetScreenSize().iy();
		SetCameraPos(float4{ 0,(PlayerCamera * GameEngineWindow::GetScreenSize().y) });
	}
}