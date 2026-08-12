#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterEnums.h"
#include "MonsterStaggerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterStaggered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHIVERY_API UMonsterStaggerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMonsterStaggerComponent();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    // Apply explosion damage — call this from BP_ExplosionSpell on hit
    UFUNCTION(BlueprintCallable, Category = "Monster|Stagger")
    void ApplyExplosionHit(float DamageAmount);

    // Slowly drain gauge over time
    UFUNCTION(BlueprintCallable, Category = "Monster|Stagger")
    void TickDecay(float DeltaTime);

    // Is the monster fully staggered?
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Stagger")
    bool IsStaggered() const;

    // Reset gauge to 0
    UFUNCTION(BlueprintCallable, Category = "Monster|Stagger")
    void Reset();

    // Set whether this monster is in a death zone
    UFUNCTION(BlueprintCallable, Category = "Monster|Stagger")
    void SetIsInDeathZone(bool bInDeathZone);

    // Current stagger gauge 0.0-1.0
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster|Stagger")
    float StaggerGauge = 0.0f;

    // Threshold before stagger triggers (default 1.0 = 3 hits at 0.35 each)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Stagger")
    float StaggerThreshold = 1.0f;

    // How fast gauge decays per second when not being hit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Stagger")
    float DecayRate = 0.05f;

    // Set true on final level death zone
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Stagger")
    bool bIsInDeathZone = false;

    // Fired when monster reaches stagger threshold
    UPROPERTY(BlueprintAssignable, Category = "Monster|Stagger")
    FOnMonsterStaggered OnMonsterStaggered;

    // Fired when monster is in death zone and staggered
    UPROPERTY(BlueprintAssignable, Category = "Monster|Stagger")
    FOnMonsterDeath OnMonsterDeath;

protected:
    virtual void BeginPlay() override;

private:
    // Reference to motivation component for triggering breakout/despawn
    class UMonsterMotivationComponent* MotivationComponent;

    // Flag to prevent stagger triggering multiple times
    bool bStaggerTriggered = false;
};