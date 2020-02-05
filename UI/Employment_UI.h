#ifndef CEMPLOYMENT_UI_H_
#define CEMPLOYMENT_UI_H_


class CPolygon;


class CEmploymentUI
{
private:
	enum
	{
		notDraw = 0,
		moveSelect,
		Select,
		backSelect,
		moveEmp,
		Emp,
		backEmp,
		end
	};

	static const int maxTex = 4;
	CPolygon*	m_Texture[maxTex];
	CPolygon*	m_Icon[5];
	CDrawText*	m_Text[3];
	CNumber*	m_Number;
	PlayerData* m_AddData;

	float m_TexPos[maxTex];

	int Frame;
	int StartFrame;

	int Phase;
	int selectJob;
public:
	CEmploymentUI();
	~CEmploymentUI();

	void Initialize();
	void Finalize();
	void Update(int frame);
	void Draw();

	void StartEmp();

	int GetPhase() { return Phase; }
};

#endif // !CEMPLOYMENT_UI_H_