#pragma once
#include "Object.h"
class Image;
class Bullet :
    public Object
{
private:
//    int  m_fDir; // �Ѿ� ����(��, �Ʒ�)
    float   m_fTheta; // �̵� ����
    Vec2    m_vDir;
    Image* m_pImage;
public:
//    void SetDir(bool _b)
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    {
        m_vDir = _vDir; 
        m_vDir.Normalize();
    }
    //{
        //if (_b) // ���̸� ��
        //    m_fDir = -1.f;
        //else
        //    m_fDir = 1.f;
    //}
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void EnterCollision(Collider* _pOther);

//    Bullet* Clone() { return new Bullet(*this); }
    CLONE(Bullet);
public:
    Bullet();
    ~Bullet();
};

