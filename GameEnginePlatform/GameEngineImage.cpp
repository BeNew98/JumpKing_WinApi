#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>


GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
}


bool GameEngineImage::ImageCreate(HDC _Hdc)
{
	if (nullptr == _Hdc)
	{
		MsgAssert("이미지 생성에 실패했습니다 nullptr 인 HDC를 넣어줬습니다.");
		return false;
	}

	ImageDC = _Hdc;
	ImageScaleCheck();
	return true;
}

bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str());
}

bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 로드에 실패했습니다.");
		return false;
	}

	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 HDC 생성에 실패했습니다.");
		return false;
	}

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ImageScaleCheck();

	return false;
}

void GameEngineImage::ImageScaleCheck()
{
	GetObject(BitMap, sizeof(BITMAP), &Info);
}

void GameEngineImage::BitCopy(GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale)
{
	BitBlt(ImageDC
		, _Pos.ix()
		, _Pos.iy()
		, _Scale.ix()
		, _Scale.iy()
		, _OtherImage->GetImageDC()
		, 0, 0
		, SRCCOPY
	);
}