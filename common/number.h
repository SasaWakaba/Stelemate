#ifndef NUMBER_H_
#define NUMBER_H_

#define NUMBER_WIDTH (64)
#define NUMBER_HEIGHT (64)

class CPolygon;

class CNumber
{
private:
	CPolygon* m_Polygon;
public:
	void Initialize(void);
	void Finalize(void);

	// 0 <= n <= 9
	void Draw(float x, float y, float w, float h, int n);
};


#endif