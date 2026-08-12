#include "TeamAgentInterface.h"

bool ITeamAgentInterface::AreEnemies(AActor* ActorA, AActor* ActorB)
{
    if (!ActorA || !ActorB) return false;

    FGenericTeamId TeamA = GetTeamIdFromActor(ActorA);
    FGenericTeamId TeamB = GetTeamIdFromActor(ActorB);

    // NoTeam (255) is neutral — never an enemy
    if (TeamA == FGenericTeamId::NoTeam ||
        TeamB == FGenericTeamId::NoTeam)
        return false;

    return TeamA != TeamB;
}

FGenericTeamId ITeamAgentInterface::GetTeamIdFromActor(AActor* Actor)
{
    if (!Actor) return FGenericTeamId::NoTeam;

    ITeamAgentInterface* TeamAgent =
        Cast<ITeamAgentInterface>(Actor);

    if (TeamAgent)
    {
        return TeamAgent->GetTeamId();
    }

    return FGenericTeamId::NoTeam;
}