// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireItem.h"

bool UGrimoireItem::SetEntry(FString entry_key, FString table_key)
{
	if (entry_key.Equals("Item"))
	{
		item_name = table_key;
		return true;
	}
	else
	{
		return false;
	}
}

UEntryData* UGrimoireItem::GetEntry(FString entry_key)
{
	item_table = LoadObject<UDataTable>(this, TEXT("/Game/Programming/InventorySystem/ItemDataTable.ItemDataTable"));
	if (entry_key.Equals("Item"))
	{ 
		UEntryData* data = NewObject<UEntryData>(this);
		data->SetKey(item_name);
		data->SetDataTable(item_table);
		return data;
	}
	else
	{
		return nullptr;
	}
}

/*
TArray<TArray<FString>> UGrimoireItem::GetEntries()
{
	TArray<TArray<FString>> output = Super::GetEntries();
	output.Add({ "Item", item_name });
	return output;
}
*/