// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteActor.h"
#include "PaperTileSet.h"
#include "MazeCell.h"
#include "MazeGrid.h"
#include "StartMarker.h"
#include "EndMarker.h"
#include "MyStaticLibrary.h"
#include <unordered_map>
#include <stdexcept>
#include <map>
#include "MazeGenerator.generated.h"

UCLASS()
class MAZECRAWLER_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();
	void GenerateMaze();
	void CarvePassagesFrom(int32 currentX, int32 currentY);
	void RenderMaze();
	void AddStartAndEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

private:	
	void PopulateGrid();

	UPaperTileMapComponent* m_TileMapComp;
	AStartMarker* m_StartMarker;
	AEndMarker* m_EndMarker;
	UPaperTileSet* m_TileSet;
	TSubclassOf<class AStartMarker> m_StartMarkerBlueprint;
	TSubclassOf<class AEndMarker> m_EndMarkerBlueprint;
	FMazeGrid m_Grid;
	int32 m_GridSize;
	int32 m_CellSize;
	std::unordered_map<EMazeMoveDirection, int32> m_DirectionX;
	std::unordered_map<EMazeMoveDirection, int32> m_DirectionY;
	std::unordered_map<EMazeMoveDirection, EMazeMoveDirection> m_Opposite;
	TArray<UMazeCell *> deadEnds;
	
};


