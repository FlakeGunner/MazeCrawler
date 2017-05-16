// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MazeCrawlerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAZECRAWLER_API AMazeCrawlerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
};


