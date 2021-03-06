#pragma once
//==================================================================
//		## commonMacroFunction ## (필요한 분분은 직접 만들어서 추가할것!)
//==================================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//선 그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT 센터점에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//사각형 그리기 (렉탱글함수 사용)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//원 그리기 (일립스함수 사용)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//원 센터점 중심으로 그리기 (일립스함수 사용)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline bool PtInRhomBus(float x, float y, float width, float height, POINT pt)
{
	float k = fabs(pt.x - x) / (width / 2) + fabs(pt.y - y) / (height / 2);

	if (k <= 1) return true;

	return false;
}

inline void RhombusRender(HDC hdc, float x, float y, int width, int height, int penWidth, COLORREF penColor)
{
	HPEN drawPen, oldPen;
	drawPen = CreatePen(PS_SOLID, penWidth, penColor);
	oldPen = (HPEN)SelectObject(hdc, drawPen);
	LineMake(hdc, (int)x, (int)y, (int)x - width / 2, (int)y + height / 2);
	LineMake(hdc, (int)x, (int)y, (int)x + width / 2, (int)y + height / 2);
	LineMake(hdc, (int)x, (int)y + height, (int)x - width / 2, (int)y + height / 2);
	LineMake(hdc, (int)x, (int)y + height, (int)x + width / 2, (int)y + height / 2);
	DeleteObject(drawPen);
}
