// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireLore.h"


bool UGrimoireLore::SetEntry(FString entry_key, FString table_key)
{
	if (entry_key.Equals("Lore"))
	{
		lore_name = table_key;
		return true;
	}
	else
	{
		return false;
	}
}

UEntryData* UGrimoireLore::GetEntry(FString entry_key)
{
	if (entry_key.Equals("Lore"))
	{
		UDataTable* table = LoadObject<UDataTable>(this, TEXT("/Game/Programming/Grimoire/DT_Lore.DT_Lore"));
		UEntryData* data = NewObject<UEntryData>(this);
		data->SetKey(lore_name);
		data->SetDataTable(table);
		return data;
	}
	else
	{
		return nullptr;
	}
}


/*
TArray<TArray<FString>> UGrimoireLore::GetEntries()
{
	TArray<TArray<FString>> output = Super::GetEntries();
	output.Add({ "Lore", lore_name });
	return output;
}
*/