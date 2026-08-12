// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireKey.h"


bool UGrimoireKey::SetEntry(FString entry_key, FString table_key)
{
	if (entry_key.Equals("Key"))
	{
		key_name = table_key;
		return true;
	}
	else
	{
		return false;
	}
}

UEntryData* UGrimoireKey::GetEntry(FString entry_key)
{
	if (entry_key.Equals("Key"))
	{
		UDataTable* table = LoadObject<UDataTable>(this, TEXT("/Game/Programming/Grimoire/DT_Keys.DT_Keys"));
		UEntryData* data = NewObject<UEntryData>(this);
		data->SetKey(key_name);
		data->SetDataTable(table);
		return data;
	}
	else
	{
		return nullptr;
	}
}

/*
TArray<TArray<FString>> UGrimoireKey::GetEntries()
{
	TArray<TArray<FString>> output = Super::GetEntries();
	output.Add({ "Key", key_name });
	return output;
}
*/