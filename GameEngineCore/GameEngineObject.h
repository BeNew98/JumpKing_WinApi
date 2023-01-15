#pragma once

// Ό³Έν :
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	bool IsUpdate()
	{
		return nullptr != Parent ? (ObjectUpdate && false == ObjectDeath && Parent->IsUpdate()) : (ObjectUpdate && false == ObjectDeath);
	}

	bool IsDeath()
	{
		return nullptr != Parent ? (true == ObjectDeath && Parent->IsDeath()) : (true == ObjectDeath);
	}

	void On()
	{
		ObjectUpdate = true;
	}
	void Off()
	{
		ObjectUpdate = false;
	}

	void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}


	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

protected:

private:
	GameEngineObject* Parent = nullptr;
	bool ObjectDeath = false;
	bool ObjectUpdate = true;

};

