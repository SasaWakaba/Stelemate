#ifndef CDRAW_TEXT_H_
#define CDRAW_TEXT_H_

class CDrawText
{
public:
	static void Initialize();
	static void Finalize();
	
	static void Draw(int x, int y, int h, std::string text);


};

#endif // CDRAW_TEXT_H_
