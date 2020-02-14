#ifndef CRESULT_UI_H_
#define CRESULT_UI_H_

#define RESULT_UI_NUM (12)

class CPolygon;
class CDrawText;
class CNumber;

class CResultUI :public CGameObject
{
private:
	enum
	{
		BackSet = 0,
		Heading,
		Number,
		select,
		end,
	};

	CPolygon* m_Texture[RESULT_UI_NUM];
	CDrawText* m_Text[2];

	UI_POS ResultTitlePos;
	UI_POS UIbasePos;
	UI_POS SelectPos[2];

	CNumber* number;

	float textAlpha[2];
	float NumScale[4];
	int Phase;
	int StartFrame;
	int frame;
	int selectEnd;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !CRESULT_UI_H_
