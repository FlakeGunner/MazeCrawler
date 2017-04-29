// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MazeCrawler.h"
#include "MazeCrawlerGameMode.h"
#include "MazeCrawlerCharacter.h"

AMazeCrawlerGameMode::AMazeCrawlerGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AMazeCrawlerCharacter::StaticClass();	
}

void AMazeCrawlerGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void AMazeCrawlerGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
