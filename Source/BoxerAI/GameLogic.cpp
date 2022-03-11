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
		// StartMatch();
	}
	
}

int AGameLogic::GetAgentId()
{
	return agentId;
}

void AGameLogic::SetAgentId(const int _agentId)
{
	agentId = _agentId;
}

void AGameLogic::SaveScore(const float _score)
{
	FString path = FPaths::ProjectDir() + TEXT("\\Weights\\") + FString::FromInt(agentId) + TEXT(".score");
	FString content = FString::SanitizeFloat(_score);
	FFileHelper::SaveStringToFile(content, *path, FFileHelper::EEncodingOptions::AutoDetect);
}

FString AGameLogic::LoadScore()
{
	FString path = FPaths::ProjectDir() + TEXT("\\Weights\\") + FString::FromInt(agentId) + TEXT(".score");
	FString content;
	FFileHelper::SaveStringToFile(content, *path, FFileHelper::EHashOptions::None, (uint32_t)0u);
	return content;
}

void AGameLogic::NaturalSelection(const float mortality, const float propability, const float mutability)
{
	float score[40];
	float fitnessSum;
	float min = std::numeric_limits<float>::max();

	for (agentId = 0; agentId < 40; agentId++)
	{
		score[agentId] = FCString::Atof(LoadScore());
		fitnessSum += val;
		if (min > score[40])
		{
			min = score[40];
		}
	}
	agentId = 0;

	// only allow positve numbers
	fitnessSum += min;
	float chosenOne = rand() % fitnessSum;
	float runningSum = 0.f;
	size_t i = 0;
	for (i = 0; ; i++)
	{
		runningSum += score[i];
		if (runningSum >= chosenOne)
		{
			// copy score[i] and mutate with mutability
			score[i];
		}
	}
	
}

// Called every frame
void AGameLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

