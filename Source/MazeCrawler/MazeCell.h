// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "MazeMoveDirection.h"
#include "MazeCell.generated.h"

/**
 * 
 */
UCLASS()
class MAZECRAWLER_API UMazeCell : public UObject
{
	GENERATED_BODY()
public:
	void Init(int x, int y, int size);
	void AddDirection(EMazeMoveDirection direction);
	TArray<EMazeMoveDirection> GetDirections();
	bool GetIsVisited();
	bool IsDirectionClosed(EMazeMoveDirection direction);
	int32 X();
	int32 Y();
	
private:
	TArray<EMazeMoveDirection> m_Directions;
	int32 m_X;
	int32 m_Y;
	int32 m_Size;
	
	
};
