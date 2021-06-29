#pragma once
#include <string>
#include <unordered_map>

// Singleton
class ImageMng
{
public:
	static void Create();
	static void Destroy();
	static ImageMng& Instance();

	bool AddImage(const std::string& fileName, const std::string& key);
	void DeleteImage(const std::string& key);
	int GetID(const std::string& key);
	
private:
	ImageMng();
	~ImageMng();
	
private:
	// Don't allow copy and move semantics
	ImageMng(const ImageMng&);
	ImageMng(ImageMng&&) noexcept;
	void operator = (const ImageMng&);
	void operator = (ImageMng&&) noexcept;
	//

private:
	std::unordered_map<std::string, int> m_handleMap;

	static ImageMng* m_instance;
};

