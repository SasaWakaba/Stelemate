#ifndef PREPARATION_UI_H_
#define PREPARATION_UI_H_

class CDrawText;

class CPreparationUI : public CGameObject
{
private:

	enum SelectPre
	{
		Start = 0,
		Arrangement,
		Employment,
		Strengthen,
	};

	static const int maxTex = 4;
	CPolygon*	m_Texture[maxTex];
	CDrawText*	m_Text[2];

	SelectPre  m_Cursol;

	int frame;

public:
	CPreparationUI();
	~CPreparationUI();

	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};


#endif // !PREPARATION_UI_H_
