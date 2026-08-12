// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/GUID.h"

struct SerialVersion
{
	enum Type
	{
		InitialRelease,
		GrimoireRelease,
		GrimoireFix,
		LatestVersion = GrimoireFix
	};

	static const FGuid GUID;
};
/**
 * 
 */
class SHIVERY_API SaveVersion
{
	public:
		SaveVersion();
		~SaveVersion();
};
