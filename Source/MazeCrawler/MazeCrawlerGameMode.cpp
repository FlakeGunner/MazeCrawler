// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MazeCrawler.h"
#include "MazeCrawlerGameMode.h"
#include "MazeCrawlerCharacter.h"

AMazeCrawlerGameMode::AMazeCrawlerGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AMazeCrawlerCharacter::StaticClass();	
}
