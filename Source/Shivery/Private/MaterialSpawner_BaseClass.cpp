// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialSpawner_BaseClass.h"
UMaterialSpawner_BaseClass::UMaterialSpawner_BaseClass()
{
}
void UMaterialSpawner_BaseClass::Tick(float DeltaTime)
{
	//UpdateTimer(DeltaTime);
}

void UMaterialSpawner_BaseClass::BeginPlay()
{
	
}

void UMaterialSpawner_BaseClass::SetActor(AActor* c_actor)
{
	actor = c_actor;
}
