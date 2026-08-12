// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireBook_Parent.h"

// Sets default values for this component's properties
UGrimoireBook_Parent::UGrimoireBook_Parent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrimoireBook_Parent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrimoireBook_Parent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

