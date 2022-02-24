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
	
}

void ABoxer::SetPosition(const int index, const FVector _position)
{
	position[index] = _position;
}

void ABoxer::SetVelocity(const int index, const FVector _velocity)
{
	velocity[index] = _velocity;
}

void ABoxer::SetDirectionalVectors(const int index, const FVector _forwardVector, const FVector _rightVector, const FVector _upVector)
{
	forwardVector[index] = _forwardVector;
	rightVector[index] = _rightVector;
	upVector[index] = _upVector;
}

FVector ABoxer::GetForce(const int index)
{
	return force[index];
}

// Called every frame
void ABoxer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("the heads position in the X-axis is %f"), bodyPartsPosition[0].Y));
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("the heads velocity in the X-axis is %f"), bodyPartsVelocity[0].Y));
	}
}

