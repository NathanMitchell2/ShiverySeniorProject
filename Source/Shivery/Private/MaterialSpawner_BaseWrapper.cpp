// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialSpawner_BaseWrapper.h"

void UMaterialSpawner_BaseWrapper::SetMaterialSpawner(UMaterialSpawner_BaseClass* ms)
{
	material_spawner = ms;
}

void UMaterialSpawner_BaseWrapper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (material_spawner != nullptr)
		material_spawner->Tick(DeltaTime);
}

void UMaterialSpawner_BaseWrapper::BeginPlay()
{
	Super::BeginPlay();

	if (material_spawner != nullptr)
		material_spawner->BeginPlay();
}

void UMaterialSpawner_BaseWrapper::SetActor(AActor* p_actor)
{
	Super::SetActor(p_actor);

	if (material_spawner != nullptr)
		material_spawner->SetActor(p_actor);
}

void UMaterialSpawner_BaseWrapper::SetSpawnActor(TSubclassOf<AActor> p_actor)
{
	if (material_spawner != nullptr)
		material_spawner->SetSpawnActor(p_actor);
}

void UMaterialSpawner_BaseWrapper::PauseTimer()
{
	if (material_spawner != nullptr)
		material_spawner->PauseTimer();
}

void UMaterialSpawner_BaseWrapper::StartTimer()
{
	if (material_spawner != nullptr)
		material_spawner->StartTimer();
}

void UMaterialSpawner_BaseWrapper::PauseSpawn()
{
	if (material_spawner != nullptr)
		material_spawner->PauseSpawn();
}

void UMaterialSpawner_BaseWrapper::StartSpawn()
{
	if (material_spawner != nullptr)
		material_spawner->StartSpawn();
}

void UMaterialSpawner_BaseWrapper::IncreaseTimerByXToLimit(float x, float limit)
{
	if (material_spawner != nullptr)
		material_spawner->IncreaseTimerByXToLimit(x, limit);
}

void UMaterialSpawner_BaseWrapper::DecreaseTimerByXToLimit(float x, float limit)
{
	if (material_spawner != nullptr)
		material_spawner->DecreaseTimerByXToLimit(x, limit);
}