#pragma once
#include "Object.h"

class Image;
class Player :
    public Object
{
private:
    Image* m_pImage;
public:
    Player();
    //Player(const Player& _origin) 
    //    : Object(_origin)
    //    , m_pImage(_origin.m_pImage)
    //{}
    ~Player();
private:
    void CreateBullet();

//    Player* Clone{ return new Player(*this); }
    CLONE(Player);
public:
    void Update()       override;
    void Render(HDC _dc) override;
};

