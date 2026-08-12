#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "UObject/Interface.h"
#include "TeamAgentInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UTeamAgentInterface : public UInterface
{
    GENERATED_BODY()
};

class SHIVERY_API ITeamAgentInterface
{
    GENERATED_BODY()

public:
    // Call this to get the team ID of any actor
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Teams")
    FGenericTeamId GetTeamId() const;

    // Helper: are two actors enemies?
    static bool AreEnemies(AActor* ActorA, AActor* ActorB);

    // Helper: get team ID safely from any actor
    static FGenericTeamId GetTeamIdFromActor(AActor* Actor);
};