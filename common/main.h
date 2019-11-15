#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#include <assert.h>

#include <typeinfo>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>


#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")

void EndGaming(void);


#define SCREEN_WIDTH	(1440)			// ウインドウの幅
#define SCREEN_HEIGHT	(810)			// ウインドウの高さ

#define SPACE_SIZE (1.5f)

#define PI (3.14159265358979f)


HWND GetWindow();

typedef struct {
	XMFLOAT4 a, b, c, d;
}VertexColor_4;

struct Vector2_3D
{
	int x, z;

	bool operator==(const Vector2_3D& syc)
	{
		return x == syc.x && z == syc.z;
	}

	bool operator!=(const Vector2_3D& syc)
	{
		return x != syc.x || z != syc.z;
	}
};

typedef struct
{
	float x, y;
}UI_POS;

