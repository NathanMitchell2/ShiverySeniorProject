#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterDirectorConfig.generated.h"

UCLASS(BlueprintType)
class SHIVERY_API UMonsterDirectorConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    // How long monster stays frontstage before going backstage
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timing")
    float FrontstageDuration = 40.0f;

    // How long monster stays backstage before returning
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timing")
    float BackstageDuration = 30.0f;

    // How fast menace gauge fills per second when monster is near player
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menace")
    float MenaceFillRate = 0.10f;

    // How fast menace gauge drains per second when monster is far
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menace")
    float MenaceDrainRate = 0.10f;

    // How many times monster can menace player in one frontstage session
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menace")
    int32 MaxMenaceCount = 3;

    // Radius of frontstage sweep area around DirectorTargetLocation
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float SweepRadius = 1500.0f;

    // Starting radius of stalk search — shrinks each subsequent stalk
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float StalkRadius = 1200.0f;

    // How much StalkRadius shrinks per stalk session (0.1 = 10% tighter each time)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float StalkRadiusShrinkRate = 0.1f;

    // Minimum stalk radius — never shrinks below this
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MinStalkRadius = 300.0f;

    // Whether ambush attacks are allowed in this config
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Permissions")
    bool bAmbushAllowed = false;

    // Whether killtrap placement is allowed in this config
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Permissions")
    bool bKilltrapAllowed = false;

    // Distance threshold — within this distance menace starts filling
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menace")
    float MenaceStartDistance = 1500.0f;
};