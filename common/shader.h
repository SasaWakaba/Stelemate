#pragma once

class CShader {
#define MAX_SHADERS (8)
private:
	static ID3D11PixelShader* pixelList[MAX_SHADERS];
	static ID3D11GeometryShader* geoList[MAX_SHADERS];
	static char geoPath[MAX_SHADERS][32];
	static char pixelPath[MAX_SHADERS][32];
	static char vertexPath[MAX_SHADERS][32];
	static ID3D11VertexShader* vertexList[MAX_SHADERS];
	static ID3D11InputLayout* indexList[MAX_SHADERS];
public:
	static void LoadPixelShader(const char* fchar, ID3D11PixelShader** tar);
	static void LoadGeometryShader(const char* fchar, ID3D11GeometryShader** tar);
	static void LoadVertexShader(const char* fchar, ID3D11VertexShader** tar, ID3D11InputLayout** tarinp, D3D11_INPUT_ELEMENT_DESC desc[], UINT numElements);
};

