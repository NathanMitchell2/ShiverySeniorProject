// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MaterialSpawner_BaseClass.h"
#include "MaterialSpawner_Implement.h"
#include "A_MaterialSpawner.generated.h"

UCLASS(Blueprintable)
class SHIVERY_API AA_MaterialSpawner : public AActor
{
	GENERATED_BODY()

public:
	//UPROPERTY(BlueprintReadOnly,EditAnywhere)
	//TSubclassOf<AActor> material; // The actor MaterialSpawner spawns
	// Material Spawner Creation Options?

	AA_MaterialSpawner(); // Sets default values for this actor's properties

public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Material Spawner")
	UMaterialSpawner_BaseClass* material_spawner;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	USceneComponent* RootSceneComponent;

	virtual void BeginPlay() override; // Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override; // Called every frame

private:
	// C++ Implementation (TODO)
	//UPROPERTY(EditAnywhere)
	//UObjectTestBase* matSpwn;

	//Make this UPROPERTY so can change what MaterialSpawner is used
	//Make MaterialSpawner_Implementation public

	/*
	Right now features like altering behavior are only allowed by children of MaterialSpawner_Implementation
	If you need to make other classes comunicate with this class would need to make those methods public and add a delegate
	*/

};
