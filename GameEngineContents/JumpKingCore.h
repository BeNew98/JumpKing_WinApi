#pragma once
#include <GameEngineCore/GameEngineCore.h>

// Ό³Έν : 
class JumpKingCore :public GameEngineCore
{
public:
	// delete Function
	JumpKingCore(const JumpKingCore& _Other) = delete;
	JumpKingCore(JumpKingCore&& _Other) noexcept = delete;
	JumpKingCore& operator=(const JumpKingCore& _Other) = delete;
	JumpKingCore& operator=(JumpKingCore&& _Other) noexcept = delete;

	static JumpKingCore* GetInst()
	{
		static JumpKingCore Core;
		return &Core;
	}

protected:
	void Start() override;
	void Update() override;
	void End() override;

private:
	// constrcuter destructer
	JumpKingCore();
	~JumpKingCore();

};

