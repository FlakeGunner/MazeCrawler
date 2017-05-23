// Fill out your copyright notice in the Description page of Project Settings.
#include "MazeMoveDirection.generated.h"

#pragma once
UENUM(BlueprintType)
enum class EMazeMoveDirection : uint8
{
	UP 		UMETA(DisplayName = "Up"),
	DOWN 	UMETA(DisplayName = "Down"),
	RIGHT	UMETA(DisplayName = "Right"),
	LEFT	UMETA(DisplayName = "Left")
};