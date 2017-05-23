// Fill out your copyright notice in the Description page of Project Settings.
#include "MazeCell.h"
#include "MazeGrid.generated.h"

#pragma once

//Special thanks to Rama for this 2d dynamic struct array implementation, and for many great answers, wiki posts and forum posts on Unreal Engine 4
// https://forums.unrealengine.com/showthread.php?47-SaxonRahs-Tutorial-Thread-Random-Maze-Generation-amp-Solving&p=27139&viewfull=1#post27139
USTRUCT()
struct FMazeGridRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<UMazeCell *> Columns;

	void AddNewColumn()
	{
		Columns.Add(NULL);
	}
	//default properties
	FMazeGridRow()
	{

	}
};

USTRUCT()
struct FMazeGrid
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<FMazeGridRow> Rows;

	void AddNewRow()
	{
		Rows.Add(FMazeGridRow());
	}

	void AddUninitialized(const int32 RowCount, const int32 ColCount)
	{
		//Add Rows
		for (int32 v = 0; v < RowCount; v++)
		{
			AddNewRow();
		}

		//Add Columns
		for (int32 v = 0; v < RowCount; v++)
		{
			for (int32 b = 0; b < ColCount; b++)
			{
				Rows[v].AddNewColumn();
			}
		}
	}

	void Clear()
	{
		if (Rows.Num() <= 0) return;
		//~~~~~~~~~~~~~~~

		//Destroy any walls
		const int32 RowTotal = Rows.Num();
		const int32 ColTotal = Rows[0].Columns.Num();

		for (int32 v = 0; v < RowTotal; v++)
		{
			for (int32 b = 0; b < ColTotal; b++)
			{
				if (Rows[v].Columns[b] && Rows[v].Columns[b]->IsValidLowLevel())
				{
					Rows[v].Columns[b]->ConditionalBeginDestroy();
				}
			}
		}

		//Empty
		for (int32 v = 0; v < Rows.Num(); v++)
		{
			Rows[v].Columns.Empty();
		}
		Rows.Empty();
	}
	//default properties
	FMazeGrid()
	{

	}
};