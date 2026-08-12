// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrimoireEntry.h"
#include "GrimoireLore.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType)
class SHIVERY_API UGrimoireLore : public UGrimoireEntry
{
	GENERATED_BODY()

private:
	UPROPERTY(SaveGame)
	FString lore_name = "";

public:
	virtual bool SetEntry(FString entry_key, FString table_key) override;
	virtual UEntryData* GetEntry(FString entry_key) override;
	//TArray<TArray<FString>> GetEntries();
};
