#include "../common/main.h"

#include "../GameSystem/WorldManager.h"
#include <string>
#include <map>

#include "CPlayerManager.h"

std::map<std::string, PlayerData*> CPlayerManager::GetMenberData()
{
	return m_PlayerTeam;
}

void CPlayerManager::CharacterAdd(const char* characterName, PlayerData* menber)
{
	if (m_PlayerTeam[characterName] == nullptr)
	{
		m_PlayerTeam[characterName] = menber;
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
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_1;
				break;
			case 2:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_2;
				break;
			case 3:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_3;
				break;
			case 4:
			default:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_4;
				break;
			}
		}
		else
		{
			switch (difference)
			{
			case -1:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * -EXP_BONUS_1;
				break;
			case -2:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * -EXP_BONUS_2;
				break;
			case -3:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * -EXP_BONUS_3;
				break;
			case -4:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * -EXP_BONUS_4;
				break;
			case -5:
			default:
				EXP = m_PlayerTeam[characterName]->m_NextExp / LEVELUP_ENEMY_NUM * EXP_BONUS_NOT;
				break;
			}
		}
		m_PlayerTeam[characterName]->m_Exp += EXP;

		if (m_PlayerTeam[characterName]->m_Exp - m_PlayerTeam[characterName]->m_NextExp >= 0)
		{
			m_PlayerTeam[characterName]->m_Character->Level++;
			m_PlayerTeam[characterName]->m_Exp = m_PlayerTeam[characterName]->m_Exp - m_PlayerTeam[characterName]->m_NextExp;
			m_PlayerTeam[characterName]->m_NextExp = m_PlayerTeam[characterName]->m_NextExp * NEXT_EXP;
		}

		return EXP;
	}
	else
	{
		return 0;
	}
}

