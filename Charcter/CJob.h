#ifndef CJOB_H_
#define CJOB_H_



class CSwordsman :public CCharcterBase
{
private:
	XMFLOAT3 m_LocationOld;
	CModelAnimation* m_Model[2];
	int frame;
public:
	CSwordsman():CCharcterBase(Swordman){}
	~CSwordsman(){}
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};

class CLancer :public CCharcterBase
{
private:
	XMFLOAT3 m_LocationOld;
	CModelAnimation* m_Model[2];
	int frame;
public:
	CLancer() :CCharcterBase(Lancer) {}
	~CLancer() {}
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

class CArcher :public CCharcterBase
{
private:
	XMFLOAT3 m_LocationOld;
	CModelAnimation* m_Model[2];
	int frame;
public:
	CArcher() :CCharcterBase(Archer) {}
	~CArcher() {}
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

class CSorcerer :public CCharcterBase
{
private:
	XMFLOAT3 m_LocationOld;
	CModelAnimation* m_Model[2];
public:
	CSorcerer() :CCharcterBase(Sorcerer) {}
	~CSorcerer() {}
	void Initialize(){}
	void Finalize(){}
	void Update(){}
	void Draw(){}
};

class CHealer :public CCharcterBase
{
private:
	XMFLOAT3 m_LocationOld;
	CModelAnimation* m_Model[2];
public:
	CHealer() :CCharcterBase(Healer) {}
	~CHealer() {}
	void Initialize() {}
	void Finalize() {}
	void Update() {}
	void Draw() {}
};

#endif // !CJOB_H_
