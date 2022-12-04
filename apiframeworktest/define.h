#pragma once
//#define ADD(a,b) a+b
//int Add(int a, int b)
//{
//	return a + b;
//}
//int a = ADD(10, 10);
//a = 10 * ADD(5, 5);
//#define SINGLE(type) static type* GetInst() { static type mgr; return &mgr; }
#define SINGLE(type) static type* GetInst()\
					{\
						 static type mgr;\
						return &mgr;\
					}
#define WINDOW_NAME L"Gameframework"
#define fDT TimeMgr::GetInst()->GetfDT()
#define DT TimeMgr::GetInst()->GetDT()
#define KEY_CHECK(key, state) KeyMgr::GetInst()->GetKey(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define CLONE(type) type* Clone() {return new type(*this);}
#define PI 3.1415926535897932384f

//static Core* GetInst()
//{
//	static Core core;
//	return &core;
//}
enum class KEY_STATE
{
	NONE, // ������ �ʾҰ�, �������� ������ �ʴ� ����
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����(���� ������ �������ִ�)
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,Z,X,C,V,B,
	ALT,LSHIFT, CTRL, SPACE, ENTER, ESC,
	LBTN,RBTN, 
	LAST // �� (END=�� �����ϱ�)
};

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	BULLET_PLAYER,
	BULLET_MONSTER,
	MONSTER,

	END = 32,
};

enum class SCENE_TYPE
{
	START,
	TOOL,
	SCENE_01,
	SCENE_02,
	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};