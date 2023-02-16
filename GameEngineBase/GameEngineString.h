#pragma once
#include <string>
#include <string_view>

// 설명 :
//멀티 바이트(ansi) =>1~2
//유니코드 =>2
class GameEngineString
{
public:
	static std::string ToUpper(const std::string_view& _Str);

	static std::string ToString(int Value);

	static std::wstring AnsiToUniCode(const std::string_view& _Text);
	static std::string UniCodeToAnsi(const std::wstring_view& _Text);

	static std::string UniCodeToUTF8(const std::wstring_view& _Text);
	static std::string AnsiToUTF8(const std::string_view& _Text);

protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};

