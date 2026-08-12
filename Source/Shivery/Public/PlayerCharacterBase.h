#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "TeamAgentInterface.h"
#include "PlayerCharacterBase.generated.h"

UCLASS()
class SHIVERY_API APlayerCharacterBase : public ACharacter,
    public IGenericTeamAgentInterface,
    public ITeamAgentInterface
{
    GENERATED_BODY()

public:
    APlayerCharacterBase();

    virtual FGenericTeamId GetGenericTeamId() const override;
    virtual FGenericTeamId GetTeamId_Implementation() const override;

private:
    FGenericTeamId TeamId;
};