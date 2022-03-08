// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic.h"

// Sets default values
AGameLogic::AGameLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameLogic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameLogic::StartBatch(const unsigned int batchSize)
{
	for (size_t i = 0; i < batchSize; i++)
	{
		StartMatch();
	}
	
}

void AGameLogic::StartMatch()
{
	
}

void AGameLogic::EndMatch()
{
	// destroy actor and save Score
}

// Called every frame
void AGameLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// if (timePerRound < timeElapsedThisRound)
	// 	timeElapsedThisRound += DeltaTime;
	// else
	// {
	// 	timeElapsedThisRound = 0;
	// 	EndMatch();
	// }

	// StartBatch(40u);
}

