// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireCategory.h"
#include "Engine/Engine.h"

UGrimoireEntry* UGrimoireCategory::FindEntry(FString entry_name)
{
    for (int i = 0; i < entries.Num(); i++)
    {
        UGrimoireEntry* cur = entries[i];
        if (cur->isEntry(entry_name))
            return cur;
    }
    return nullptr;
}

TArray<FString> UGrimoireCategory::GetEntryNames()
{
    TArray<FString> out;
    for (int i = 0; i < entries.Num(); i++)
    {
        out.Add(entries[i]->GetEntryName());
    }
    return out;
}

void UGrimoireCategory::Serialize(FArchive& Ar)
{
    Ar.UsingCustomVersion(SerialVersion::GUID);
    // Call super to ensure outer system properties are handled
    Super::Serialize(Ar);
    
    if (Ar.IsSaving() && Ar.IsSaveGame())
    {
        // 1. Write total array size
        //int32 ArraySize = entries.Num();
        int32 ArraySize = entries.Num();
        Ar << ArraySize;
        
        // 2. Loop and serialize each object
        for (UGrimoireEntry* Obj : entries)
        {
            bool bIsValid = (Obj != nullptr);
            Ar << bIsValid;


            if (bIsValid)
            {
                // Store the exact class path so we know what to instantiate on load
                FString ClassPath = Obj->GetClass()->GetPathName();
                Ar << ClassPath;

                // Let the object serialize its own inner variables
                //if (!(Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireFix))
                //Ar << Obj;
                Obj->Serialize(Ar);
            }
        }
        
    }
    else if (Ar.IsLoading() && (!(Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireFix) || Ar.IsSaveGame()))
    {
        if (Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireRelease)
        {
            // 1. Read array size and prepare container
            int32 ArraySize = 0;
            Ar << ArraySize;
            //entries.Empty();
            entries.Empty(ArraySize);
            
            // 2. Reconstruct each UObject
            for (int32 i = 0; i < ArraySize; ++i)
            {
                bool bIsValid = false;
                Ar << bIsValid;

                if (bIsValid)
                {
                    FString ClassPath;
                    Ar << ClassPath;

                    // Resolve the class type from string
                    UClass* ObjClass = LoadObject<UClass>(nullptr, *ClassPath);

                    if (ObjClass)
                    {
                        // Reconstruct object allocating memory with the owner as Outer
                        UGrimoireEntry* NewObj = NewObject<UGrimoireEntry>(this, ObjClass);

                        // Populate data fields
                        if (!(Ar.CustomVer(SerialVersion::GUID) >= SerialVersion::GrimoireFix))
                            Ar << NewObj;
                        else
                            NewObj->Serialize(Ar);

                        entries.Add(NewObj);
                        /*
                        if (GEngine)
                        {
                            FString out = ObjClass->GetDisplayNameText().ToString();
                            GEngine->AddOnScreenDebugMessage(
                                -1,          // Key: Use -1 to create a new message, or a specific number to overwrite an existing line
                                5.0f,        // Duration: How long to display the message in seconds
                                FColor::Yellow, // Color: The color of the text
                                TEXT("Grimoire Category") // The actual message
                            );
                            GEngine->AddOnScreenDebugMessage(
                                -1,          // Key: Use -1 to create a new message, or a specific number to overwrite an existing line
                                5.0f,        // Duration: How long to display the message in seconds
                                FColor::Red, // Color: The color of the text
                                out // The actual message
                            );
                            out = NewObj->GetEntryName();
                            GEngine->AddOnScreenDebugMessage(
                                -1,          // Key: Use -1 to create a new message, or a specific number to overwrite an existing line
                                5.0f,        // Duration: How long to display the message in seconds
                                FColor::Green, // Color: The color of the text
                                out // The actual message
                            );
                        }
                        */
                    }
                }
                else
                {
                    entries.Add(nullptr);
                }
            }
            
            
        }
    }
    
    
}


void UGrimoireCategory::AddEntry(UGrimoireEntry* entry)
{
    entries.Add(entry);
}
