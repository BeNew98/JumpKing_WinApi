#pragma once

// ���� :
class CEndLevel
{
public:
	// constrcuter destructer
	CEndLevel();
	~CEndLevel();

	// delete Function
	CEndLevel(const CEndLevel& _Other) = delete;
	CEndLevel(CEndLevel&& _Other) noexcept = delete;
	CEndLevel& operator=(const CEndLevel& _Other) = delete;
	CEndLevel& operator=(CEndLevel&& _Other) noexcept = delete;

protected:

private:

};

