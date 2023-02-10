#include <Windows.h>
#include <GameEngineContents/JumpKingCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	JumpKingCore::GetInst()->CoreStart(hInstance);
	return 1;
}