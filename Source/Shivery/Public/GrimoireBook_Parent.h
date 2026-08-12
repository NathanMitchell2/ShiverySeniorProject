// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrimoireSpread_Parent.h"
#include "GrimoireBook_Parent.generated.h"


UCLASS( Blueprintable, meta=(BlueprintSpawnableComponent) )
class SHIVERY_API UGrimoireBook_Parent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrimoireBook_Parent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Grimoire Book")
	TArray<UGrimoireSpread_Parent*> spreads;
};
