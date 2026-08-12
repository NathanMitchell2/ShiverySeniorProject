// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaterialSpawner_BaseWrapper.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "MaterialSpawner_PreventSpawnWrap.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType)
class SHIVERY_API UMaterialSpawner_PreventSpawnWrap : public UMaterialSpawner_BaseWrapper
{
	GENERATED_BODY()

//Implementing
private:
	UPROPERTY(EditAnywhere, Category = "Prevent Spawing", meta = (DisplayName = "Use Player as Actor to Detect"))
	bool bUsePlayer = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prevent Spawing", meta = (AllowPrivateAccess = true, DisplayName = "Actor to Detect", ToolTip = "When None set gets first player character", EditCondition="!bUsePlayer", EditConditionHides))
	AActor* prevents_actor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prevent Spawing", meta = (AllowPrivateAccess = true, DisplayName = "Prevents Spawning at distance >:"))
	float min_distance = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prevent Spawing", meta = (AllowPrivateAccess = true, DisplayName = "Prevents Spawing at distance <:"))
	float max_distance = 10;

	bool within_distance = false;

//Overriding
public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
