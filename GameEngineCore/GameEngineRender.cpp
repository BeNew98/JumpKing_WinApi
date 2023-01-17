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
}

void GameEngineRender::SetOrder(int _Order)
{
	Order = _Order;
	Owner->GetLevel()->PushRender(this);
}

void GameEngineRender::Render(float _DeltaTime)
{
	if (nullptr!= CurrentAnimation)
	{
		CurrentAnimation->Render(_DeltaTime);
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
		Image = CurrentAnimation->Image;
	}
	float4 RenderPos = Owner->GetPos() + Position;

	if (true == Image->IsImageCutting())
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, Scale);
	}
	else
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, Scale, { 0, 0 }, Image->GetImageScale());
	}
}

void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	CurrentTime = _DeltaTime;

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
				CurrentIndex = FrameIndex.size() - 1;
			}
		}
		CurrentTime = FrameTime[CurrentIndex];
	}
}


void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Parameter)
{
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Parameter.ImageName);

	if (nullptr == Image)
	{
		MsgAssert("존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	std::string UpperName = GameEngineString::ToUpper(_Parameter.AnimationName);

	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("이미 존재하는 이름의 애니메이션 입니다." + UpperName);
	}

	FrameAnimation& NewAnimation = Animation[UpperName];

	NewAnimation.Image = Image;

	if (0!= _Parameter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Parameter.FrameTime;
	}
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); i++)
		{
			NewAnimation.FrameTime.push_back(_Parameter.InterTime);
		}
	}
	NewAnimation.Loop = _Parameter.Loop;
	NewAnimation.Parent = this;
}

void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("존재하지 않는 애니메이션으로 바꾸려고 했습니다." + UpperName);
	}

	if (CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	CurrentAnimation = &Animation[UpperName];

	CurrentAnimation->CurrentIndex = 0;

	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}