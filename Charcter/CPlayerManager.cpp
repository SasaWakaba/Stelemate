#include "../common/main.h"

#include "../GameSystem/WorldManager.h"
#include <string>
#include <map>
#include <time.h>
#include <random>

#include "CPlayerManager.h"

std::map<std::string, PlayerData*> CPlayerManager::GetMenberData()
{
	return m_PlayerTeam;
}

int CPlayerManager::StatusGlowUp(int glowNum, int glowNow, int level)
{
	int glow;
	switch (glowNum)
	{
	case 0:
		glow = GLOWUP_BASE;
		break;
	case 1:
		glow = GLOWUP_1;
		break;
	case 2:
		glow = GLOWUP_2;
		break;
	case 3:
		glow = GLOWUP_3;
		break;
	case 4:
		glow = GLOWUP_4;
		break;
	case 5:
		glow = GLOWUP_5;
		break;
	case 6:
		glow = GLOWUP_6;
		break;
	case 7:
		glow = GLOWUP_7;
		break;
	case 8:
		glow = GLOWUP_8;
		break;
	case 9:
		glow = GLOWUP_9;
		break;
	case 10:
		glow = GLOWUP_10;
		break;
	case 11:
		glow = GLOWUP_11;
		break;
	case 12:
		glow = GLOWUP_12;
		break;
	}


	if (glowNow > glow)
	{
		if (MAX_LEVEL - level > glow)
		{
			if (rand() % 100 + 1 < 25)
			{
				glowNow++;
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			glowNow++;
			return 1;
		}
	}
	else
	{
		return 0;
	}
}

STATUS* CPlayerManager::CharacterAdd(const char* characterName, PlayerData* menber)
{
	srand((unsigned int)time(NULL));
	if (m_PlayerTeam[characterName] == nullptr)
	{
		m_PlayerTeam[characterName] = menber;
		m_PlayerGlaw[characterName] = new STATUS[2];
		STATUS* glow = m_PlayerGlaw[characterName];
		glow[0].Attack = rand() % 13;
		glow[0].Defense = rand() % 13;
		glow[0].Dexterity = rand() % 13;
		glow[0].HP = rand() % 13;
		glow[0].Luck = rand() % 13;
		glow[0].Speed = rand() % 13;
		glow[0].MagicDefense = rand() % 13;

		glow[1].Attack =		0;
		glow[1].Defense =		0;
		glow[1].Dexterity =		0;
		glow[1].HP =			0;
		glow[1].Luck =			0;
		glow[1].Speed =			0;
		glow[1].MagicDefense =	0;
		return &glow[0];
	}
	else
	{
		int num = 0;
		while(1)
		{
			std::string neme = characterName + std::to_string(num);
			if (m_PlayerTeam[neme] == nullptr)
			{
				m_PlayerTeam[neme] = menber;
				m_PlayerTeam[neme]->m_Character->SetName(neme);
				m_PlayerGlaw[neme] = new STATUS[2];
				STATUS* glow = m_PlayerGlaw[neme];
				glow[0].Attack = rand() % 13;
				glow[0].Defense = rand() % 13;
				glow[0].Dexterity = rand() % 13;
				glow[0].HP = rand() % 13;
				glow[0].Luck = rand() % 13;
				glow[0].Speed = rand() % 13;
				glow[0].MagicDefense = rand() % 13;

				glow[1].Attack = 0;
				glow[1].Defense = 0;
				glow[1].Dexterity = 0;
				glow[1].HP = 0;
				glow[1].Luck = 0;
				glow[1].Speed = 0;
				glow[1].MagicDefense = 0;
				return &glow[0];
				break;
			}
			else
			{
				num++;
			}
		}
	}
}

int CPlayerManager::CharacterGetExperience(const char* characterName, int EnemyLevel)
{
	if (m_PlayerTeam[characterName]->m_Character->Level != MAX_LEVEL)
	{
		int EXP = 0;
		int difference = EnemyLevel - m_PlayerTeam[characterName]->m_Character->Level;

		if (difference >= 0)
		{
			switch (difference)
			{
			case 0:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM;
				break;
			case 1:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_1);
				break;
			case 2:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_2);
				break;
			case 3:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_3);
				break;
			case 4:
			default:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_4);
				break;
			}
		}
		else
		{
			switch (difference)
			{
			case -1:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * -EXP_BONUS_1);
				break;
			case -2:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * -EXP_BONUS_2);
				break;
			case -3:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * -EXP_BONUS_3);
				break;
			case -4:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * -EXP_BONUS_4);
				break;
			case -5:
			default:
				EXP = (int)(m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_NOT);
				break;
			}
		}
		m_PlayerTeam[characterName]->m_Exp += EXP;

		if (m_PlayerTeam[characterName]->m_Exp - m_PlayerTeam[characterName]->m_NextExp >= 0)
		{
			srand((unsigned int)time(NULL));
			m_PlayerTeam[characterName]->m_Character->Level++;
			m_PlayerTeam[characterName]->m_Exp = m_PlayerTeam[characterName]->m_Exp - m_PlayerTeam[characterName]->m_NextExp;
			m_PlayerTeam[characterName]->m_NextExp = (int)(m_PlayerTeam[characterName]->m_NextExp * NEXT_EXP);

			STATUS* PL = m_PlayerTeam[characterName]->m_Character->GetStatus();
			STATUS* glow = m_PlayerGlaw[characterName];
			PL->Attack +=		StatusGlowUp(glow[0].Attack, glow[1].Attack, m_PlayerTeam[characterName]->m_Character->Level);
			PL->Defense +=		StatusGlowUp(glow[0].Defense, glow[1].Defense, m_PlayerTeam[characterName]->m_Character->Level);
			PL->Dexterity +=	StatusGlowUp(glow[0].Dexterity, glow[1].Dexterity, m_PlayerTeam[characterName]->m_Character->Level);
			PL->HP +=			StatusGlowUp(glow[0].HP, glow[1].HP, m_PlayerTeam[characterName]->m_Character->Level);
			PL->Luck +=			StatusGlowUp(glow[0].Luck, glow[1].Luck, m_PlayerTeam[characterName]->m_Character->Level);
			PL->MagicDefense += StatusGlowUp(glow[0].MagicDefense, glow[1].MagicDefense, m_PlayerTeam[characterName]->m_Character->Level);
			PL->Speed +=		StatusGlowUp(glow[0].Speed, glow[1].Speed, m_PlayerTeam[characterName]->m_Character->Level);

		}

		return EXP;
	}
	else
	{
		return 0;
	}
}

