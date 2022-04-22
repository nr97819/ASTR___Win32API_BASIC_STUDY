#pragma once
#include "CObject.h"

class CPlayer :
    public CObject
{
private:

public:
    virtual void Update() override;

public:
    CPlayer();
    ~CPlayer();
};

