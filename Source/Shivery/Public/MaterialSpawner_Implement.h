// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaterialSpawner_BaseClass.h"
#include "MaterialSpawner_Implement.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType)
class SHIVERY_API UMaterialSpawner_Implement : public UMaterialSpawner_BaseClass
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = true, DisplayName = "Material to Spawn"))
	TSubclassOf<AActor> spawn_actor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = true, ClampMin = 0, Delta = 0.5, ForceUnits = "sec", DisplayName = "Time to Spawn"))
	float start_time = 1;
	float timer = 0;
	int pause_count = 0;
	int spawn_count = 0;
	AActor* cur_spawned_actor = nullptr;

	UFUNCTION()
	void OnSpawnedActorDestroyed(AActor* DestroyedActor);

// Override BaseClass
public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
// Implement BaseClass
public:
	virtual void SetSpawnActor(TSubclassOf<AActor> p_actor) override;
	virtual void PauseTimer() override; //could make this return an id that StartTimer takes but overkill
	virtual void StartTimer() override;
	virtual void PauseSpawn() override; //could make this return an id that StartTimer takes but overkill
	virtual void StartSpawn() override;
	virtual void IncreaseTimerByXToLimit(float x, float limit) override;
	virtual void DecreaseTimerByXToLimit(float x, float limit) override;	

protected:
	virtual void SpawnMaterial();
	virtual void UpdateTimer(float DeltaTime);
};
