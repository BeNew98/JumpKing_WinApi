#include <Windows.h>
#include <GameEngineContents/JumpKingCore.h>
#include <crtdbg.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow){
	//_CrtSetBreakAlloc(312);
	JumpKingCore::GetInst()->CoreStart(hInstance);
	return 1;
}