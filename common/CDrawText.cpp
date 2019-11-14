#include "main.h"
#include <Shlwapi.h>

#include "CDrawText.h"

void CDrawText::Initialize()
{
	// フォントを使えるようにする
	DESIGNVECTOR design;
	AddFontResourceEx(
		TEXT("asset/Hannari.otf"),
		FR_PRIVATE,
		&design
	);
}

void CDrawText::Finalize()
{
	// リソース削除
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
	hFont = CreateFont(h,    //フォント高さ
		0,                    //文字幅
		0,                    //テキストの角度
		0,                    //ベースラインとｘ軸との角度
		FW_REGULAR,            //フォントの重さ（太さ）
		FALSE,                //イタリック体
		FALSE,                //アンダーライン
		FALSE,                //打ち消し線
		SHIFTJIS_CHARSET,    //文字セット
		OUT_DEFAULT_PRECIS,    //出力精度
		CLIP_DEFAULT_PRECIS,//クリッピング精度
		PROOF_QUALITY,        //出力品質
		FIXED_PITCH | FF_MODERN,//ピッチとファミリー
		(LPTSTR)"はんなり明朝");    //書体名

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 255, 255));

	TextOut(hdc, x, y, (LPTSTR)text.c_str(), text.length());

	SelectObject(hdc, GetStockObject(SYSTEM_FONT));
	DeleteObject(hFont);

	ReleaseDC(GetWindow(), hdc);
}