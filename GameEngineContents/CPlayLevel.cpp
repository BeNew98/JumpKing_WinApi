#include "CPlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
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

	GameEngineImage* pMidGround_1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("1.bmp"));

	GameEngineImage* pMidGround_2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("2.bmp"));

	GameEngineImage* pMidGround_1_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("1_col.bmp"));

	GameEngineImage* pMidGround_2_col = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("2_col.bmp"));



	CPlayer* pActor = CreateActor<CPlayer>();
	pActor->SetPos({ static_cast<float>(GameEngineWindow::GetScreenSize().hix()),600});
	CMidGround* pMidGround = CreateActor<CMidGround>();


	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}

	if (false == GameEngineInput::IsKey("PlayerSetOn"))
	{
		GameEngineInput::CreateKey("PlayerSetOn", 'D');
	}

	if (false == GameEngineInput::IsKey("UpArrow"))
	{
		GameEngineInput::CreateKey("UpArrow", VK_UP);
	}

	if (false == GameEngineInput::IsKey("DownArrow"))
	{
		GameEngineInput::CreateKey("DownArrow", VK_DOWN);
	}

	if (false == GameEngineInput::IsKey("ShowColMap"))
	{
		GameEngineInput::CreateKey("ShowColMap", 'B');
	}
}

void CPlayLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch();
		DebugMode();
	}	
	if (m_DebugOn)
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

		if (GameEngineInput::IsDown("ShowColMap"))
		{
			std::vector<GameEngineActor*> vMidground = GetActors(static_cast<int>(RenderOrder::MIDGROUND));

			for(GameEngineActor* pMidground : vMidground)
			{
				pMidground->SetOrder(static_cast<int>(RenderOrder::DEBUG));
			}
		}
	}

}