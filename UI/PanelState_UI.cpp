#include "../common/main.h"
#include "../common/Game_Object.h"
#include "../common/texture.h"
#include "../common/polygon.h"

#include "PanelState_UI.h"

#define STATE_WIDTH (240.0f)
#define STATE_HEIGHT (80.0f)

#define DATAWINDOW_WIDTH (240.0f)
#define DATAWINDOW_HEIGHT (120.0f)


unsigned short CPanelState::m_PanelPattarn;

void CPanelState::Initialize()
{
	m_Polygon[0] = new CPolygon();
	m_Polygon[0]->Initialize();
	m_Polygon[0]->Load("asset/texture/Map_Menu.png");

	m_Polygon[1] = new CPolygon();
	m_Polygon[1]->Initialize();
	m_Polygon[1]->Load("asset/texture/dataWindow.png");

	m_Polygon[2] = new CPolygon();
	m_Polygon[2]->Initialize();
	m_Polygon[2]->Load("asset/texture/UI_grass.png");

	m_Polygon[3] = new CPolygon();
	m_Polygon[3]->Initialize();
	m_Polygon[3]->Load("asset/texture/UI_forest.png");

	m_Polygon[4] = new CPolygon();
	m_Polygon[4]->Initialize();
	m_Polygon[4]->Load("asset/texture/data_grass.png");

	m_Polygon[5] = new CPolygon();
	m_Polygon[5]->Initialize();
	m_Polygon[5]->Load("asset/texture/data_forest.png");
	

	m_PanelPattarn = 0;
}

void CPanelState::Finalize()
{
	for (int i = 0; i < PANELSTATE_TEX_NUM; i++)
	{
		m_Polygon[i]->Finalize();
		delete m_Polygon[i];
	}
}

void CPanelState::Update()
{

}

void CPanelState::Draw()
{
	VertexColor_4 color{
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f),
		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
	};

	m_Polygon[0]->Draw(STATE_WIDTH / 2, STATE_HEIGHT / 3 * 2, 0.0f, 0.0f, STATE_WIDTH, STATE_HEIGHT, STATE_WIDTH, STATE_HEIGHT, color);
	m_Polygon[1]->Draw(DATAWINDOW_WIDTH / 4 * 3, 150.0f, 0.0f, 0.0f, DATAWINDOW_WIDTH, DATAWINDOW_HEIGHT, DATAWINDOW_WIDTH, DATAWINDOW_HEIGHT, color);

	switch (m_PanelPattarn)
	{
	case 1:
		m_Polygon[2]->Draw(STATE_WIDTH / 2, STATE_HEIGHT / 3 * 2, 0.0f, 0.0f, STATE_WIDTH, STATE_HEIGHT, STATE_WIDTH, STATE_HEIGHT, color);
		m_Polygon[4]->Draw(DATAWINDOW_WIDTH / 4 * 3, 150.0f, 0.0f, 0.0f, DATAWINDOW_WIDTH, DATAWINDOW_HEIGHT, DATAWINDOW_WIDTH, DATAWINDOW_HEIGHT, color);
		break;
	case 2:
		m_Polygon[3]->Draw(STATE_WIDTH / 2, STATE_HEIGHT / 3 * 2, 0.0f, 0.0f, STATE_WIDTH, STATE_HEIGHT, STATE_WIDTH, STATE_HEIGHT, color);
		m_Polygon[5]->Draw(DATAWINDOW_WIDTH / 4 * 3, 150.0f, 0.0f, 0.0f, DATAWINDOW_WIDTH, DATAWINDOW_HEIGHT, DATAWINDOW_WIDTH, DATAWINDOW_HEIGHT, color);
		break;
	}
	
}