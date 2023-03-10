#include "CPlayLevel.h"
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>

#include "CPlayer.h"
#include "CMidGround.h"
#include "CBackGround.h"
#include "CForeGround.h"
#include "CColMap.h"
#include "CFlag.h"
#include "CSnow.h"
#include "CCandle.h"
#include "CJump.h"
#include "CBabe.h"
#include "CAngel.h"
#include "EnumHeader.h"
#include "CBlackScreen.h"

GameEngineSoundPlayer CPlayLevel::BGMPlayer;

CPlayLevel::CPlayLevel() 
{
}

CPlayLevel::~CPlayLevel() 
{
}

void CPlayLevel::SetCandle(float _X , float _Y)
{
	
	CCandle* pCandle0 = CreateActor<CCandle>();
	pCandle0->SetPos(float4{ _X,_Y });


	CCandle* pCandle1 = CreateActor<CCandle>();
	pCandle1->SetPos(pCandle0->GetPos() + float4{ 16,0 });


	CCandle* pCandle2 = CreateActor<CCandle>();
	pCandle2->SetPos(pCandle0->GetPos() + float4{ 8,18 });


	CCandle* pCandle3 = CreateActor<CCandle>();
	pCandle3->SetPos(pCandle0->GetPos() + float4{ 48,0 });


	CCandle* pCandle4 = CreateActor<CCandle>();
	pCandle4->SetPos(pCandle3->GetPos() + float4{ 16,0 });


	CCandle* pCandle5 = CreateActor<CCandle>();
	pCandle5->SetPos(pCandle3->GetPos() + float4{ 8,18 });
	
}

void CPlayLevel::SetCandleMiddle(float _X, float _Y)
{

	CCandle* pCandle0 = CreateActor<CCandle>();
	pCandle0->SetPos(float4{ _X,_Y });


	CCandle* pCandle1 = CreateActor<CCandle>();
	pCandle1->SetPos(pCandle0->GetPos() + float4{ 33,0 });


	CCandle* pCandle2 = CreateActor<CCandle>();
	pCandle2->SetPos(pCandle0->GetPos() + float4{ 13,30 });


	CCandle* pCandle2_1 = CreateActor<CCandle>();
	pCandle2_1->SetPos(pCandle0->GetPos() + float4{ 30,30 });


	CCandle* pCandle3 = CreateActor<CCandle>();
	pCandle3->SetPos(pCandle0->GetPos() + float4{ 68,0 });


	CCandle* pCandle4 = CreateActor<CCandle>();
	pCandle4->SetPos(pCandle3->GetPos() + float4{ 33,0 });


	CCandle* pCandle5 = CreateActor<CCandle>();
	pCandle5->SetPos(pCandle3->GetPos() + float4{ 3,30 });

	CCandle* pCandle5_1 = CreateActor<CCandle>();
	pCandle5_1->SetPos(pCandle3->GetPos() + float4{ 20,30 });
}

void CPlayLevel::SetCandleLarge(float _X, float _Y)
{
	float x = _X;
	float y = _Y;
	SetCandle(x, y);	
	SetCandle(x + 122 ,y);
	SetCandleMiddle(x + 40,y+61);
}

void CPlayLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("jump_king");

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().SoundLoad(Files[i].GetFullPath());
	}

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("babe");

	Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().SoundLoad(Files[i].GetFullPath());
	}

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("music");

	Files = Dir.GetAllFile();
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
	Dir.Move("Player");

	GameEngineImage* pImage_L = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("L_basecut.bmp").GetPathToString());
	pImage_L->Cut(4, 4);


	GameEngineImage* pImage_R = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("R_basecut.bmp").GetPathToString());
	pImage_R->Cut(4, 4);

	GameEngineImage* pJumpParticle = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("jump_particle.bmp").GetPathToString());
	pJumpParticle->Cut(3, 2);

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

	GameEngineImage* pCandleEffect = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CandleEffect.bmp").GetPathToString());
	pCandleEffect->Cut(2, 2);

	GameEngineImage* pBonfire = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Bonfire.bmp").GetPathToString());
	pBonfire->Cut(1, 3);


	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	Dir.Move("Particle");
	
	GameEngineImage* pSnow = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("snow.bmp").GetPathToString());
	pSnow->Cut(2, 2);



	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	Dir.Move("End");

	GameEngineImage* Angel = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Angel.bmp").GetPathToString());
	Angel->Cut(2, 2);

	GameEngineImage* Babe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Babe.bmp").GetPathToString());
	Babe->Cut(4, 2);

	GameEngineImage* CrownKing = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CrownKing.bmp").GetPathToString());
	CrownKing->Cut(2, 3);

	GameEngineImage* Fly = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Fly.bmp").GetPathToString());
	Fly->Cut(3, 3);

	GameEngineImage* KingBabe = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("KingBabe.bmp").GetPathToString());
	KingBabe->Cut(3, 3);

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

	if (false == GameEngineInput::IsKey("Space"))
	{
		GameEngineInput::CreateKey("Space", ' ');
	}


	if (false == GameEngineInput::IsKey("Number1"))
	{
		GameEngineInput::CreateKey("Number1", '1');
	}
	if (false == GameEngineInput::IsKey("Number2"))
	{
		GameEngineInput::CreateKey("Number2", '2');
	}
	if (false == GameEngineInput::IsKey("Number3"))
	{
		GameEngineInput::CreateKey("Number3", '3');
	}
	if (false == GameEngineInput::IsKey("Number4"))
	{
		GameEngineInput::CreateKey("Number4", '4');
	}
	if (false == GameEngineInput::IsKey("Number5"))
	{
		GameEngineInput::CreateKey("Number5", '5');
	}
	if (false == GameEngineInput::IsKey("Number6"))
	{
		GameEngineInput::CreateKey("Number6", '6');
	}
	if (false == GameEngineInput::IsKey("Number7"))
	{
		GameEngineInput::CreateKey("Number7", '7');
	}
	if (false == GameEngineInput::IsKey("Number8"))
	{
		GameEngineInput::CreateKey("Number8", '8');
	}
	if (false == GameEngineInput::IsKey("Number9"))
	{
		GameEngineInput::CreateKey("Number9", '9');
	}



}
void CPlayLevel::Loading()
{	
	SoundLoad();
	ImageLoad();
	KeyLoad();

	SetCandle(199, 7486);
	SetCandle(230, 7215);
	SetCandle(677, 7215);
	SetCandle(599, 7332);
	SetCandle(791, 7379);
	SetCandle(342, 7459);
	SetCandle(552, 7524);
	SetCandle(440, 7650);	

	SetCandleMiddle(260, 7670);

	SetCandleLarge(139, 6866);
	SetCandleLarge(443, 6740);
	SetCandleLarge(651, 6853);
	SetCandleLarge(284, 7027);
	
	SetCandle(230, 7156);
	SetCandle(678, 7156);


	SetCandleLarge(283, 5941);
	SetCandleLarge(490, 6069);




	CColMap* pColMap = CreateActor<CColMap>();


	CMidGround* pMidGround = CreateActor<CMidGround>();
	CBackGround* pBackGround = CreateActor<CBackGround>();
	CForeGround* pForeGround = CreateActor<CForeGround>();

	CJump* pJumpParticle = CreateActor<CJump>();

	CFlag* pFlag0 = CreateActor<CFlag>();
	pFlag0->SetPos({ 615, 15326 });
	pFlag0->AnimChange("L_Flag");

	CFlag* pFlag1 = CreateActor<CFlag>();
	pFlag1->SetPos({ 199, 13081 });
	CFlag* pFlag2 = CreateActor<CFlag>();
	pFlag2->SetPos({ 487, 13141 });

	CSnow* pSnow = CreateActor<CSnow>();
	pSnow->SetPos(float4::Zero);

	CPlayer* pActor = CreateActor<CPlayer>();

	pActor->SetPos(float4{ CColMap::m_MapSize.hx(),CColMap::m_MapSize.y - 70 });

	CBabe* pBabe = CreateActor<CBabe>();
	pBabe->SetPos({ 787,258 });

	CAngel* pAngel = CreateActor<CAngel>();
	pAngel->SetPos({ 1200, -300 });
	
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
		//GameEngineInput::MouseCursorOn();

		if (GameEngineInput::IsDown("PlayerSetOn"))
		{
			CPlayer::MainPlayer->SetPos(GetMousePosToCamera());
		}

		if (GameEngineInput::IsDown("UpArrow"))
		{
			--m_iDebugMapNumber;
		}

		if (GameEngineInput::IsDown("DownArrow"))
		{			
			++m_iDebugMapNumber;
		}

		if (GameEngineInput::IsDown("Number1"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 112,27534 });
		}
		if (GameEngineInput::IsDown("Number2"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 49,26254 });
		}
		if (GameEngineInput::IsDown("Number3"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 588,22574 });
		}
		if (GameEngineInput::IsDown("Number4"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 213,13070 });
		}
		if (GameEngineInput::IsDown("Number5"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 330,10425 });
		}
		if (GameEngineInput::IsDown("Number6"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 228,7888 });
		}
		if (GameEngineInput::IsDown("Number7"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 372,4510 });
		}
		if (GameEngineInput::IsDown("Number8"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 300,687 });
		}
		if (GameEngineInput::IsDown("Number9"))
		{
			CPlayer::MainPlayer->SetPos(float4{ 300,286 });
		}




		if (!CPlayer::MainPlayer->IsEnd())
		{		
			SetCameraPos(float4{ 0,(m_iDebugMapNumber * GameEngineWindow::GetScreenSize().y) });
		}
	}
	else
	{
		if (CPlayer::MainPlayer->bAct().Act9)
		{
			if (GameEngineInput::IsDown("space"))
			{
				GameEngineCore::GetInst()->ChangeLevel("End");
			}
		}
		if (CPlayer::MainPlayer->IsEnd())
		{
			return;
		}

		float4 fPlayerPos = CPlayer::MainPlayer->GetPos();
		m_iPrevMapNumber = m_iMapNumber;
		m_iDebugMapNumber = m_iMapNumber;
		m_iMapNumber = fPlayerPos.iy()/ GameEngineWindow::GetScreenSize().iy();
		SetCameraPos(float4{ 0,(m_iMapNumber * GameEngineWindow::GetScreenSize().y) });
	}	

	if (!CPlayer::MainPlayer->IsEnd())
	{
		BGMPlay(5, 5, "");
		BGMPlay(6, 14, "Sewer.wav");
		BGMPlay(15, 22, "Fallen King.mp3");
		BGMPlay(23, 26, "snowy windy.wav");
		BGMPlay(27, 32, "Despair.mp3");
		BGMPlay(33, 36, "Masse.mp3");
		BGMPlay(37, 39, "Sky Blue.mp3");
		BGMPlay(40, 42, "Coronation.mp3");
		BGMPlay(43, 43, "");
	}

}

void CPlayLevel::BGMPlay(int _Start, int _End, const std::string_view& _BGM)
{
	
	if (m_iPrevMapNumber != m_iMapNumber)
	{
		if (m_iMapNumber <= 43 - _Start && m_iMapNumber >= 43 - _End)
		{
			if (m_iPrevMapNumber <= 43 - _Start && m_iPrevMapNumber >= 43 - _End)
			{
				return;
			}
			BGMPlayer.Stop();
			if (_BGM == "")
			{
				return;
			}
			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl(_BGM);
			BGMPlayer.LoopCount(999);
			//BGMPlayer.Volume(0.1f);
		}
	}
}

void CPlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("opening theme.wav");
	BGMPlayer.LoopCount(1);
	CBlackScreen* BS = CreateActor<CBlackScreen>();
	BS->SetPos(float4{ 0,(42 * GameEngineWindow::GetScreenSize().y) });
	BS->SetFadeIn();
}
