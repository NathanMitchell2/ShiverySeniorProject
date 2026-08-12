// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialSpawner_PreventSpawnWrap.h"

void UMaterialSpawner_PreventSpawnWrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (actor != nullptr && prevents_actor != nullptr)
	{
		float distance = FVector::Distance(prevents_actor->GetActorLocation(), actor->GetActorLocation());

		if (distance > min_distance && distance < max_distance)
		{
			if (!within_distance)
			{
				within_distance = true;
				PauseSpawn();
			}
		}
		else
		{
			if (within_distance)
			{
				within_distance = false;
				StartSpawn();
			}
		}
	}
}

void UMaterialSpawner_PreventSpawnWrap::BeginPlay()
{
	Super::BeginPlay();

	if (prevents_actor == nullptr)
	{
		UWorld* const world = GetWorld();
		ACharacter* player = UGameplayStatics::GetPlayerCharacter(world, 0);
		prevents_actor = Cast<AActor>(player);
	}
}
