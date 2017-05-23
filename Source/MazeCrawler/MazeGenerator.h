// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "MazeCell.h"
#include "MazeGrid.h"
#include <unordered_map>
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

private:	
	TArray<EMazeMoveDirection> Shuffle(TArray<EMazeMoveDirection> directions);
	void PopulateGrid();

	UPaperTileMapComponent* m_TileMapComp;
	UPaperTileSet* m_TileSet;
	FMazeGrid m_Grid;
	int32 m_GridSize;
	int32 m_CellSize;
	std::unordered_map<EMazeMoveDirection, int32> m_DirectionX;
	std::unordered_map<EMazeMoveDirection, int32> m_DirectionY;
	std::unordered_map<EMazeMoveDirection, EMazeMoveDirection> m_Opposite;
	
};
