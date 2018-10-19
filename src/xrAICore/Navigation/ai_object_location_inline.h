////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_object_location.h
//	Created 	: 27.11.2003
//  Modified 	: 27.11.2003
//	Author		: Dmitriy Iassenev
//	Description : AI object location
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "xrAICore/Navigation/level_graph.h"
#include "xrAICore/Navigation/game_graph.h"
#include "xrGame/ai_space.h"

IC void CAI_ObjectLocation::init()
{
    if (ai().get_level_graph())
        ai().level_graph().set_invalid_vertex(m_level_vertex_id);
    else
        m_level_vertex_id = u32(-1);

    if (ai().get_game_graph())
        ai().game_graph().set_invalid_vertex(m_game_vertex_id);
    else
        m_game_vertex_id = GameGraph::_GRAPH_ID(-1);
}

IC CAI_ObjectLocation::CAI_ObjectLocation() { init(); }
IC void CAI_ObjectLocation::reinit() { init(); }
IC const GameGraph::_GRAPH_ID CAI_ObjectLocation::game_vertex_id() const { return (m_game_vertex_id); }
IC const u32 CAI_ObjectLocation::level_vertex_id() const { return (m_level_vertex_id); }
