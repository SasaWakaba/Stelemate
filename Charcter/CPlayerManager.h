#ifndef CPLAYER_MANAGER_H_
#define CPLAYER_MANAGER_H_

typedef struct
{
	CCharcterBase*	m_Character;
	int				m_Exp;
	int				m_NextExp;
	int				PosX;
	int				PosZ;
}PlayerData;

#define EXP_BONUS_1 (1.1f)
#define EXP_BONUS_2 (1.3f)
#define EXP_BONUS_3 (1.6f)
#define EXP_BONUS_4 (1.9f)
#define EXP_BONUS_NOT (0.0f)

#define LEVELUP_ENEMY_NUM (2)
#define FIRST_LEVELUP (100)
#define NEXT_EXP (1.1f)

#define MAX_LEVEL (40)

class CPlayerManager
{
private:
	std::map<std::string, PlayerData*> m_PlayerTeam;
public:
	void CharacterAdd(const char* characterName, PlayerData* menber);
	int CharacterGetExperience(const char* characterName, int EnemyLevel);

	std::map<std::string, PlayerData*> GetMenberData();
};

#endif // !CPLAYER_MANAGER_H_
