#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "TeamAgentInterface.h"
#include "MonsterAIController.generated.h"

UCLASS()
class SHIVERY_API AMonsterAIController : public AAIController,
                                         public ITeamAgentInterface
{
    GENERATED_BODY()

public:
    AMonsterAIController();

    // IGenericTeamAgentInterface — used by UE perception system
    virtual FGenericTeamId GetGenericTeamId() const override;

    // ITeamAgentInterface — our custom interface
    virtual FGenericTeamId GetTeamId_Implementation() const override;

    UFUNCTION(BlueprintCallable, Category = "Monster|Timers")
    void StartNamedTimer(FName TimerName, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Monster|Timers")
    void ExpireNamedTimer(FName TimerName);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Timers")
    bool HasTimerExpired(FName TimerName) const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Timers")
    bool IsTimerActive(FName TimerName) const;

private:
    FGenericTeamId TeamId;
    UPROPERTY()
    TMap<FName, float> NamedTimers;
};