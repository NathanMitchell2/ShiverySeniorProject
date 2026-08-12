#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterEnums.h"
#include "MonsterTrapComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrapTriggered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrapExpired);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHIVERY_API UMonsterTrapComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMonsterTrapComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    // Call this from BP_Trap on overlap with monster
    UFUNCTION(BlueprintCallable, Category = "Monster|Trap")
    void TriggerTrap();

    // Called when trap duration expires
    UFUNCTION(BlueprintCallable, Category = "Monster|Trap")
    void OnTrapExpired();

    // Is monster currently trapped?
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Trap")
    bool IsTrapped() const;

    // Can monster be trapped? (ban timer check)
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Trap")
    bool CanBeTrapped() const;

    // How long monster stays frozen
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Trap")
    float TrapDuration = 5.0f;

    // Cooldown before monster can be trapped again
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Trap")
    float TrapBanDuration = 15.0f;

    // Fired when trap triggers — bind in BP to play animation + sound
    UPROPERTY(BlueprintAssignable, Category = "Monster|Trap")
    FOnTrapTriggered OnTrapTriggered;

    // Fired when trap expires — bind in BP to play recovery animation
    UPROPERTY(BlueprintAssignable, Category = "Monster|Trap")
    FOnTrapExpired OnTrapExpiredDelegate;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster|Trap")
    bool bIsTrapped = false;

protected:
    virtual void BeginPlay() override;

private:
    class UMonsterMotivationComponent* MotivationComponent;
    class UCharacterMovementComponent* MovementComponent;
    class AAIController* AIController;

    // Timer handles
    FTimerHandle TrapDurationHandle;
    FTimerHandle TrapBanHandle;

    float OriginalMaxWalkSpeed = 0.0f;
    bool bIsBanned = false;
};