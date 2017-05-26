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

	FVector actorLocation = GetActorLocation();

	actorLocation.X += 64.0f;
	actorLocation.Y += 28.0f;
	actorLocation.Z += -64.0f;

	AMazeCrawlerGameMode* gameMode = (AMazeCrawlerGameMode*)GetWorld()->GetAuthGameMode();

	gameMode->SpawnCharacter(actorLocation);

}

