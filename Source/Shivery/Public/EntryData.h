// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EntryData.generated.h"

/**
 * 
 */
UCLASS()
class SHIVERY_API UEntryData : public UObject
{
	GENERATED_BODY()
	
private:
	FString string = "";
	UDataTable* data_table = nullptr;

public:
	void SetKey(FString str);
	void SetDataTable(UDataTable* table);

	UFUNCTION(BlueprintCallable)
	FString GetKey();
	UFUNCTION(BlueprintCallable)
	UDataTable* GetDataTable();
};
