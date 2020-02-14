
#include "../../common/main.h"
#include "../../common/Scene.h"
#include "../../common/manager.h"
#include "../../GameSystem/CEnemyAI.h"
#include "../../GameSystem/WorldManager.h"



#include "../../common/main.h"
#include "../../Stage/CStage.h"
#include <vector>


#include "../../Charcter/CCharcterBase.h"
#include "../../GameSystem/CSystemBattle.h"
#include "../../GameSystem/CAttackSearch.h"
#include "../../GameSystem/CMoveSearch.h"

#include "EnemyPttern.h"
#include "EnemyPatternEnd.h"


void CEnemyPatternEnd::Update(CEnemyAI* pEnemy, Vector2_3D* cursol)
{
	pEnemy->GetMoveEnemy()->SetTurnMove(true);
	pEnemy->SetMoveEnemy(nullptr);
	pEnemy->SetMove(wait);
}