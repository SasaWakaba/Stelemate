#ifndef CSTAGE_DATA_H_
#define CSTAGE_DATA_H_

#include <map>

class CCharcterBase;

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

typedef struct
{
	int EnemyNum;
	int SwordmanNum;
	int ArcherNum;
	int SorcererNum;
	int HealerNum;
	int LancerNum;
}StageEnemy;

class CStageData
{
private:
	static void Load(const char* filename);
public:
	static std::map<std::string, StageInfo*> m_StageData;
	static std::map<std::string, StageEnemy> m_StageEnemy;

	static void Initialize();
	static void Finalize();
};

#endif // !CSTAGE_DATA_H_


