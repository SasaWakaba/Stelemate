#include "main.h"
#include <Shlwapi.h>

#include "CDrawText.h"

void CDrawText::Initialize()
{
	// �t�H���g���g����悤�ɂ���
	DESIGNVECTOR design;
	AddFontResourceEx(
		TEXT("asset/Hannari.otf"),
		FR_PRIVATE,
		&design
	);
}

void CDrawText::Finalize()
{
	// ���\�[�X�폜
	DESIGNVECTOR design;
	RemoveFontResourceEx(
		TEXT("asset/Hannari.otf"), 
		FR_PRIVATE,
		&design
	);
}

void CDrawText::Draw(int x, int y, int h, std::string text)
{
	HDC hdc = GetDC(GetWindow());

	SetBkMode(hdc, TRANSPARENT);
	HFONT hFont;
	hFont = CreateFont(h,    //�t�H���g����
		0,                    //������
		0,                    //�e�L�X�g�̊p�x
		0,                    //�x�[�X���C���Ƃ����Ƃ̊p�x
		FW_REGULAR,            //�t�H���g�̏d���i�����j
		FALSE,                //�C�^���b�N��
		FALSE,                //�A���_�[���C��
		FALSE,                //�ł�������
		SHIFTJIS_CHARSET,    //�����Z�b�g
		OUT_DEFAULT_PRECIS,    //�o�͐��x
		CLIP_DEFAULT_PRECIS,//�N���b�s���O���x
		PROOF_QUALITY,        //�o�͕i��
		FIXED_PITCH | FF_MODERN,//�s�b�`�ƃt�@�~���[
		(LPTSTR)"�͂�Ȃ薾��");    //���̖�

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 255, 255));

	TextOut(hdc, x, y, (LPTSTR)text.c_str(), text.length());

	SelectObject(hdc, GetStockObject(SYSTEM_FONT));
	DeleteObject(hFont);

	ReleaseDC(GetWindow(), hdc);
}