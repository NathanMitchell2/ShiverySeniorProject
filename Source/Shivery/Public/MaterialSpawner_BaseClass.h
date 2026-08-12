// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MaterialSpawner_BaseClass.generated.h"

/**
 * Blueprintable, BlueprintType, 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class SHIVERY_API UMaterialSpawner_BaseClass : public UObject
{
	GENERATED_BODY()

//Implemented
public:
	UMaterialSpawner_BaseClass();

protected:
	AActor* actor = nullptr;
	
//Virtual
public:
	UFUNCTION(BlueprintCallable)
	virtual void Tick(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay();
	virtual void SetActor(AActor* p_actor);

// Pure Abstract
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetSpawnActor(TSubclassOf<AActor> p_actor) PURE_VIRTUAL(UMaterialSpawner_BaseClass::SetSpawnActor,);
	UFUNCTION(BlueprintCallable)
	virtual void PauseTimer() PURE_VIRTUAL(UMaterialSpawner_BaseClass::PauseTimer, ); //could make this return an id that StartTimer takes but overkill
	UFUNCTION(BlueprintCallable)
	virtual void StartTimer() PURE_VIRTUAL(UMaterialSpawner_BaseClass::StartTimer, );
	UFUNCTION(BlueprintCallable)
	virtual void PauseSpawn() PURE_VIRTUAL(UMaterialSpawner_BaseClass::PauseSpawn, ); //could make this return an id that StartTimer takes but overkill
	UFUNCTION(BlueprintCallable)
	virtual void StartSpawn() PURE_VIRTUAL(UMaterialSpawner_BaseClass::StartSpawn, );
	UFUNCTION(BlueprintCallable)
	virtual void IncreaseTimerByXToLimit(float x, float limit) PURE_VIRTUAL(UMaterialSpawner_BaseClass::IncreaseTimerByXToLimit,);
	UFUNCTION(BlueprintCallable)
	virtual void DecreaseTimerByXToLimit(float x, float limit) PURE_VIRTUAL(UMaterialSpawner_BaseClass::DecreaseTimerByXToLimit,);

protected:
	//virtual void SpawnMaterial() PURE_VIRTUAL(UMaterialSpawner_BaseClass::SpawnMaterial,);
	//virtual void UpdateTimer(float DeltaTime) PURE_VIRTUAL(UMaterialSpawner_BaseClass::UpdateTimer,);


};


/*
--------------------------
MaterialSpawner
	Uses EventChanceManager
	Uses Item (idk)
--------------------------
#item_chance_manager : EventChanceManager<Item>
#num_item_chance_manger : EventChanceManager<int>
-item_spawn_locations (location?): List<Transform>
-start_time : float
	Exposed in Editor
-timer : float
--------------------------
#Start() : void, (Note: learn how to bind OnDestroy in C++)
+Update() : void
#UpdateTimer() : void, virtual
-SpawnItems() : void
#RollForItem() : void, virtual
#IncreaseTimerByXToLimit(float x, float limit) : void
#ReduceTimerByXToLimit(float x, float limit) : void
--------------------------
--Update reduces timer by deltaTime
--------------------------
*/