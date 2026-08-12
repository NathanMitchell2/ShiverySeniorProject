// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireEntry.h"

bool UGrimoireEntry::isEntry(FString key_name)
{
	return key_name.Equals(entry_name);
}

FString UGrimoireEntry::GetEntryName()
{
	return entry_name;
}

/*
TArray<TArray<FString>> GetEntries()
{
	return TArray<TArray<FString>>();
}
*/

void UGrimoireEntry::Serialize(FArchive& Ar)
{
	Ar.UsingCustomVersion(SerialVersion::GUID);
	Super::Serialize(Ar);

	//if (!(Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireFix))
	{
		if (Ar.IsSaving() && Ar.IsSaveGame())
		{
			FString string = "";
			string = entry_name;
			//if (!(Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireFix))
				Ar << string;
		}
		else if (Ar.IsLoading() && (!(Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireFix) || Ar.IsSaveGame()))
		{
			if (Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireRelease)
			{
				FString string = "";
				//if (!(Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireFix))
				{
					Ar << string;
					entry_name = string;
				}
			}
			/*
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,          // Key: Use -1 to create a new message, or a specific number to overwrite an existing line
					5.0f,        // Duration: How long to display the message in seconds
					FColor::Yellow, // Color: The color of the text
					TEXT("Grimoire Entry") // The actual message
				);
				GEngine->AddOnScreenDebugMessage(
					-1,          // Key: Use -1 to create a new message, or a specific number to overwrite an existing line
					5.0f,        // Duration: How long to display the message in seconds
					FColor::Red, // Color: The color of the text
					string // The actual message
				);

				//UE_LOG(LogTemp, Error, string);
			}
			*/
		}
	}
}