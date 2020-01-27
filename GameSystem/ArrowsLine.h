#ifndef CARROWS_LINE_H_
#define CARROWS_LINE_H_


class CTexture;
class C3DPolygon;


class CArrowsLine
{
private:
	CTexture* m_Arrows;
	CTexture* m_Line;
	CTexture* m_Curve;

	C3DPolygon* m_Polygon;

	std::vector<Vector2_3D> m_ArrowsLine;

public:
	void Add(Vector2_3D pos);

	void Delete() { m_ArrowsLine.pop_back(); }

	void Reset() { m_ArrowsLine.clear(); }

	void Initialize();
	void Finalize();
	void Draw(int x, int z);
};


#endif // !CARROWS_LINE_H_
