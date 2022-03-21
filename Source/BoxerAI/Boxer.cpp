// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) \
	if (GEngine)    \
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#include "Boxer.h"

// Sets default values
ABoxer::ABoxer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoxer::BeginPlay()
{
	Super::BeginPlay();
}

void ABoxer::SetPosition(const int index, const FVector _position)
{
	position[index] = _position;
}

void ABoxer::SetVelocity(const int index, const FVector _velocity)
{
	velocity[index] = _velocity;
}

// void ABoxer::SetOrientationalVectors(const int index, const FVector _forwardVector, const FVector _rightVector, const FVector _upVector)
// {
// 	forwardVector[index] = _forwardVector;
// 	rightVector[index] = _rightVector;
// 	upVector[index] = _upVector;
// }

FVector ABoxer::GetForce(const int index)
{
	return force[index];
}


void ABoxer::RandomizeWeights()
{
	for (size_t i = 0; i < 12996; i++)
	{
		InputLayerToFirstHiddenLayerWeight[i] = FMath::RandRange(-1.f, 1.f);
		if (i < 6498)
			FirstHiddenLayerToSecondHiddenLayerWeight[i] = FMath::RandRange(-1.f, 1.f);
		if (i < 3249)
			SecondHiddenLayerToOutputWeight[i] = FMath::RandRange(-1.f, 1.f);
	}
}


void ABoxer::SaveWeights(const int agentId)
{
	size_t i;
	// Save inputs to first hidden layer weights
	FString path = FPaths::ProjectDir() + TEXT("Weights/") + FString::FromInt(agentId) + TEXT(".ih1");
	FString content = TEXT("");
	
	FFileHelper::SaveStringToFile(content, *path, FFileHelper::EEncodingOptions::AutoDetect, (uint32_t)0u);
	for (i = 0; i < sizeof(InputLayerToFirstHiddenLayerWeight) / sizeof(InputLayerToFirstHiddenLayerWeight[0]) - 1; i++)
	{
		content += FString::SanitizeFloat(InputLayerToFirstHiddenLayerWeight[i]) + LINE_TERMINATOR;
	}
	content += FString::SanitizeFloat(InputLayerToFirstHiddenLayerWeight[++i]);


	// Save first to second hidden layer weights
	path = FPaths::ProjectDir() + TEXT("Weights/") + FString::FromInt(agentId) + TEXT(".h1h2");
	content = TEXT("");
	
	FFileHelper::SaveStringToFile(content, *path, FFileHelper::EEncodingOptions::AutoDetect, (uint32_t)0u);
	for (i = 0; i < sizeof(FirstHiddenLayerToSecondHiddenLayerWeight) / sizeof(*FirstHiddenLayerToSecondHiddenLayerWeight) - 1; i++)
	{
		content += FString::SanitizeFloat(FirstHiddenLayerToSecondHiddenLayerWeight[i]) + LINE_TERMINATOR;
	}
	content += FString::SanitizeFloat(FirstHiddenLayerToSecondHiddenLayerWeight[++i]);


	// Save second hidden to output layer weights
	path = FPaths::ProjectDir() + TEXT("Weights/") + FString::FromInt(agentId) + TEXT(".h2o");
	content = TEXT("");
	
	FFileHelper::SaveStringToFile(content, *path, FFileHelper::EEncodingOptions::AutoDetect, (uint32_t)0u);
	for (i = 0; i < sizeof(SecondHiddenLayerToOutputWeight) / sizeof(*SecondHiddenLayerToOutputWeight) - 1; i++)
	{
		content += FString::SanitizeFloat(SecondHiddenLayerToOutputWeight[i]) + LINE_TERMINATOR;
	}
	content += FString::SanitizeFloat(SecondHiddenLayerToOutputWeight[++i]);
}



