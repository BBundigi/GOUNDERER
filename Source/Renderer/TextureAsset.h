#pragma once
#include <memory>
#include <string>
#include <assert.h>

typedef unsigned int UINT;
struct Color24
{
	char R;
	char G;
	char B;
};

struct TextureDataType
{
	Color24* ColorData;
	UINT DataSize;
	UINT TexHeight;
	UINT TexWidth;
};

class TextureAsset final
{
private:
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};
public:
	explicit TextureAsset() noexcept = default;
	virtual ~TextureAsset() noexcept = default;
	// Load Targa file
	void Load(const std::string& InPath);
private:
	std::unique_ptr<Color24[]> mTextureData;
	UINT mDataSize;
	UINT mTextureHeight;
	UINT mTextureWidth;
public:
	inline Color24* GetTextureData() const { return mTextureData.get(); }
	inline UINT GetTextureDataSize() const { return mDataSize; }
	inline UINT GetTextureHeight() const { return mTextureHeight; }
	inline UINT GetTextureWidth() const { return mTextureWidth; }
};
