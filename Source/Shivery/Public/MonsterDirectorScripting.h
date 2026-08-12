#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MonsterEnums.h"
#include "MonsterDirectorScripting.generated.h"

class AActor;
class UAnimMontage;

/**
 * Blueprint Function Library for level designers to control the monster.
 * Call these from level triggers, sequences, or cutscene events.
 * All functions find BP_MonsterDirector automatically via tag "MonsterDirector".
 */
UCLASS()
class SHIVERY_API UMonsterDirectorScripting : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // === STATE CONTROL ===

    UFUNCTION(BlueprintCallable, Category = "Monster Director|State",
        meta = (WorldContext = "WorldContextObject"))
    static void ForceDirectorState(
        UObject* WorldContextObject,
        EDirectorState NewState);

    UFUNCTION(BlueprintCallable, Category = "Monster Director|State",
        meta = (WorldContext = "WorldContextObject"))
    static void LockDirectorState(
        UObject* WorldContextObject,
        bool bLock);

    UFUNCTION(BlueprintCallable, Category = "Monster Director|State",
        meta = (WorldContext = "WorldContextObject"))
    static void ReleaseDirector(UObject* WorldContextObject);

    UFUNCTION(BlueprintPure, Category = "Monster Director|State",
        meta = (WorldContext = "WorldContextObject"))
    static EDirectorState GetCurrentDirectorState(UObject* WorldContextObject);

    // === SPAWN/DESPAWN CONTROL ===

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Spawn",
        meta = (WorldContext = "WorldContextObject"))
    static void ForceSpawnAt(
        UObject* WorldContextObject,
        AActor* SpawnPoint);

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Spawn",
        meta = (WorldContext = "WorldContextObject"))
    static void ForceDespawnNow(UObject* WorldContextObject);

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Spawn",
        meta = (WorldContext = "WorldContextObject"))
    static void TeleportMonsterTo(
        UObject* WorldContextObject,
        FVector Location);

    // === BEHAVIOR OVERRIDE ===

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Behavior",
        meta = (WorldContext = "WorldContextObject"))
    static void ForceTargetActor(
        UObject* WorldContextObject,
        AActor* NewTarget);

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Behavior",
        meta = (WorldContext = "WorldContextObject"))
    static void ForceMoveTo(
        UObject* WorldContextObject,
        FVector Location,
        bool bRunSpeed);

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Behavior",
        meta = (WorldContext = "WorldContextObject"))
    static void ForceAttackPlayer(
        UObject* WorldContextObject,
        bool bIgnoreCooldowns);

    // === SENSE OVERRIDE ===

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Sense",
        meta = (WorldContext = "WorldContextObject"))
    static void ForceMonsterSeesPlayer(
        UObject* WorldContextObject,
        float Duration);

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Sense",
        meta = (WorldContext = "WorldContextObject"))
    static void ForceMonsterIgnoresPlayer(
        UObject* WorldContextObject,
        float Duration);

    // === CINEMATIC ===

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Cinematic",
        meta = (WorldContext = "WorldContextObject"))
    static void SetMonsterCinematicMode(
        UObject* WorldContextObject,
        bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Monster Director|Cinematic",
        meta = (WorldContext = "WorldContextObject"))
    static void PlayMontageOnMonster(
        UObject* WorldContextObject,
        UAnimMontage* Montage);

private:
    /** Helper to find the Director actor in the world */
    static AActor* FindMonsterDirector(UObject* WorldContextObject);
};