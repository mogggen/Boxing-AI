// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
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

	randomizeWeights();
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

void ABoxer::randomizeWeights()
{
	srand((unsigned int)time(NULL));

	for (size_t i = 0; i < 12996; i++)
	{
		InputLayerToFirstHiddenLayerWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
		if (i < 6498)
			FirstHiddenLayerToSecondHiddenLayerWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
		if (i < 3249)
			SecondHiddenLayerToOutputWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
	}
}



void ABoxer::CalculateOutput()
{
	float inputs[114];
	for (int i = 0; i < 114; i++)
	{
		inputs[i] = 0;
	}

	for (size_t i = 0; i < sizeof(inputs) / sizeof(*inputs); i+=6)
	{
		inputs[i] = position[i].X;
		inputs[i+1] = position[i].Y;
		inputs[i+2] = position[i].Z;
		
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
			firstWeightSum[i] += inputs[j] * InputLayerToFirstHiddenLayerWeight[i*114+j];
		}
		if (firstWeightSum[i] < 0)
			firstWeightSum[i] = 0;
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
			secondWeightSum[i] += firstWeightSum[j] * FirstHiddenLayerToSecondHiddenLayerWeight[i*57+j];
		}
		if (secondWeightSum[i] < 0)
			secondWeightSum[i] = 0;
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
			finalWeightSum[i] += secondWeightSum[j] * SecondHiddenLayerToOutputWeight[i*57+j];
		}
		if (finalWeightSum[i] < 0)
			finalWeightSum[i] = 0;
	}
	
	for (size_t i = 0; i < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); i += 3)
	{
		force[i / 3].X = finalWeightSum[i];
		force[i / 3].Y = finalWeightSum[i+1];
		force[i / 3].Z = finalWeightSum[i+2];
	}
}

// Called every frame
void ABoxer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateOutput();

	if (GEngine)
	{
		for (size_t i = 0; i < 1.9; i++)
		{
		}
	}
}

