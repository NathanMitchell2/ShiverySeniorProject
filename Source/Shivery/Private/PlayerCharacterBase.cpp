#include "PlayerCharacterBase.h"

APlayerCharacterBase::APlayerCharacterBase()
{
    // Player is team 0
    TeamId = FGenericTeamId(0);
}

FGenericTeamId APlayerCharacterBase::GetGenericTeamId() const
{
    return TeamId;
}

FGenericTeamId APlayerCharacterBase::GetTeamId_Implementation() const
{
    return TeamId;
}