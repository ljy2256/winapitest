#pragma once
#include "Res.h"
class Image :
    public Res
{
private:
    HDC     m_hdc;
    HBITMAP m_hBit;
    BITMAP  m_bitInfo;
private:
    Image();
    virtual ~Image();
    friend class ResMgr;
public:
    void Load(const wstring& _strFilePath);
    UINT GetWidth() { return m_bitInfo.bmWidth; }
    UINT GetHeight() { return m_bitInfo.bmHeight; }
    HDC GetDC() { return m_hdc; }
};

