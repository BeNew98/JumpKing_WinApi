#pragma once

// Ό³Έν :
class CWind
{
public:
	// constrcuter destructer
	CWind();
	~CWind();

	// delete Function
	CWind(const CWind& _Other) = delete;
	CWind(CWind&& _Other) noexcept = delete;
	CWind& operator=(const CWind& _Other) = delete;
	CWind& operator=(CWind&& _Other) noexcept = delete;

protected:

private:

};

