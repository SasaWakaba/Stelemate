#include "main.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include <io.h>
ID3D11PixelShader* CShader::pixelList[MAX_SHADERS];
ID3D11VertexShader* CShader::vertexList[MAX_SHADERS];
ID3D11InputLayout* CShader::indexList[MAX_SHADERS];
ID3D11GeometryShader* CShader::geoList[MAX_SHADERS];
char CShader::pixelPath[MAX_SHADERS][32];
char CShader::vertexPath[MAX_SHADERS][32];
char CShader::geoPath[MAX_SHADERS][32];
void CShader::LoadPixelShader(const char* filepath, ID3D11PixelShader** tar)
{
	int count = 0;
	for (count = 0; count < MAX_SHADERS; count++) {
		if (strcmp(pixelPath[count], filepath) == 0) {
			*tar = pixelList[count];
			return;
		}
	}
	FILE* file;
	long int fsize;
	ID3D11PixelShader* pshader;
	file = fopen(filepath, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	CRenderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &pshader);
	delete[] buffer;

	*tar = pshader;

	for (count = 0; count < MAX_SHADERS; count++) {
		if (pixelPath[count][0] == '\0') {
			pixelList[count] = pshader;
			strcpy(pixelPath[count], filepath);
			return;
		}
	}

}

void CShader::LoadGeometryShader(const char* filepath, ID3D11GeometryShader** tar)
{
	int count = 0;
	for (count = 0; count < MAX_SHADERS; count++) {
		if (strcmp(geoPath[count], filepath) == 0) {
			*tar = geoList[count];
			return;
		}
	}
	FILE* file;
	long int fsize;
	ID3D11GeometryShader* gshader;
	file = fopen(filepath, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	CRenderer::GetDevice()->CreateGeometryShader(buffer, fsize, NULL, &gshader);
	delete[] buffer;

	*tar = gshader;

	for (count = 0; count < MAX_SHADERS; count++) {
		if (geoPath[count][0] == '\0') {
			geoList[count] = gshader;
			strcpy(pixelPath[count], filepath);
			return;
		}
	}

}

void CShader::LoadVertexShader(const char * filepath, ID3D11VertexShader ** tar, ID3D11InputLayout ** tarinp, D3D11_INPUT_ELEMENT_DESC desc[], UINT numElements)
{
	int count = 0;
	for (count = 0; count < MAX_SHADERS; count++) {
		if (strcmp(vertexPath[count], filepath) == 0) {
			*tar = vertexList[count];
			*tarinp = indexList[count];
			return;
		}
	}
	FILE* file;
	long int fsize;
	ID3D11VertexShader* vshader = NULL;
	ID3D11InputLayout* ilayout = NULL;
	file = fopen(filepath, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	CRenderer::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &vshader);


	CRenderer::GetDevice()->CreateInputLayout(desc,
		numElements,
		buffer,
		fsize,
		&ilayout);
	*tar = vshader;

	*tarinp = ilayout;
	delete[] buffer;

	for (count = 0; count < MAX_SHADERS; count++) {
		if (vertexPath[count][0] == '\0') {
			vertexList[count] = vshader;
			indexList[count] = ilayout;
			strcpy(vertexPath[count], filepath);
			return;
		}
	}
}





