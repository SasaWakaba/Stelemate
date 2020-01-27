#ifndef CPREPARATION_H_
#define CPREPARATION_H_

class CAudioClip;

class CPreparation : public CScene
{
private:
	static bool bChange;
	CAudioClip* m_BGM;
public:

	void Init();
	void UnInit();
	void Update();

	static void Change();
};

#endif // !CPREPARATION_H_
