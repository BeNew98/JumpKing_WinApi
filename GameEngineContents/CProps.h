#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CProps : public GameEngineActor
{
public:
	// constrcuter destructer
	CProps();
	~CProps();

	// delete Function
	CProps(const CProps& _Other) = delete;
	CProps(CProps&& _Other) noexcept = delete;
	CProps& operator=(const CProps& _Other) = delete;
	CProps& operator=(CProps&& _Other) noexcept = delete;

	void AnimChange(std::string_view _Name);

protected:
	virtual void Start() override;


private:
	GameEngineRender* AnimationRender = nullptr;
};

