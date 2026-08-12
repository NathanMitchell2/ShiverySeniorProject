// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireMap.h"


bool UGrimoireMap::SetEntry(FString entry_key, FString table_key)
{
	if (entry_key.Equals("Image"))
	{
		map_name = table_key;
		return true;
	}
	else
	{
		return false;
	}
}

UEntryData* UGrimoireMap::GetEntry(FString entry_key)
{
	map_table = LoadObject<UDataTable>(this, TEXT("/Game/Programming/Grimoire/DT_Maps.DT_Maps"));
	if (entry_key.Equals("Image"))
	{
		UEntryData* data = NewObject<UEntryData>(this);
		data->SetKey(map_name);
		data->SetDataTable(map_table);
		return data;
	}
	else
	{
		return nullptr;
	}
}

/*
TArray<TArray<FString>> UGrimoireMap::GetEntries()
{
	TArray<TArray<FString>> output = Super::GetEntries();
	output.Add({ "Map", map_name });
	return output;
}
*/