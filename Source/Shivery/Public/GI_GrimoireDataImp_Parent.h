// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/NoExportTypes.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "GrimoireData.h"
#include "GI_GrimoireDataImp_Parent.generated.h"


USTRUCT(BlueprintType)
struct FSaveObject
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<UObject> ObjectClass;

	UPROPERTY()
	TArray<uint8> ObjectData;

	FSaveObject()
	{
		ObjectClass = NULL;
		ObjectData = {};
	}
};
USTRUCT(BlueprintType)
struct FMapSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FString, FSaveObject> SerializedMap;

	FMapSaveData()
	{
		SerializedMap = {};
	}
};

/**
 * 
 */
UCLASS()
class SHIVERY_API UGI_GrimoireDataImp_Parent : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, SaveGame, Category = "Grimoire Data")
	TMap<FString, UGrimoireData*> grimoire_data;
	UFUNCTION(BlueprintCallable)
	FMapSaveData GetGrimoireSaveData();
	UFUNCTION(BlueprintCallable)
	void SetGrimoireSaveData(FMapSaveData saveData);
};
