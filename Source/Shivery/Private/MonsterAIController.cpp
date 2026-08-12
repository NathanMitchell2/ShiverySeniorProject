
#include "MonsterAIController.h"

AMonsterAIController::AMonsterAIController()
{
    TeamId = FGenericTeamId(1);
}

FGenericTeamId AMonsterAIController::GetGenericTeamId() const
{
    return TeamId;
}

FGenericTeamId AMonsterAIController::GetTeamId_Implementation() const
{
    return TeamId;
}
void AMonsterAIController::StartNamedTimer(FName TimerName, float Duration)
{
    // Store the world time when this timer expires
    float ExpiryTime = GetWorld()->GetTimeSeconds() + Duration;
    NamedTimers.Add(TimerName, ExpiryTime);
}

void AMonsterAIController::ExpireNamedTimer(FName TimerName)
{
    // Set expiry to 0 so HasTimerExpired returns true immediately
    NamedTimers.Add(TimerName, 0.0f);
}

bool AMonsterAIController::HasTimerExpired(FName TimerName) const
{
    const float* ExpiryTime = NamedTimers.Find(TimerName);

    // Timer doesn't exist = treat as expired
    if (!ExpiryTime) return true;

    return GetWorld()->GetTimeSeconds() >= *ExpiryTime;
}

bool AMonsterAIController::IsTimerActive(FName TimerName) const
{
    return !HasTimerExpired(TimerName);
}