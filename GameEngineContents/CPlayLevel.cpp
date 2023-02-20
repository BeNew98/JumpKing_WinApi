#include "CPlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineFile.h>

#include "CPlayer.h"
#include "CMidGround.h"
#include "CBackGround.h"
#include "CForeGround.h"
#include "CProps.h"
#include "EnumHeader.h"


CPlayLevel::CPlayLevel() 
{
}

CPlayLevel::~CPlayLevel() 
{
}

void CPlayLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().SoundLoad(Files[i].GetFullPath());
	}
}

void CPlayLevel::ImageLoad()
{
	GameEngineDirectory Dir;

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	GameEngineImage* pImage_L = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("L_basecut.bmp").GetPathToString());
	pImage_L->Cut(4, 4);


	GameEngineImage* pImage_R = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("R_basecut.bmp").GetPathToString());
	pImage_R->Cut(4, 4);


	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	Dir.Move("MidGround");

	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
	}	

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	Dir.Move("ForeGround");

	Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
	}

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	Dir.Move("BackGround");

	Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().ImageLoad(Files[i].GetFullPath());
	}

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	Dir.Move("Props");

	GameEngineImage* pR_Flag = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("R_Flag.bmp").GetPathToString());
	pR_Flag->Cut(2, 5);

	GameEngineImage* pL_Flag = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("L_Flag.bmp").GetPathToString());
	pL_Flag->Cut(2, 5);

	GameEngineImage* pCandle = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Candle.bmp").GetPathToString());
	pCandle->Cut(2, 2);

	GameEngineImage* pBonfire = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Bonfire.bmp").GetPathToString());
	pBonfire->Cut(1, 3);
}
void CPlayLevel::KeyLoad()
{
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
	if (false == GameEngineInput::IsKey("Number2"))
	{
		GameEngineInput::CreateKey("Number2", '2');
	}
}
void CPlayLevel::Loading()
{	
	SoundLoad();
	ImageLoad();
	KeyLoad();

	CMidGround* pMidGround = CreateActor<CMidGround>();
	CBackGround* pBackGround = CreateActor<CBackGround>();
	CForeGround* pForeGround = CreateActor<CForeGround>();
	CProps* pProps0 = CreateActor<CProps>();
	pProps0->AnimChange("R_Flag");
	pProps0->SetPos({ 201, 13085 });

	CProps* pProps1= CreateActor<CProps>();
	pProps1->AnimChange("R_Flag");
	pProps1->SetPos({ 486, 13154 });


	CPlayer* pActor = CreateActor<CPlayer>();

	//pActor->SetPos(float4{ 841,3934 });
	pActor->SetPos(float4{ CMidGround::m_MapSize.hx(),CMidGround::m_MapSize.y - 70 });
	
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
			CPlayer::MainPlayer->SetPos(float4{ 600,4848 });
		}
		if (GameEngineInput::IsDown("Number2"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 465,3729 });
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