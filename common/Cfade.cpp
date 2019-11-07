#include "main.h"
#include "polygon.h"

#include "CFade.h"


CPolygon* CFade::m_Polygon[2];
bool CFade::bFadeStart;
bool CFade::bFadeEnd;
float CFade::m_pos[2];
int CFade::frame;

bool CFade::startfin;

void CFade::Initialize()
{
	m_Polygon[0] = new CPolygon();
	m_Polygon[0]->Initialize();
	m_Polygon[0]->Load("asset/texture/fade.png");

	m_pos[0] = -SCREEN_WIDTH;
	m_pos[1] = 0.0f;
	frame = 0;
	bFadeStart = false;
	bFadeEnd = false;

	startfin = false;
}

void CFade::Finalize()
{
	m_Polygon[0]->Finalize();
	delete m_Polygon[0];

	//m_Polygon[1]->Finalize();
	//delete m_Polygon[1];
}

void CFade::Update()
{
	if (bFadeStart)
	{
		if (m_pos[0] < SCREEN_WIDTH / 2)
		{
			m_pos[0] += (SCREEN_WIDTH + SCREEN_WIDTH / 2) / 30.0f;
		}
		else
		{
			startfin = true;
		}
	}

	if (bFadeEnd)
	{
		if (m_pos[0] < SCREEN_WIDTH * 2)
		{
			m_pos[0] += (SCREEN_WIDTH + SCREEN_WIDTH / 2) / 30.0f;
		}
		else
		{
			bFadeEnd = false;
		}
	}
}

void CFade::Draw()
{
	if (bFadeStart || bFadeEnd)
	{
		m_Polygon[0]->Draw(m_pos[0], SCREEN_HEIGHT / 2, 0.0f, 0.0f, SCREEN_WIDTH * 2, SCREEN_HEIGHT, SCREEN_WIDTH * 2, SCREEN_HEIGHT);
	}
}