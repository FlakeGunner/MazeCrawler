// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCrawler.h"
#include "MazeCrawlerPlayerController.h"

void AMazeCrawlerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}


