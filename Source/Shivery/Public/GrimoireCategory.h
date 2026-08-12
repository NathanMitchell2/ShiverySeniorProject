// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrimoireData.h"
#include "GrimoireEntry.h"
#include "SaveVersion.h"
#include "GrimoireCategory.generated.h"


/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType)
class SHIVERY_API UGrimoireCategory : public UGrimoireData
{
	GENERATED_BODY()
	

private:
	UPROPERTY(EditAnywhere, Instanced, Category = "Entry", meta = (AllowPrivateAccess = true, DisplayName = "Entries"))
	TArray<UGrimoireEntry*> entries;

public:
	UFUNCTION(BlueprintCallable)
	UGrimoireEntry* FindEntry(FString entry_name);
	UFUNCTION(BlueprintCallable)
	void AddEntry(UGrimoireEntry* entry);
	TArray<FString> GetEntryNames();
	//UFUNCTION(BlueprintCallable)
	//TArray<UGrimoireEntry*> GetEntries();
	virtual void Serialize(FArchive& Ar) override;
};
