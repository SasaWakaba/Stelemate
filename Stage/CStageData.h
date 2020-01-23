#ifndef CSTAGE_DATA_H_
#define CSTAGE_DATA_H_


typedef struct
{
	unsigned short PanelPattarn;
	CCharcterBase* Charcter;
	bool bChar;
}PanelState;

typedef struct
{
	PanelState* stage;
	int StageXnum;
	int StageZnum;
}StageInfo;

class CStageData
{
private:
	static void Load(const char* filename);
public:
	static std::map<std::string, StageInfo*> m_StageData;

	static void Initialize();
	static void Finalize();
};

#endif // !CSTAGE_DATA_H_


