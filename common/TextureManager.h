#ifndef CTEXTURE_MANAGER_H_
#define CTEXTURE_MANAGER_H_

#include <map>
class CTexture;

class CTextureManager
{
private:
	static std::map<std::string, CTexture*> m_Textures;
public:
	static void Initialize();
	static void Finalize();
	static CTexture* LoadTexture(const char* filename);
};

#endif // !CTEXTURE_MANAGER_H_
