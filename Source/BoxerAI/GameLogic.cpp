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
	float fitnessSum = 0.f;
	float runningSum = 0.f;
	float min = std::numeric_limits<float>::max(); // shift values by this amount
	float max = std::numeric_limits<float>::min(); // don't mutate
	int maxIndex;

	// find min and max values
	for (agentId = 0; agentId < 40; agentId++)
	{
		score[agentId] = FCString::Atof(LoadScore());
		
		if (min > score[agentId])
		{
			min = score[agentId];
		}
		if (max < score[agentId])
		{
			max = score[agentId];
			maxIndex = agentId;
		}
	}

	// make sure the fitnessSum represents the Scores when they are non-negative values
	for (size_t i = 0; i < 40; i++)
	{
		score[i] += min;
		fitnessSum += score[i];
	}


	float theNotChosen = 0.f;
	float deathPropability[40];
	float deathSum = 0.f;
	float runningDeath = 0.f;
	bool hasDied[39];
	
	for (size_t i = 0; i < 40; i++)
	{
		deathPropability[i] = fitnessSum / score[i];
		deathSum += deathPropability[i];
	}

	int deathCount = 40 * mortality;
	for (size_t d = 0; d < deathCount; d++)
	{
		// pick a boxer whom will have their weights overwritten
		size_t j;
		theNotChosen = FMath::RandRange(0, deathPropability)
		for (j = 0; ; j++)
		{
			if (runningDeath >= notNotChosen)
			{
				if (hasDied[j])
				{
					j = 0;
					runningDeath = 0.f;
					theNotChosen = FMath::RandRange(0, deathPropability);
				}
				else
				{
					break;
				}
			}
			runningDeath += deathPropability[j];
		}

		// pick which boxer to copy weights from
		float chosenOne = FMath::RandRange(0.f, fitnessSum);
		size_t i = 0;
		for (i = 0; ; i++)
		{
			if (runningSum >= chosenOne)
			{
				// copy score[i] and mutate with mutability
				score[j] = score[i];
				hasDied[j] = true;
				break;
			}
			runningSum += score[i];
		}
	}

	for (agentId = 0; agentId < 40; agentId++)
	{
		score[agentId] = FCString::Atof(LoadScore());
		for (size_t i = 0; i < 12996; i++)
		{
			InputLayerToFirstHiddenLayerWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
			if (i < 6498)
				FirstHiddenLayerToSecondHiddenLayerWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
			if (i < 3249)
				SecondHiddenLayerToOutputWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
		}

		for (i = 0; i < sizeof(SecondHiddenLayerToOutputWeight) / sizeof(SecondHiddenLayerToOutputWeight[0]) - 1; i++)
		{
			FString strWeight;
			content.Split(LINE_TERMINATOR, &strWeight, &content);
			float weight = FCString::Atof(*strWeight);
			SecondHiddenLayerToOutputWeight[i] = weight;
		}
	}
	agentId = 0;
}

// Called every frame
void AGameLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

