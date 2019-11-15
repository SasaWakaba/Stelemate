#ifndef CDRAW_TEXT_H_
#define CDRAW_TEXT_H_

class CTexture;

class CDrawText
{
public:
	static void Initialize();
	static void Finalize();
	
	static void Draw(int x, int y, int h, std::string text);
	static CTexture* Create(TCHAR* c, int fontsize);


};

#endif // CDRAW_TEXT_H_
