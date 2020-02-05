#ifndef PREPARATION_UI_H_
#define PREPARATION_UI_H_

class CDrawText;
class CNumber;
class CEmploymentUI;

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

	static const int maxTex = 8;
	CPolygon*	m_Texture[maxTex];
	CDrawText*	m_Text[2];
	CNumber*	m_Number;
	CEmploymentUI* m_Emp;

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
