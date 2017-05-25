// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "MazeCrawlerGameMode.h"
#include "StartMarker.generated.h"

/**
 * 
 */
UCLASS()
class MAZECRAWLER_API AStartMarker : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:
	AStartMarker();

	UFUNCTION(BlueprintCallable, Category = "MazeCrawler")
		void StartTimer();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	

	
	
};

