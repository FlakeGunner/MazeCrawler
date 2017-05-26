// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCrawler.h"
#include "MazeGenerator.h"


// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UPaperTileSet> locateTileSet(TEXT("PaperTileSet'/Game/Maps/Level_Two/basic_block_TileSet.basic_block_TileSet'"));
	m_TileSet = locateTileSet.Object;

	static ConstructorHelpers::FObjectFinder<UBlueprint> locateStartMarkerBlueprint(TEXT("Blueprint'/Game/Blueprints/StartMarker_BP.StartMarker_BP'"));
	if (locateStartMarkerBlueprint.Object) {
		m_StartMarkerBlueprint = (UClass*)locateStartMarkerBlueprint.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> locateEndMarkerBlueprint(TEXT("Blueprint'/Game/Blueprints/EndMarker_BP.EndMarker_BP'"));
	if (locateEndMarkerBlueprint.Object) {
		m_EndMarkerBlueprint = (UClass*)locateEndMarkerBlueprint.Object->GeneratedClass;
	}
	
	m_GridSize = 8;

	m_CellSize = 6;

	m_DirectionX = {
		{ EMazeMoveDirection::UP, 0 },
		{ EMazeMoveDirection::DOWN, 0 },
		{ EMazeMoveDirection::RIGHT, 1 },
		{ EMazeMoveDirection::LEFT, -1 }
	};

	m_DirectionY = {
		{ EMazeMoveDirection::UP, -1 },
		{ EMazeMoveDirection::DOWN, 1 },
		{ EMazeMoveDirection::RIGHT, 0 },
		{ EMazeMoveDirection::LEFT, 0 }
	};

	m_Opposite = {
		{ EMazeMoveDirection::UP, EMazeMoveDirection::DOWN },
		{ EMazeMoveDirection::DOWN, EMazeMoveDirection::UP },
		{ EMazeMoveDirection::RIGHT, EMazeMoveDirection::LEFT },
		{ EMazeMoveDirection::LEFT, EMazeMoveDirection::RIGHT }
	};


}

// Special thanks to Jamis Buck for his excellent articles on Maze Generation Algorithms
// http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking

void AMazeGenerator::GenerateMaze()
{
	PopulateGrid();

	CarvePassagesFrom(0, 0);
}

void AMazeGenerator::CarvePassagesFrom(int32 currentX, int32 currentY)
{
	TArray<EMazeMoveDirection> directions;
	directions.Add(EMazeMoveDirection::UP);
	directions.Add(EMazeMoveDirection::DOWN);
	directions.Add(EMazeMoveDirection::LEFT);
	directions.Add(EMazeMoveDirection::RIGHT);

	directions = UMyStaticLibrary::Shuffle<EMazeMoveDirection>(directions);


	bool isDeadEnd = true;

	for (auto& direction : directions)
	{
		int32 newX = currentX + m_DirectionX[direction];
		int32 newY = currentY + m_DirectionY[direction];

		if (newY >= 0 && newY <= (m_GridSize - 1) && newX >= 0 && newX <= (m_GridSize - 1) && !m_Grid.Rows[newX].Columns[newY]->GetIsVisited())
		{
			m_Grid.Rows[currentX].Columns[currentY]->AddDirection(direction);
			m_Grid.Rows[newX].Columns[newY]->AddDirection(m_Opposite[direction]);

			isDeadEnd = false;

			CarvePassagesFrom(newX, newY);
		}

	}

	if (isDeadEnd)
	{
		deadEnds.Add(m_Grid.Rows[currentX].Columns[currentY]);
	}

}

