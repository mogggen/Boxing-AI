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

void ABoxer::SetHeadVelocity(FVector _headVelocity)
{
	headVelocity = _headVelocity;
}

void ReadPhysicsProperties(float* Velocities, FVector& centerOfMass)
{

}

// Called every frame
void ABoxer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//print("Problem?");
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("the heads velocity in the X-axis is %f"), headVelocity.X));
}

