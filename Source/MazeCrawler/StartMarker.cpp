// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCrawler.h"
#include "StartMarker.h"


AStartMarker::AStartMarker()
{
	
}

void AStartMarker::StartTimer()
{

}


// Called when the game starts or when spawned
void AStartMarker::BeginPlay()
{
	Super::BeginPlay();

	FVector location(96.0f, 29.0f, -96.0f);

	AMazeCrawlerGameMode* gameMode = (AMazeCrawlerGameMode*)GetWorld()->GetAuthGameMode();

	gameMode->SpawnCharacter(location);

}

