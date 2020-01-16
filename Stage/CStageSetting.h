#ifndef CSTAGE_SETTING_H_
#define CSTAGE_SETTING_H_

class CStagePanel;


class CStageSetting
{
private:
	CStagePanel* pStage;
	int StageXnum;
	int StageZnum;
public:
	void Initialize();
	void Finalize();

	CStagePanel* GetStageData(int stageNum);
	void SetStageData(CStagePanel* stage);
};

#endif // !CSTAGE_SETTING_H_
