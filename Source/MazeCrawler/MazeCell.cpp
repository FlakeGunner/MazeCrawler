// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCrawler.h"
#include "MazeCell.h"

void UMazeCell::Init(int x, int y, int size)
{
	m_X = x;
	m_Y = y;
	m_Size = size;
}

bool UMazeCell::GetIsVisited()
{
	if (m_Directions.Num() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UMazeCell::IsDirectionClosed(EMazeMoveDirection direction)
{
	return !m_Directions.Contains(direction);
}


void UMazeCell::AddDirection(EMazeMoveDirection direction)
{
	m_Directions.Add(direction);
}

TArray<EMazeMoveDirection> UMazeCell::GetDirections()
{
	return TArray<EMazeMoveDirection>();
}

int32 UMazeCell::X()
{
	return m_X;
}

int32 UMazeCell::Y()
{
	return m_Y;
}

