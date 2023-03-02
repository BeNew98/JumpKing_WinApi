#pragma once

// Ό³Έν :
class CBabe
{
public:
	// constrcuter destructer
	CBabe();
	~CBabe();

	// delete Function
	CBabe(const CBabe& _Other) = delete;
	CBabe(CBabe&& _Other) noexcept = delete;
	CBabe& operator=(const CBabe& _Other) = delete;
	CBabe& operator=(CBabe&& _Other) noexcept = delete;

protected:

private:

};

