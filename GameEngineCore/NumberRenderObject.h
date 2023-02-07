#pragma once

// Ό³Έν :
class NumberRenderObject
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

protected:

private:

};

