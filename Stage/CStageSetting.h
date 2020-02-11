#ifndef CSTAGE_SETTING_H_
#define CSTAGE_SETTING_H_

class CStagePanel;
class CSubCamera;
class C3DPolygon;
class CTexture;
class CBillboard;

class CStageSetting
{
private:
	StageInfo* pStage;

	CSubCamera* camera;

	CStagePanel* m_StagePanel[2];

	C3DPolygon* m_3DPolygon;

	CTexture* m_Texture[2];

	Vector2_3D m_CursorLocation;
	Vector2_3D selectPos;

	CBillboard*	m_Yazirushi;

	bool edit;
	bool select;
	int frame;
public:
	void Initialize(int stageNum);
	void Finalize();
	void Update();
	void Draw();

	StageInfo* GetStageData(int stageNum);
	StageEnemy GetStageEnemy(int stageNum);
	void SetStageData(StageInfo* stage);

	void Edit();
	bool GetEdit();
	StageInfo* GetSettingStage();
};

#endif // !CSTAGE_SETTING_H_