void AMazeGenerator::RenderMaze()
{

	m_TileMapComp = NewObject<UPaperTileMapComponent>(this);
	if (m_TileMapComp)
	{
		m_TileMapComp->RegisterComponent();
		m_TileMapComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		m_TileMapComp->CreateNewTileMap(m_GridSize * m_CellSize, m_GridSize * m_CellSize, 32, 32, 1, true);
		m_TileMapComp->SetRelativeLocation(FVector(16.0f, 1.0f, -16.0f));
		m_TileMapComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		m_TileMapComp->MakeTileMapEditable();

		FPaperTileInfo LocalTileInfo;
		LocalTileInfo.TileSet = m_TileSet;
		LocalTileInfo.PackedTileIndex = 0;


		for (auto& row : m_Grid.Rows)
		{
			for (auto& mazeCell : row.Columns)
			{
				int32 cellOriginX = (mazeCell->X() * m_CellSize) - mazeCell->X();
				int32 cellOriginY = (mazeCell->Y() * m_CellSize) - mazeCell->Y();
				if (mazeCell->IsDirectionClosed(EMazeMoveDirection::UP))
				{
					for (int32 i = 0; i < m_CellSize; i++)
					{
						m_TileMapComp->SetTile(cellOriginX + i, cellOriginY, 0, LocalTileInfo);
					}	
				}
				if (mazeCell->IsDirectionClosed(EMazeMoveDirection::DOWN))
				{
					for (int32 i = 0; i < m_CellSize; i++)
					{
						m_TileMapComp->SetTile(cellOriginX + i, cellOriginY + m_CellSize - 1, 0, LocalTileInfo);
					}
				}
				if (mazeCell->IsDirectionClosed(EMazeMoveDirection::LEFT))
				{
					for (int32 i = 0; i < m_CellSize; i++)
					{
						m_TileMapComp->SetTile(cellOriginX, cellOriginY + i, 0, LocalTileInfo);
					}
				}
				if (mazeCell->IsDirectionClosed(EMazeMoveDirection::RIGHT))
				{
					for (int32 i = 0; i < m_CellSize; i++)
					{
						m_TileMapComp->SetTile(cellOriginX + m_CellSize - 1, cellOriginY + i, 0, LocalTileInfo);
					}
				}
			}
		}

		m_TileMapComp->RebuildCollision();

	}
}

void AMazeGenerator::AddStartAndEnd()
{
	UWorld* const World = GetWorld();
	if (World) {

		FVector startLocation = m_TileMapComp->GetTileCornerPosition(1, 1, 1, true);

		startLocation.Y = 1.0f;

		m_StartMarker = UMyStaticLibrary::SpawnBP<AStartMarker>(GetWorld(), m_StartMarkerBlueprint, startLocation, FRotator(0.0f, 0.0f, 0.0f));

		deadEnds = UMyStaticLibrary::Shuffle<UMazeCell*>(deadEnds);

		int32 cellOriginX = m_GridSize - 1;
		int32 cellOriginY = m_GridSize - 1;
		for (auto& deadEnd : deadEnds)
		{
			if (deadEnd->X() < (m_GridSize / 2) || deadEnd->Y() < (m_GridSize / 2)) {
				continue;
			}

			cellOriginX = (deadEnd->X() * m_CellSize) - deadEnd->X() + 1;
			cellOriginY = (deadEnd->Y() * m_CellSize) - deadEnd->Y() + 1;
			break;
		}

		
		
		FVector endLocation = m_TileMapComp->GetTileCornerPosition(cellOriginX, cellOriginY, 1, true);

		endLocation.Y = 1.0f;

		m_EndMarker = UMyStaticLibrary::SpawnBP<AEndMarker>(GetWorld(), m_EndMarkerBlueprint, endLocation, FRotator(0.0f, 0.0f, 0.0f));
		
	}
}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();

	GenerateMaze();

	RenderMaze();

	AddStartAndEnd();
	
}



void AMazeGenerator::PopulateGrid()
{
	m_Grid.Clear();
	m_Grid.AddUninitialized(m_GridSize, m_GridSize);

	for (int x = 0; x < m_GridSize; x++)
	{
		for (int y = 0; y < m_GridSize; y++)
		{
			FString CellName = FString::Printf(TEXT("Cell_%d_%d"), x, y);
			UMazeCell* newCell = NewObject<UMazeCell>(this, UMazeCell::StaticClass(), *CellName);
			newCell->Init(x, y, m_CellSize);
			m_Grid.Rows[x].Columns[y] = newCell;
		}
	}
}


