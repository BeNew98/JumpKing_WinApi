#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CCompanyLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	CCompanyLogo();
	~CCompanyLogo();

	// delete Function
	CCompanyLogo(const CCompanyLogo& _Other) = delete;
	CCompanyLogo(CCompanyLogo&& _Other) noexcept = delete;
	CCompanyLogo& operator=(const CCompanyLogo& _Other) = delete;
	CCompanyLogo& operator=(CCompanyLogo&& _Other) noexcept = delete;

protected:
	virtual void Start() override;

private:

};

