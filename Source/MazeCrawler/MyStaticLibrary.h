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

	template<typename ShuffleObjectType> static FORCEINLINE TArray<ShuffleObjectType> Shuffle(TArray<ShuffleObjectType> arrayToShuffle)
	{
		FRandomStream SRand = FRandomStream();
		SRand.GenerateNewSeed();

		for (int32 i = arrayToShuffle.Num() - 1; i > 0; i--) {
			int32 j = FMath::FloorToInt(SRand.FRand() * (i + 1)) % arrayToShuffle.Num();
			ShuffleObjectType temp = arrayToShuffle[i];
			arrayToShuffle[i] = arrayToShuffle[j];
			arrayToShuffle[j] = temp;
		}

		return arrayToShuffle;
	}
	
	
};

UENUM(BlueprintType)
enum class EMazeMoveDirection : uint8
{
	UP 		UMETA(DisplayName = "Up"),
	DOWN 	UMETA(DisplayName = "Down"),
	RIGHT	UMETA(DisplayName = "Right"),
	LEFT	UMETA(DisplayName = "Left")
};