#ifndef CCARACTER_DATA_H_
#define CCARACTER_DATA_H_
#include <map>
#define MAX_STATUS (7)

class CCharacterData
{
public:
	static std::map<std::string, STATUS> m_CharData;

	static void Initialize();
	static void Finalize();
};

#endif // !CCARACTER_DATA_H_
