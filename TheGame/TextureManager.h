#pragma once
class TextureManager
{
public:
	static TextureManager* getInstance();
	virtual ~TextureManager();

	bool LoadTexture(
		std::string nameID,
		std::string filepath,
		GLenum magFilter,
		GLenum minFilter
	);

	bool UnloadTexture(std::string texID);
	bool BindTexture(std::string texID);
	void UnloadAllTextures();

protected:
	TextureManager();

	static TextureManager* instance;
	std::map<std::string, GLuint> textures;
};

