#include "GameEngineRender.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

GameEngineRender::GameEngineRender() 
{
}

GameEngineRender::~GameEngineRender() 
{
}

void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
	SetScaleToImage();
}

void GameEngineRender::SetScaleToImage()
{
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʾҴµ� �̹����� ũ��� �����Ϸ��� �߽��ϴ�.");
	}

	SetScale(Image->GetImageScale());
}

void GameEngineRender::SetFrame(int _Frame)
{
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʴ� Renderer�� �������� �����Ϸ��� �߽��ϴ�.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("��ȿ���� ���� �̹��� �ε��� �Դϴ�.");
	}

	Frame = _Frame;
}

void GameEngineRender::SetOrder(int _Order)
{
	GetActor()->GetLevel()->PushRender(this,_Order);
}

void GameEngineRender::SetText(const std::string_view& _Text)
{
	RenderText = _Text;
}

void GameEngineRender::Render(float _DeltaTime)
{
	if (RenderText != "")
	{
		TextRender(_DeltaTime);
	}
	else
	{
		ImageRender(_DeltaTime);
	}
}

void GameEngineRender::TextRender(float _DeltaTime)
{

	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	float4 RenderPos = GetActorPlusPos() - CameraPos;

	TextOutA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderPos.ix(), RenderPos.iy(), RenderText.c_str(), static_cast<int>(RenderText.size()));

	return;
}


void GameEngineRender::ImageRender(float _DeltaTime)
{
	if (nullptr != CurrentAnimation)
	{
		CurrentAnimation->Render(_DeltaTime);
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
		Image = CurrentAnimation->Image;
	}

	if (nullptr == Image)
	{
		MsgAssert("�̹����� ���������� �ʾҽ��ϴ�.");
	}

	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	float4 RenderPos = GetActorPlusPos() - CameraPos;

	if (true == Image->IsImageCutting())
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale());
	}
	else
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale());
	}
}



bool GameEngineRender::FrameAnimation::IsEnd()
{
	int Value = (static_cast<int>(FrameIndex.size()) - 1);
	return CurrentIndex == Value;
}

void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	CurrentTime -= _DeltaTime;

	if (CurrentTime<=0.0f)
	{
		++CurrentIndex;

		if (FrameIndex.size() <= CurrentIndex)
		{
			if (Loop == true)
			{
				CurrentIndex = 0;
			}
			else
			{
				CurrentIndex = static_cast<int>(FrameIndex.size()) - 1;
			}
		}
		CurrentTime = FrameTime[CurrentIndex];
	}
}


bool GameEngineRender::IsAnimationEnd()
{
	return CurrentAnimation->IsEnd();
}

void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Parameter)
{
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Parameter.ImageName);

	if (nullptr == Image)
	{
		MsgAssert("�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	std::string UpperName = GameEngineString::ToUpper(_Parameter.AnimationName);

	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼� �Դϴ�." + UpperName);
	}

	FrameAnimation& NewAnimation = Animation[UpperName];

	NewAnimation.Image = Image;

	if (0 != _Parameter.FrameIndex.size())
	{
		NewAnimation.FrameIndex = _Parameter.FrameIndex;
	}
	else
	{
		for (int i = _Parameter.Start; i <= _Parameter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	if (0 != _Parameter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Parameter.FrameTime;
	}
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Parameter.InterTime);
		}
	}
	NewAnimation.Loop = _Parameter.Loop;
	NewAnimation.Parent = this;
}

void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("�������� �ʴ� �ִϸ��̼����� �ٲٷ��� �߽��ϴ�." + UpperName);
	}

	if (false == _ForceChange && CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	CurrentAnimation = &Animation[UpperName];

	CurrentAnimation->CurrentIndex = 0;

	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}