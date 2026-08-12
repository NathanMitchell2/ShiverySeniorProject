// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaterialSpawner_BaseClass.h"
#include "MaterialSpawner_BaseWrapper.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class SHIVERY_API UMaterialSpawner_BaseWrapper : public UMaterialSpawner_BaseClass
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Wrapped Material Spawner")
	UMaterialSpawner_BaseClass* material_spawner = nullptr;

public:
	void SetMaterialSpawner(UMaterialSpawner_BaseClass* ms);

	// Override BaseClass
public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetActor(AActor* p_actor) override;

	// Implement BaseClass
public:
	virtual void SetSpawnActor(TSubclassOf<AActor> p_actor) override;
	virtual void PauseTimer() override; //could make this return an id that StartTimer takes but overkill
	virtual void StartTimer() override;
	virtual void PauseSpawn() override;
	virtual void StartSpawn() override;
	virtual void IncreaseTimerByXToLimit(float x, float limit) override;
	virtual void DecreaseTimerByXToLimit(float x, float limit) override;
};
