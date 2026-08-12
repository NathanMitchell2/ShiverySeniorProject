// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrimoireData.h"
#include "GrimoireBool.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced, Blueprintable, BlueprintType)
class SHIVERY_API UGrimoireBool : public UGrimoireData
{
	GENERATED_BODY()

	//Implemented
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = true, DisplayName = "Is Active"))
	bool is_active = false;
};
