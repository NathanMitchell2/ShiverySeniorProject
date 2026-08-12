#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterEnums.h"
#include "MonsterSenseComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHIVERY_API UMonsterSenseComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMonsterSenseComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    // Increase a sense activation level
    UFUNCTION(BlueprintCallable, Category = "Monster|Sense")
    void IncreaseSense(EMonsterSenseType SenseType, float Amount);

    // Manually decrease a sense
    UFUNCTION(BlueprintCallable, Category = "Monster|Sense")
    void DecreaseSense(EMonsterSenseType SenseType, float Amount);

    // Is sense above a threshold?
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Sense")
    bool IsSenseActivationAbove(
        EMonsterSenseType SenseType,
        ESenseThreshold Threshold) const;

    // How many seconds since sense was last above threshold
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Sense")
    float GetLastTimeSensed(
        EMonsterSenseType SenseType,
        ESenseThreshold Threshold) const;

    // Was the last sense increase above threshold?
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Sense")
    bool WasSenseThresholdLastIncreaseAbove(
        EMonsterSenseType SenseType,
        ESenseThreshold Threshold) const;

    // Get raw activation level 0.0-1.0
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Sense")
    float GetSenseLevel(EMonsterSenseType SenseType) const;

    // Reset a specific sense to 0
    UFUNCTION(BlueprintCallable, Category = "Monster|Sense")
    void ResetSense(EMonsterSenseType SenseType);

    // Reset all senses
    UFUNCTION(BlueprintCallable, Category = "Monster|Sense")
    void ResetAllSenses();

    // Update lamp sense from BB PlayerLampIntensity
    UFUNCTION(BlueprintCallable, Category = "Monster|Sense")
    void UpdateLampSense(float LampIntensity);

    // Threshold values — designers can tune these
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Sense|Thresholds")
    float LowerThreshold = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Sense|Thresholds")
    float ActivatedThreshold = 0.6f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Sense|Thresholds")
    float UpperThreshold = 0.9f;

    // Decay rate per second for each sense
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Sense|Decay")
    float DefaultDecayRate = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Sense|Decay")
    float VisualDecayRate = 0.15f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster|Sense|Decay")
    float ExplosionDecayRate = 0.05f;

protected:
    virtual void BeginPlay() override;

private:
    // Current activation level per sense type
    TMap<EMonsterSenseType, float> SenseActivationLevels;

    // Time when sense last exceeded each threshold
    TMap<EMonsterSenseType, float> LastTimeAboveLower;
    TMap<EMonsterSenseType, float> LastTimeAboveActivated;
    TMap<EMonsterSenseType, float> LastTimeAboveUpper;

    // Was last increase above threshold
    TMap<EMonsterSenseType, bool> LastIncreaseAboveLower;
    TMap<EMonsterSenseType, bool> LastIncreaseAboveActivated;
    TMap<EMonsterSenseType, bool> LastIncreaseAboveUpper;

    // Get threshold float value from enum
    float GetThresholdValue(ESenseThreshold Threshold) const;

    // Get decay rate for specific sense
    float GetDecayRate(EMonsterSenseType SenseType) const;

    // Update last time maps after sense change
    void UpdateThresholdTimes(EMonsterSenseType SenseType,
        float OldLevel, float NewLevel);
};