#include "pch.h"
#include "Vec2.h"

Vec2::Vec2()
	: x(0.f)
	, y(0.f)
{
}

Vec2::~Vec2()
{
}

Vec2::Vec2(float _x, float _y)
	: x(_x)
	, y(_y)
{
}
/*m_ptResolution 을 받아오는 타입이 
Vec2가 아닌 POINT라서 그렇습니다. 
Resolution을 받아오는 타입 역시 Vec2로 받아오면 
오류가 생기지 않습니다.

POINT x,y가 int가 아니고 LONG타입이니깐 
struct.h에 생성자에 
long 타입을 추가해도 될 거 같습니다

*/

/// <summary>
/// int는 float으로 변환해도 소수점 아래가 0일테니 이걸 빼자?
/// </summary>
/// <param name="_x"></param>
/// <param name="_y"></param>
Vec2::Vec2(int _x, int _y)
	: x((float)_x)
	, y((float)_y)
{
}

Vec2::Vec2(long _x, long _y)
	: x(_x)
	, y(_y)
{
}

Vec2::Vec2(const POINT _pt)
	: x((float)_pt.x)
	, y((float)_pt.y)
{
}

float Vec2::Length()
{
	return sqrt(x * x + y * y);
}

Vec2& Vec2::Normalize()
{
	float fLen = Length();
	assert(fLen != 0.f);
	x /= fLen;
	y /= fLen;
	return *this;
}


