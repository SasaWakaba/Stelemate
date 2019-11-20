#ifndef CDRAW_TEXT_H_
#define CDRAW_TEXT_H_

class CTexture;

class CDrawText
{
private:
	ID3D11Texture2D* tex2D;
	CTexture*	m_Texture;
	ID3D11Buffer* m_VertexBuffer;
	void Draw1text(int dx, int dy, int h, int w, TCHAR* c, VertexColor_4 textcolor);
public:
	static void Initialize();
	static void Finalize();

	void Set(int fontsize);
	void UnSet();

	void DrawEng(int dx, int dy, int h, int w, std::string c, VertexColor_4 textcolor);
	void DrawJpn(int dx, int dy, int h, int w, std::string c, VertexColor_4 textcolor);



};

#endif // CDRAW_TEXT_H_
