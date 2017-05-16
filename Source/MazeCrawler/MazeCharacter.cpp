// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCrawler.h"
#include "MazeCharacter.h"

AMazeCharacter::AMazeCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> locateMoveUp(TEXT("PaperFlipbook'/Game/Characters/Crawler/move_up.move_up'"));
	m_MoveUp = locateMoveUp.Object;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> locateMoveDown(TEXT("PaperFlipbook'/Game/Characters/Crawler/move_down.move_down'"));
	m_MoveDown = locateMoveDown.Object;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> locateMoveRight(TEXT("PaperFlipbook'/Game/Characters/Crawler/move_right.move_right'"));
	m_MoveRight = locateMoveRight.Object;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> locateMoveLeft(TEXT("PaperFlipbook'/Game/Characters/Crawler/move_left.move_left'"));
	m_MoveLeft = locateMoveLeft.Object;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> locateIdleUp(TEXT("PaperFlipbook'/Game/Characters/Crawler/idle_up.idle_up'"));
	m_IdleUp = locateIdleUp.Object;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> locateIdleDown(TEXT("PaperFlipbook'/Game/Characters/Crawler/idle_down.idle_down'"));
	m_IdleDown = locateIdleDown.Object;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> locateIdleRight(TEXT("PaperFlipbook'/Game/Characters/Crawler/idle_right.idle_right'"));
	m_IdleRight = locateIdleRight.Object;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> locateIdleLeft(TEXT("PaperFlipbook'/Game/Characters/Crawler/idle_left.idle_left'"));
	m_IdleLeft = locateIdleLeft.Object;

	m_LastMovedDirection = EMazeMoveDirection::RIGHT;
}

void AMazeCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}

void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovementFlipbook();
}

void AMazeCharacter::UpdateMovementFlipbook()
{
	if (InputComponent)
	{
		float RightOrLeft = InputComponent->GetAxisValue(TEXT("RightOrLeft"));
		float UpOrDown = InputComponent->GetAxisValue(TEXT("UpOrDown"));

		if (RightOrLeft != 0 || UpOrDown != 0)
		{
			if (UpOrDown > 0)
			{
				m_LastMovedDirection = EMazeMoveDirection::UP;
			}
			else if (UpOrDown < 0)
			{
				m_LastMovedDirection = EMazeMoveDirection::DOWN;
			}
			else if (RightOrLeft > 0)
			{
				m_LastMovedDirection = EMazeMoveDirection::RIGHT;
			}
			else
			{
				m_LastMovedDirection = EMazeMoveDirection::LEFT;
			}
		}

		if (GetVelocity().Size() > 0)
		{
			switch (m_LastMovedDirection) 
			{
			case EMazeMoveDirection::UP:
				GetSprite()->SetFlipbook(m_MoveUp);
				break;
			case EMazeMoveDirection::DOWN:
				GetSprite()->SetFlipbook(m_MoveDown);
				break;
			case EMazeMoveDirection::RIGHT:
				GetSprite()->SetFlipbook(m_MoveRight);
				break;
			case EMazeMoveDirection::LEFT:
				GetSprite()->SetFlipbook(m_MoveLeft);
				break;
			}
		}
		else
		{

			switch (m_LastMovedDirection)
			{
			case EMazeMoveDirection::UP:
				GetSprite()->SetFlipbook(m_IdleUp);
				break;
			case EMazeMoveDirection::DOWN:
				GetSprite()->SetFlipbook(m_IdleDown);
				break;
			case EMazeMoveDirection::RIGHT:
				GetSprite()->SetFlipbook(m_IdleRight);
				break;
			case EMazeMoveDirection::LEFT:
				GetSprite()->SetFlipbook(m_IdleLeft);
				break;
			}

		}

	}

}



