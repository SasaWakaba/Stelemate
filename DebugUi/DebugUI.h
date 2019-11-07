#ifndef DEBUGUI_H_
#define DEBUGUI_H_


typedef struct
{
	bool bEnable;

	bool bText;
	char* Text;
	float* num;
}DEBUG_INFO;

class CDebugUI
{
private:

public:
	static void Initialize();
	static void Finalize();
	static void Update();
	static void Draw();
};



#endif // !DEBUGUI_H_
