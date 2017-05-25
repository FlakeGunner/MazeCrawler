// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "MyStaticLibrary.h"
#include "MazeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MAZECRAWLER_API AMazeCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	AMazeCharacter();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "MazeCrawler")
	void UpdateMovementFlipbook();

	UPROPERTY()
		EMazeMoveDirection m_LastMovedDirection;

private:
	UPaperFlipbook * m_MoveUp;
	UPaperFlipbook * m_MoveDown;
	UPaperFlipbook * m_MoveRight;
	UPaperFlipbook * m_MoveLeft; 
	UPaperFlipbook * m_IdleUp;
	UPaperFlipbook * m_IdleDown;
	UPaperFlipbook * m_IdleRight;
	UPaperFlipbook * m_IdleLeft;
};
