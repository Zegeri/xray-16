#include "StdAfx.h"
#include "Level.h"
#include "game_sv_capture_the_artefact.h"

game_sv_CaptureTheArtefact::MyTeam::MyTeam(
    TEAM_DATA_LIST::size_type indexInTeamList, u16 pCount, const shared_str& tName, const shared_str& aName)
    : indexOfTeamInList(indexInTeamList), playersCount(pCount), teamName(tName), artefactName(aName)
{}

void game_sv_CaptureTheArtefact::MyTeam::SetArtefactRPoint(const RPoint& rpoint)
{
    artefactRPoint = rpoint;
    rPointInitialized = true;
}

void game_sv_CaptureTheArtefact::MyTeam::OnPlayerAttachArtefact(CSE_ActorMP* newArtefactOwner)
{
    artefactOwner = newArtefactOwner;
    freeArtefactTimeStart = 0;
    activationArtefactTimeStart = 0;
    artefactActivated = false;
}

void game_sv_CaptureTheArtefact::MyTeam::OnPlayerDetachArtefact(CSE_ActorMP* oldArtefactOwner)
{
    VERIFY(oldArtefactOwner && artefactOwner);
    VERIFY2(oldArtefactOwner == artefactOwner,
        make_string("artefacts owners not equal: firstOwnerId = %d, secondOwnerId = %d", oldArtefactOwner->ID,
            artefactOwner->ID)
            .c_str());
    artefactOwner = NULL;
    freeArtefactTimeStart = Level().timeServer();
}

void game_sv_CaptureTheArtefact::MyTeam::OnPlayerActivateArtefact(u16 eid_who)
{
    activationArtefactTimeStart = Level().timeServer();
    artefactActivated = true;
    last_activator_id = eid_who;
}
bool game_sv_CaptureTheArtefact::MyTeam::IsArtefactActivated() { return artefactActivated; }
void game_sv_CaptureTheArtefact::MyTeam::DeactivateArtefact()
{
    artefactActivated = false;
    activationArtefactTimeStart = 0;
    last_activator_id = 0;
}

CSE_ActorMP* game_sv_CaptureTheArtefact::MyTeam::GetArtefactOwner() const { return artefactOwner; }
// functors ---------------
bool game_sv_CaptureTheArtefact::MinPlayersFunctor::operator()(const TeamPair& left, const TeamPair& right) const
{
    if (left.second.playersCount < right.second.playersCount)
    {
        return true;
    }
    return false;
}

bool game_sv_CaptureTheArtefact::SearchArtefactIdFunctor::operator()(const TeamPair& tr, u16 artefactId) const
{
    if (tr.second.artefact)
    {
        if (tr.second.artefact->ID == artefactId)
        {
            return true;
        }
    }
    return false;
}

bool game_sv_CaptureTheArtefact::SearchOwnerIdFunctor::operator()(const TeamPair& tr, u16 actorId) const
{
    if (tr.second.artefactOwner)
    {
        if (tr.second.artefactOwner->ID == actorId)
        {
            return true;
        }
    }
    return false;
}
