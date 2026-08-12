// Fill out your copyright notice in the Description page of Project Settings.


#include "A_MaterialSpawner.h"

// Sets default values
AA_MaterialSpawner::AA_MaterialSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Some Stuff I Found
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootSceneComponent);

	RootSceneComponent->SetMobility(EComponentMobility::Type::Static);

	//material_spawner = CreateDefaultSubobject<UMaterialSpawner_Implement>(TEXT("Material Spawner"));
}

// Called when the game starts or when spawned
void AA_MaterialSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Try to make this a default subobject later (kept on crashing on play with memory issues)
	//material_spawner = NewObject<UMaterialSpawner_Implement>(this,TEXT("Material Spawner"));
	

	if (material_spawner != nullptr)
	{
		material_spawner->SetActor(this);
		/*if (material != nullptr)
		{
			material_spawner->SetSpawnActor(material);
		}*/

		material_spawner->BeginPlay();
	}
		
}

// Called every frame
void AA_MaterialSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (material_spawner != nullptr)
	{
		//FString MyString = FString::Printf(TEXT("Address: %x"), material_spawner);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);
		material_spawner->Tick(DeltaTime);
	}
}


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
#Update() : void
#UpdateTimer() : void, virtual
-SpawnItems() : void
#RollForItem() : void, virtual
#IncreaseTimerByXToLimit(float x, float limit) : void
#ReduceTimerByXToLimit(float x, float limit) : void
--------------------------
--Update reduces timer by deltaTime
--------------------------
*/
