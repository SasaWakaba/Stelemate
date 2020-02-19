#ifndef CMODEL_MANAGER_H_
#define CMODEL_MANAGER_H_

#include <map>
class CModelAnimation;

class CModelManager
{
private:
	static std::map<std::string, CModelAnimation*> m_Models;
	static std::map<std::string, CModelAnimation*> m_ModelAnims;
public:
	static void Initialize();
	static void Finalize();
	static CModelAnimation* LoadModel(const char* filename);

	static void LoadAnim(CModelAnimation* model, const char* filename);
};

#endif // !CTEXTURE_MANAGER_H_
