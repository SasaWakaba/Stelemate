#ifndef TITLE_BACKGROUND_H_
#define TITLE_BACKGROUND_H_

class CPolygon;

class CTitleBackground : public CGameObject
{
private:
	CPolygon* texture[5];
	int frame;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !TITLE_BACKGROUND_H_
