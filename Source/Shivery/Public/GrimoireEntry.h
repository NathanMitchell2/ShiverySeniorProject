// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EntryData.h"
#include "SaveVersion.h"
#include "GrimoireEntry.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)
class SHIVERY_API UGrimoireEntry : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, Category = "Entry", meta = (DisplayName = "Entry Name", ExposeOnSpawn = "true"))
	FString entry_name = "";

public:
	bool isEntry(FString key_name);
	FString GetEntryName();
	UFUNCTION(BlueprintCallable)
	virtual bool SetEntry(FString entry_key, FString table_key) PURE_VIRTUAL(UGrimoireEntry::SetEntry, return false;);
	UFUNCTION(BlueprintCallable)
	virtual UEntryData* GetEntry(FString entry_key) PURE_VIRTUAL(UGrimoireEntry::GetEntry, return nullptr;);
	//UFUNCTION(BlueprintCallable)
	//TArray<TArray<FString>> GetEntries();
	virtual void Serialize(FArchive& Ar) override;
};
