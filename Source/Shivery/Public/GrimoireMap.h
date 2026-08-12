// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrimoireEntry.h"
#include "GrimoireMap.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType)
class SHIVERY_API UGrimoireMap : public UGrimoireEntry
{
	GENERATED_BODY()

private:
	UDataTable* map_table;

	//UPROPERTY(EditAnywhere, Category = "Item", meta = (DisplayName = "Item Name"))
	UPROPERTY(SaveGame)
	FString map_name = "";

public:
	virtual bool SetEntry(FString entry_key, FString table_key) override;
	virtual UEntryData* GetEntry(FString entry_key) override;
	//TArray<TArray<FString>> GetEntries();
};
