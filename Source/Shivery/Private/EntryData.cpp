// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryData.h"

void UEntryData::SetDataTable(UDataTable* table)
{
	data_table = table;
}

UDataTable* UEntryData::GetDataTable()
{
	return data_table;
}

void UEntryData::SetKey(FString str)
{
	this->string = str;
}

FString UEntryData::GetKey()
{
	return string;
}