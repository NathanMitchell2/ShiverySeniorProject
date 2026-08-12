// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrimoireItem.h"
#include "GrimoireIngredient.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType)
class SHIVERY_API UGrimoireIngredient : public UGrimoireItem
{
	GENERATED_BODY()

private:
	//UPROPERTY(EditAnywhere, Category = "Ingredient", meta = (DisplayName = "Ingredient Name"))
	UPROPERTY(SaveGame)
	FString ingredient_name = "";

public:
	virtual bool SetEntry(FString entry_key, FString table_key) override;
	virtual UEntryData* GetEntry(FString entry_key) override;
	//TArray<TArray<FString>> GetEntries();

};
