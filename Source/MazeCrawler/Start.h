// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Start.generated.h"

UCLASS()
class MAZECRAWLER_API AStart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MazeCrawler")
		void SpawnCharacter();

	UFUNCTION(BlueprintCallable, Category = "MazeCrawler")
		void StartTimer();

};
