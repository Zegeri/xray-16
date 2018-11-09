#pragma once

#include "script_object.h"

class CFryupZone : public CScriptObject
{
    typedef CScriptObject inherited;

public:
    CFryupZone() = default;
    virtual ~CFryupZone() = default;

#ifdef DEBUG
    virtual void OnRender() {};
#endif
};
