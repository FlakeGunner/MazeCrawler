// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Blueprint/UserWidget.h"
#include "MazeCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "MyStaticLibrary.h"
#include "MazeCrawlerGameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of MazeCrawlerCharacter

UCLASS(minimalapi)
class AMazeCrawlerGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMazeCrawlerGameMode();

	UFUNCTION(BlueprintCallable, Category = "Maze Crawler")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	void SpawnCharacter(FVector location);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze Crawler")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

private:
	AMazeCharacter* m_MazeCharacter;

	TSubclassOf<class AMazeCharacter> m_MazeCharacterBlueprint;
};
