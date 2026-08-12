// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireSpell.h"


void UGrimoireSpell::InstantiateCombo()
{
	if (!instantiated_combo)
	{
		UGameInstance* gi = UGameplayStatics::GetGameInstance(GetWorld());
		UGI_GrimoireDataImp_Parent* grimoireGI = Cast<UGI_GrimoireDataImp_Parent>(gi);

		UGrimoireCategory* ingredients = Cast<UGrimoireCategory>(grimoireGI->grimoire_data ["Ingredient"]);
		
		TArray<FString> ingredient_keys = ingredients->GetEntryNames();

		for (int i = 0; i < ingredient_keys.Num(); i++)
		{
			TTuple<FString, FString>* pair = new TTuple<FString, FString>(ingredient_keys[i], "");
			combo_data.Add(*pair);
		}
		instantiated_combo = true;
	}
}

bool UGrimoireSpell::SetEntry(FString entry_key, FString table_key)
{
	bool output = Super::SetEntry(entry_key, table_key);

	InstantiateCombo();

	if (output)
		return output;

	if (entry_key.Equals("Spell"))
	{
		spell_name = table_key;
		return true;
	}
	else if (entry_key.Equals("Lore"))
	{
		lore_name = table_key;
		return true;
	}
	else
	{
		TArray<TPair<FString, FString>> combo_array = combo_data.Array();

		for (int i = 0; i < combo_array.Num(); i++)
		{
			if (entry_key.Equals(combo_array[i].Key))
			{
				combo_data[combo_array[i].Key] = table_key;
				return true;
			}
		}
		return false;
	}
}

UEntryData* UGrimoireSpell::GetEntry(FString entry_key)
{
	UEntryData* data = Super::GetEntry(entry_key);

	InstantiateCombo();

	if (data != nullptr)
		return data;
	
	if (entry_key.Equals("Spell"))
	{
		UDataTable* table = LoadObject<UDataTable>(this, TEXT("/Game/Programming/Grimoire/DT_Spells.DT_Spells"));
		data = NewObject<UEntryData>(this);
		data->SetKey(spell_name);
		data->SetDataTable(table);
		return data;
	}
	else if (entry_key.Equals("Lore"))
	{
		UDataTable* table = LoadObject<UDataTable>(this, TEXT("/Game/Programming/Grimoire/DT_Lore.DT_Lore"));
		data = NewObject<UEntryData>(this);
		data->SetKey(lore_name);
		data->SetDataTable(table);
		return data;
	}
	else
	{
		TArray<TPair<FString,FString>> combo_array = combo_data.Array();

		for (int i = 0; i < combo_array.Num(); i++)
		{
			if (entry_key.Equals(combo_array[i].Key))
			{
				UDataTable* table = LoadObject<UDataTable>(this, TEXT("/Game/Programming/Grimoire/DT_IngredientReactions.DT_IngredientReactions"));
				data = NewObject<UEntryData>(this);
				data->SetKey(spell_name + "_" + combo_array[i].Value);
				data->SetDataTable(table);
				return data;
			}
		}
		return nullptr;
	}
}

void UGrimoireSpell::Serialize(FArchive& Ar)
{
	Ar.UsingCustomVersion(SerialVersion::GUID);
	Super::Serialize(Ar);
	
	{
		if (Ar.IsSaving() && Ar.IsSaveGame())
		{
			int32 size = combo_data.Num();
			Ar << size;
			for (auto& KVPair : combo_data)
			{
				Ar << KVPair.Key;
				Ar << KVPair.Value;
			}
		}
		else if (Ar.IsLoading() && (!(Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireFix) || Ar.IsSaveGame()))
		{
			if (Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireRelease)
			{
				int32 size = 0;
				Ar << size;
				combo_data.Empty(size);
				if (size > 0)
					instantiated_combo = true;
				for (int32 i = 0; i < size; i++)
				{
					FString key = "";
					FString val = "";
					Ar << key; Ar << val;
					combo_data.Add(key, val);
					//SetEntry(key, val);
					/*
					if (GEngine && !val.IsEmpty())
					{
						GEngine->AddOnScreenDebugMessage(
							-1,          // Key: Use -1 to create a new message, or a specific number to overwrite an existing line
							5.0f,        // Duration: How long to display the message in seconds
							FColor::Yellow, // Color: The color of the text
							TEXT("Grimoire Spell") // The actual message
						);

						GEngine->AddOnScreenDebugMessage(
							-1,          // Key: Use -1 to create a new message, or a specific number to overwrite an existing line
							5.0f,        // Duration: How long to display the message in seconds
							FColor::Green, // Color: The color of the text
							key // The actual message
						);

						GEngine->AddOnScreenDebugMessage(
							-1,          // Key: Use -1 to create a new message, or a specific number to overwrite an existing line
							5.0f,        // Duration: How long to display the message in seconds
							FColor::Green, // Color: The color of the text
							val // The actual message
						);
					}
					*/
				}
			}
		}
	}
}


/*
TArray<TArray<FString>> UGrimoireSpell::GetEntries()
{
	TArray<TArray<FString>> output = Super::GetEntries();
	output.Add({"Spell", spell_name });
	output.Add({"Lore", lore_name});


	TArray<TPair<FString, FString>> combo_array = combo_data.Array();

	for (int i = 0; i < combo_array.Num(); i++)
	{
		output.Add({ combo_array[i].Get<0>(), combo_array[i].Get<1>()});
	}

	return output;
}
*/