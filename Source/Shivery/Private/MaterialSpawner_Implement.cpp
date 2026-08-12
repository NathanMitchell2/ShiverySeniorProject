// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialSpawner_Implement.h"


/*
* Having trouble compiling with this, try to figure out later
* 
UMaterialSpawner_Implement::UMaterialSpawner_Implement() : Super()
{
	//Super::Super();

}
*/

void UMaterialSpawner_Implement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateTimer(DeltaTime);
}

void UMaterialSpawner_Implement::BeginPlay()
{
	Super::BeginPlay();

	SpawnMaterial();
	timer = start_time;
}

void UMaterialSpawner_Implement::UpdateTimer(float DeltaTime)
{
	if (!(spawn_count > 0) && timer <= 0)
	{
		SpawnMaterial();
		timer = start_time + timer;
	}

	if (pause_count > 0)
		return;

	if (spawn_count > 0 && timer <= 0)
		return;

	timer -= DeltaTime;

	/*
	* Original Placement of SpawnMaterial, makes more sense but might be less effective
	if (timer <= 0)
	{
		SpawnMaterial();
		timer = start_time + timer;
	}
	*/
}

void UMaterialSpawner_Implement::SpawnMaterial()
{
	if (cur_spawned_actor != nullptr)
		return;

	UWorld* const world = GetWorld();

	//FString MyString = FString::Printf(TEXT("%x"), spawn_actor.Get());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);

	if (world != nullptr && actor != nullptr && spawn_actor != nullptr)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = actor;
		cur_spawned_actor = world->SpawnActor<AActor>(spawn_actor.Get(), actor->GetActorTransform(), spawnParams);

		cur_spawned_actor->OnDestroyed.AddDynamic(this, &UMaterialSpawner_Implement::OnSpawnedActorDestroyed);//(&UMaterialSpawner_Implement::StartTimer);
		
		PauseTimer();
	}

}

void UMaterialSpawner_Implement::SetSpawnActor(TSubclassOf<AActor> p_actor)
{
	spawn_actor = p_actor;
}

void UMaterialSpawner_Implement::PauseTimer()
{
	pause_count += 1;
}

void UMaterialSpawner_Implement::StartTimer()
{
	pause_count -= 1;
}

void UMaterialSpawner_Implement::PauseSpawn()
{
	spawn_count += 1;
}

void UMaterialSpawner_Implement::StartSpawn()
{
	spawn_count -= 1;
}

void UMaterialSpawner_Implement::IncreaseTimerByXToLimit(float x, float limit)
{
	timer += x;
	
	timer = fminf(timer, limit);
}

void UMaterialSpawner_Implement::DecreaseTimerByXToLimit(float x, float limit)
{
	timer -= x;

	timer = fmaxf(timer, limit);
}

void UMaterialSpawner_Implement::OnSpawnedActorDestroyed(AActor* DestroyedActor) { cur_spawned_actor = nullptr;  StartTimer(); }