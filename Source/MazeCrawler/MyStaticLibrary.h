// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "MyStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MAZECRAWLER_API UMyStaticLibrary : public UObject
{
	GENERATED_BODY()
public:
		template <typename BPObjectType> static FORCEINLINE BPObjectType* SpawnBP(
		UWorld*         TheWorld,
		UClass*         TheBP,
		const FVector&  Loc,
		const FRotator& Rot,
		AActor*         Owner = NULL,
		APawn*          Instigator = NULL
	) {
		if (!TheWorld) return NULL;
		if (!TheBP) return NULL;

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.bDeferConstruction = false;

		return TheWorld->SpawnActor<BPObjectType>(TheBP, Loc, Rot, SpawnInfo);
	}
	
	
};
