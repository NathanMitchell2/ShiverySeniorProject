// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GrimoireCategory.h"
#include "GI_GrimoireDataImp_Parent.h"
#include "GrimoireItem.h"
#include "GrimoireSpell.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType)
class SHIVERY_API UGrimoireSpell : public UGrimoireItem
{
	GENERATED_BODY()

private:
	//UPROPERTY(EditAnywhere, Category = "Spell", meta = (DisplayName = "Spell Name"))
	UPROPERTY(SaveGame)
	FString spell_name = "";
	UPROPERTY(SaveGame)
	FString lore_name = "";
	bool instantiated_combo = false;
	//UPROPERTY(EditAnywhere, Category = "Ingredient", meta = (DisplayName = "Combinations"))
	//UPROPERTY(SaveGame)
	TMap<FString, FString> combo_data;

	void InstantiateCombo();

public:
	virtual bool SetEntry(FString entry_key, FString table_key) override;
	virtual UEntryData* GetEntry(FString entry_key) override;
	//TArray<TArray<FString>> GetEntries();
	virtual void Serialize(FArchive& Ar) override;
};
