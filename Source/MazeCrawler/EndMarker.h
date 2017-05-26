// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "EndMarker.generated.h"

/**
 * 
 */
UCLASS()
class MAZECRAWLER_API AEndMarker : public APaperSpriteActor
{
	GENERATED_BODY()
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
