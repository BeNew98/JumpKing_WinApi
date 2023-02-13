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
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ColMap.bmp"));
	}
	{
		GameEngineImage* pMidGround_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AllMap.bmp"));
	}


	CMidGround* pMidGround = CreateActor<CMidGround>();
	CPlayer* pActor = CreateActor<CPlayer>();

	pActor->SetPos(float4{ 44,334 });
	//pActor->SetPos(float4{ CMidGround::m_MapSize.hx(),CMidGround::m_MapSize.y - 70 });
	
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


	if (false == GameEngineInput::IsKey("Number1"))
	{
		GameEngineInput::CreateKey("Number1", '1');
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

		if (GameEngineInput::IsDown("UpArrow"))
		{
			--m_iMapNumber;
		}

		if (GameEngineInput::IsDown("DownArrow"))
		{			
			++m_iMapNumber;
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

		if (GameEngineInput::IsDown("Number1"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 44,334 });
		}

		SetCameraPos(float4{ 0,(m_iMapNumber * GameEngineWindow::GetScreenSize().y) });
	}
	else
	{
		float4 fPlayerPos = CPlayer::MainPlayer->GetPos();
		m_iMapNumber = fPlayerPos.iy()/ GameEngineWindow::GetScreenSize().iy();
		SetCameraPos(float4{ 0,(m_iMapNumber * GameEngineWindow::GetScreenSize().y) });
	}
}