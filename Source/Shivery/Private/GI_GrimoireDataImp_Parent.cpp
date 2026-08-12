// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_GrimoireDataImp_Parent.h"

FMapSaveData UGI_GrimoireDataImp_Parent::GetGrimoireSaveData()
{
    FMapSaveData OutSaveData;

    for (const auto& KVPair : grimoire_data)
    {
        UObject* TargetObject = KVPair.Value;
        if (!IsValid(TargetObject)) continue;

        FSaveObject Record;
        Record.ObjectClass = TargetObject->GetClass();

        // 1. Setup a binary data buffer
        FMemoryWriter MemoryWriter(Record.ObjectData);

        // 2. Wrap archive to handle UObject naming references correctly
        FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
        Archive.ArIsSaveGame = true; // Filters variables tagged with 'SaveGame'

        // 3. Capture subobject's internal UPROPERTY states
        TargetObject->Serialize(Archive);

        // 4. Store into output package map
        OutSaveData.SerializedMap.Add(KVPair.Key, Record);
    }

    return OutSaveData;
}

void UGI_GrimoireDataImp_Parent::SetGrimoireSaveData(FMapSaveData saveData)
{
    // Clear out stale objects or handle as needed per design context
    grimoire_data.Empty();

    for (const auto& KVPair : saveData.SerializedMap)
    {
        const FString& Key = KVPair.Key;
        const FSaveObject& Record = KVPair.Value;

        if (!Record.ObjectClass) continue;

        // 1. Re-instantiate the precise UObject archetype instance
        UGrimoireData* temp = NewObject<UGrimoireData>(this, Record.ObjectClass);

        // 2. Setup the binary reading framework
        FMemoryReader MemoryReader(Record.ObjectData);
        FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
        Archive.ArIsSaveGame = true;

        // 3. Inject variables back into the new runtime instance
        temp->Serialize(Archive);

        // 4. Register newly minted subobject back to your main runtime container
        grimoire_data.Add(Key, temp);
    }
}
