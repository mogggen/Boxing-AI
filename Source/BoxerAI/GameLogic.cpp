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
	FString path = FPaths::ProjectDir() + TEXT("Weights/") + FString::FromInt(agentId) + TEXT(".score");
	FString content = FString::SanitizeFloat(_score);
	FFileHelper::SaveStringToFile(content, *path, FFileHelper::EEncodingOptions::AutoDetect);
}

bool AGameLogic::LoadScore(float& _score)
{
	FString path = FPaths::ProjectDir() + TEXT("Weights/") + FString::FromInt(agentId) + TEXT(".score");
	FString content;
	if (FPaths::FileExists(*path))
	{
		FFileHelper::LoadFileToString(content, *path, FFileHelper::EHashOptions::None, (uint32_t)0u);
		_score = FCString::Atof(*content);
		return true;
	}
	else
	{
		return false;
	}
}

void AGameLogic::NaturalSelection(ABoxer* _handle, const float mortality, const float propability, const float mutability)
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
		if (!LoadScore(score[agentId]))
		{
			// should only happen the first time
			score[agentId] = 0.f;
		}
		
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

	// make sure the fitnessSum represents the Scores where they're non-negative values
	for (size_t i = 0; i < 40; i++)
	{
		score[i] += min;
		fitnessSum += score[i];
	}


	float theNotChosen = 0.f;
	float deathPropability[40];
	float deathSum = 0.f;
	float runningDeath = 0.f;
	bool hasDied[40];
	
	for (size_t i = 0; i < 40; i++)
	{
		hasDied[i] = false;
		deathPropability[i] = fitnessSum / score[i];
		deathSum += deathPropability[i];
	}

	int deathCount = 40 * mortality;
	for (size_t d = 0; d < deathCount; d++)
	{
		// pick a boxer whom will have their weights overwritten
		size_t j;
		theNotChosen = FMath::RandRange(0.f, deathSum);
		for (j = 0; ; j++)
		{
			if (runningDeath >= theNotChosen)
			{
				if (hasDied[j])
				{
					// start over
					j = 0;
					runningDeath = 0.f;
					theNotChosen = FMath::RandRange(0.f, deathSum);
				}
				else
				{
					// picked index j
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

	// mutate weights for all boxers by a factor mutability propabity times of the set (except king)
	for (agentId = 0; agentId < 40; agentId++)
	{
		if (score[agentId] == max) continue;
		boxer->LoadWeights(agentId);
		for (size_t i = 0; i < 12996; i++)
		{
			boxer->InputLayerToFirstHiddenLayerWeight[i] *= FMath::RandRange(-mutability, mutability);
			if (i < 6498)
				boxer->FirstHiddenLayerToSecondHiddenLayerWeight[i] *= FMath::RandRange(-mutability, mutability);
			if (i < 3249)
				boxer->SecondHiddenLayerToOutputWeight[i] *= FMath::RandRange(-mutability, mutability);
		}
		boxer->SaveWeights(agentId);
	}
	agentId = 0;
}

