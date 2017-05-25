// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MazeCrawler.h"
#include "MazeCrawlerGameMode.h"
#include "MazeCrawlerCharacter.h"

AMazeCrawlerGameMode::AMazeCrawlerGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AMazeCrawlerCharacter::StaticClass();	

	static ConstructorHelpers::FObjectFinder<UBlueprint> locateMazeCharacterBlueprint(TEXT("Blueprint'/Game/Blueprints/MazeCharacter_BP.MazeCharacter_BP'"));
	if (locateMazeCharacterBlueprint.Object) {
		m_MazeCharacterBlueprint = (UClass*)locateMazeCharacterBlueprint.Object->GeneratedClass;
	}
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

void AMazeCrawlerGameMode::SpawnCharacter(FVector location)
{
	UWorld* const World = GetWorld();
	if (World) {
		m_MazeCharacter = UMyStaticLibrary::SpawnBP<AMazeCharacter>(GetWorld(), m_MazeCharacterBlueprint, location, FRotator(0.0f, 0.0f, 0.0f));

		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->UnPossess();
		controller->Possess(m_MazeCharacter);
	}
}
