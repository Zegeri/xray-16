#pragma once
// XXX: Identify what parts of xrGame requires only "core", ui, ai, and finally script.
// Split up source (PCH-wise) accordingly.
// This will likely for a long time be WIP.

#include "Common/Common.hpp"

#include "xrEngine/stdafx.h" // XXX: This seems bad. PCH's are for internal (building) use.
#if !defined(LINUX)
#include "DPlay/dplay8.h"
#endif

#include "xrScriptEngine/DebugMacros.hpp"
#include "game_type.h"
// xrEngine src file count is ~1100.
// Comments following individual includes refers to number of times they are included in xrEngine as a whole.
//#include <assert.h> // ~440 - but it has no include guard! Perhaps that's intentional?
#include <math.h>
#include "xrServerEntities/smart_cast.h" // a lot
#include "Level.h"
#ifdef DEBUG
#include "Include/xrRender/DebugRender.h"
#endif
