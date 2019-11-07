#ifndef CSTAGE_PANEL_H_
#define CSTAGE_PANEL_H_

#include "../common/main.h"

class CCube;
class CTexture;
class CModelLoader;

class CStagePanel
{
protected:
	XMFLOAT3					m_Position;
	unsigned short				m_PanelPattarn;
	CCube*						cube;
	CTexture*					m_Texture;

	CModelLoader*				m_Model = nullptr;
public:
	CStagePanel(unsigned short panelpattarn, XMFLOAT3 position) :m_Position(position) { m_PanelPattarn = panelpattarn; }
	virtual ~CStagePanel(){}

	virtual void Initialize();
	virtual void Finalize();
	virtual void Draw();

	void SetPosition(XMFLOAT3 position) { m_Position = position; }
};



#endif // !CSTAGE_PANEL_H_
