#pragma once
#include <vector>

#include "GameEngineObject.h"
#include "GameEngineRender.h"

// Ό³Έν :
class GameEngineActor;
class NumberRenderObject : public GameEngineObject
{
public:
	// constrcuter destructer
	NumberRenderObject();
	~NumberRenderObject();

	// delete Function
	NumberRenderObject(const NumberRenderObject& _Other) = delete;
	NumberRenderObject(NumberRenderObject&& _Other) noexcept = delete;
	NumberRenderObject& operator=(const NumberRenderObject& _Other) = delete;
	NumberRenderObject& operator=(NumberRenderObject&& _Other) noexcept = delete;

	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor);

	void SetValue(int _Value);

	inline int GetValue()
	{
		return Value;
	}

protected:

private:
	int Order;
	float4 NumberScale;
	float4 Pos;
	int Value = 0;

	int TransColor = RGB(255, 0, 255);

	std::string_view ImageName;

	std::vector<GameEngineRender*> NumberRenders;

};