void ABoxer::LoadWeights(const int agentId)
{
	size_t i = 0;
	// Load inputs to first hidden layer weights
	FString path = FPaths::ProjectDir() + TEXT("Weights/") + FString::FromInt(agentId) + TEXT(".ih1");
	FString content;
	if (FPaths::FileExists(*path))
	{
		FFileHelper::LoadFileToString(content, *path, FFileHelper::EHashOptions::None, (uint32_t)0u);
		for (i = 0; i < sizeof(InputLayerToFirstHiddenLayerWeight) / sizeof(*InputLayerToFirstHiddenLayerWeight) - 1; i++)
		{
			FString strWeight;
			content.Split(LINE_TERMINATOR, &strWeight, &content);
			float weight = FCString::Atof(*strWeight);
			InputLayerToFirstHiddenLayerWeight[i] = weight;
		}
		InputLayerToFirstHiddenLayerWeight[++i] = FCString::Atof(*content);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("0-1"));
		RandomizeWeights();
	}

	// Load weights from first to second hidden layer weights
	path = FPaths::ProjectDir() + TEXT("\\Weights\\") + FString::FromInt(agentId) + TEXT(".h1h2");
	if (FPaths::FileExists(*path))
	{
		FFileHelper::LoadFileToString(content, *path, FFileHelper::EHashOptions::None, (uint32_t)0u);
		for (i = 0; i < sizeof(FirstHiddenLayerToSecondHiddenLayerWeight) / sizeof(*FirstHiddenLayerToSecondHiddenLayerWeight) - 1; i++)
		{
			FString strWeight;
			content.Split(LINE_TERMINATOR, &strWeight, &content);
			float weight = FCString::Atof(*strWeight);
			FirstHiddenLayerToSecondHiddenLayerWeight[i] = weight;
		}
		FirstHiddenLayerToSecondHiddenLayerWeight[++i] = FCString::Atof(*content);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("1-2"));
		RandomizeWeights();
	}

	// Load weights from second hidden to output layer weights
	path = FPaths::ProjectDir() + TEXT("\\Weights\\") + FString::FromInt(agentId) + TEXT(".h2o");
	if (FPaths::FileExists(*path))
	{
		FFileHelper::LoadFileToString(content, *path, FFileHelper::EHashOptions::None, (uint32_t)0u);
		for (i = 0; i < sizeof(SecondHiddenLayerToOutputWeight) / sizeof(*SecondHiddenLayerToOutputWeight) - 1; i++)
		{
			FString strWeight;
			content.Split(LINE_TERMINATOR, &strWeight, &content);
			float weight = FCString::Atof(*strWeight);
			SecondHiddenLayerToOutputWeight[i] = weight;
		}
		SecondHiddenLayerToOutputWeight[++i] = FCString::Atof(*content);
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("2-3"));
		RandomizeWeights();
	}
}

void ABoxer::CalculateOutput()
{
	float inputs[114];

	for (size_t i = 0; i < sizeof(inputs) / sizeof(*inputs); i += 6)
	{
		inputs[i] = position[i].X;
		inputs[i + 1] = position[i].Y;
		inputs[i + 2] = position[i].Z;

		inputs[19 + i] = velocity[i].X;
		inputs[19 + i + 1] = velocity[i].Y;
		inputs[19 + i + 2] = velocity[i].Z;
	}

	float firstWeightSum[114];
	for (size_t i = 0; i < 114; i++)
	{
		firstWeightSum[i] = 0;
	}

	for (size_t i = 0; i < 2 / 3.0 * ((19 * 3 + 19 * 3) + 57); i++)
	{
		for (size_t j = 0; j < 2 / 3.0 * ((19 * 3 + 19 * 3) + 57); j++)
		{
			firstWeightSum[i] += inputs[j] * InputLayerToFirstHiddenLayerWeight[i * 114 + j];
		}
	}

	float secondWeightSum[57];
	for (size_t i = 0; i < 57; i++)
	{
		secondWeightSum[i] = 0;
	}

	for (size_t i = 0; i < 2 / 3.0 * ((19 * 3 + 19 * 3) + 57); i++)
	{
		for (size_t j = 0; j < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); j++)
		{
			secondWeightSum[i] += firstWeightSum[j] * FirstHiddenLayerToSecondHiddenLayerWeight[i * 57 + j];
		}
	}

	float finalWeightSum[57];
	for (size_t i = 0; i < 57; i++)
	{
		finalWeightSum[i] = 0;
	}

	for (size_t i = 0; i < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); i++)
	{
		for (size_t j = 0; j < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); j++)
		{
			finalWeightSum[i] += secondWeightSum[j] * SecondHiddenLayerToOutputWeight[i * 57 + j];
		}
	}

	for (size_t i = 0; i < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); i += 3)
	{
		force[i / 3].X = finalWeightSum[i];
		force[i / 3].Y = finalWeightSum[i + 1];
		force[i / 3].Z = finalWeightSum[i + 2];
	}
}

// Called every frame
void ABoxer::Tick(float DeltaTime)
{
	// Calculate the output forces applied in the next physics step
	CalculateOutput();
	
	Super::Tick(DeltaTime);


	if (GEngine)
	{
	}
}
