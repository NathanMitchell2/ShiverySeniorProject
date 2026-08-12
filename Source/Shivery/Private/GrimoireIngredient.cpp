// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireIngredient.h"

bool UGrimoireIngredient::SetEntry(FString entry_key, FString table_key)
{
	bool output = Super::SetEntry(entry_key, table_key);

	if (output)
		return output;

	if (entry_key.Equals("Ingredient"))
	{
		ingredient_name = table_key;
		return true;
	}
	else
	{
		//See GrimoireSpell.cpp for template of how to set up reaction table
		return false;
	}
}

UEntryData* UGrimoireIngredient::GetEntry(FString entry_key)
{
	UEntryData* data = Super::GetEntry(entry_key);

	if (data != nullptr)
		return data;

	if (entry_key.Equals("Ingredient"))
	{
		UDataTable* table = LoadObject<UDataTable>(this, TEXT("/Game/Programming/Grimoire/DT_Ingredients.DT_Ingredients"));
		data = NewObject<UEntryData>(this);
		data->SetKey(ingredient_name);
		data->SetDataTable(table);
		return data;
	}
	else
	{
		//See GrimoireSpell.cpp for template of how to set up reaction table
		return nullptr;
	}
}
/*
TArray<TArray<FString>> UGrimoireIngredient::GetEntries()
{
	TArray<TArray<FString>> output = Super::GetEntries();
	output.Add({ "Ingredient", ingredient_name });
	return output;
}
*/