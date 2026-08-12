// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveVersion.h"
#include "Serialization/CustomVersion.h"

// Generate a brand new GUID for your custom version tracking
const FGuid SerialVersion::GUID(0x12345679, 0x12345679, 0x12345679, 0x12345679);

// Register the version profile into Unreal's global Serialization system
FCustomVersionRegistration GRegisterMyGameCustomVersion(
    SerialVersion::GUID,
    SerialVersion::LatestVersion,
    TEXT("Serial Versioning")
);

SaveVersion::SaveVersion()
{
}

SaveVersion::~SaveVersion()
{
}
