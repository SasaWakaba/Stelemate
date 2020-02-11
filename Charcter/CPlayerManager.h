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

#define GLOWUP_BASE (8)
#define GLOWUP_1 ((int)(GLOWUP_BASE * 1.3))
#define GLOWUP_2 ((int)(GLOWUP_1 * 1.3))
#define GLOWUP_3 ((int)(GLOWUP_2 * 1.3))
#define GLOWUP_4 ((int)(GLOWUP_3 * 1.3))
#define GLOWUP_5 ((int)(GLOWUP_4 * 1.3))
#define GLOWUP_6 ((int)(GLOWUP_5 * 1.3))
#define GLOWUP_7 ((int)(GLOWUP_6 * 1.3))
#define GLOWUP_8 ((int)(GLOWUP_7 * 1.3))
#define GLOWUP_9 ((int)(GLOWUP_8 * 1.3))
#define GLOWUP_10 ((int)(GLOWUP_9 * 1.3))
#define GLOWUP_11 ((int)(GLOWUP_10 * 1.3))
#define GLOWUP_12 ((int)(GLOWUP_11 * 1.3))


class CPlayerManager
{
private:
	std::map<std::string, PlayerData*> m_PlayerTeam;
	std::map < std::string, STATUS*>   m_PlayerGlaw;

	int StatusGlowUp(int glowNum, int glowNow, int level);
public:
	STATUS* CharacterAdd(const char* characterName, PlayerData* menber);
	int CharacterGetExperience(const char* characterName, int EnemyLevel);

	std::map<std::string, PlayerData*> GetMenberData();
};

#endif // !CPLAYER_MANAGER_H_
