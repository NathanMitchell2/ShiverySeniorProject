#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterEnums.h"
#include "MonsterMotivationComponent.generated.h"

USTRUCT(BlueprintType)
struct FMotivationEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EMonsterMotivation Motivation = EMonsterMotivation::NONE;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 Priority = 0;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHIVERY_API UMonsterMotivationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMonsterMotivationComponent();

    // Add a motivation with a given priority — higher number = higher priority
    UFUNCTION(BlueprintCallable, Category = "Monster|Motivation")
    void AddMotivation(EMonsterMotivation Motivation, int32 Priority);

    // Remove a motivation
    UFUNCTION(BlueprintCallable, Category = "Monster|Motivation")
    void RemoveMotivation(EMonsterMotivation Motivation);

    // Check if a motivation is currently active
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Motivation")
    bool HasMotivation(EMonsterMotivation Motivation) const;

    // Get the highest priority active motivation
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Motivation")
    EMonsterMotivation GetActiveMotivation() const;

    // Get all active motivations sorted by priority
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Monster|Motivation")
    TArray<FMotivationEntry> GetAllMotivations() const;

    // Clear all motivations
    UFUNCTION(BlueprintCallable, Category = "Monster|Motivation")
    void ClearAllMotivations();

    UFUNCTION(BlueprintCallable, Category = "Monster|Motivation")
    void OnBreakoutTriggered();

    UFUNCTION(BlueprintCallable, Category = "Monster|Motivation")
    void UpdateBlackboardMotivation();

    UFUNCTION(BlueprintCallable, Category = "Monster|Motivation")
    void UpdateAnimInstanceMotivation();

    UFUNCTION(BlueprintCallable, Category = "Monster|Motivation")
    void BroadcastActiveMotivation();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster|Motivation")
    TArray<FMotivationEntry> ActiveMotivations;
};