#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ctime>
#include <fstream>
#include "Boxer.generated.h"

UCLASS()
class BOXERAI_API ABoxer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Reinforment learning
	// one game at a time
	// AI with higher scores are proportionally more likely to survive
	// The NN will mutate randomly in search of favorable mutations
	
	// landing on your head -40 points
	// landing on your Shoulder -80 points
	// landing on your gloves -30 points
	// landing on your other bodyparts -20 points

	// +1p for every second without collision
	// landing on feet +50 p (+ cm from the center of the ring)
	// landing a punch on the opponent +500 points (* ForceFactor)

	// 95 inputs (let's try with 38 inputs instead, position and velocity)
	// L-R
	//  0
	// 123
	// 456
	// 789
	// ABC
	// D E
	// F G
	// H I

	// First Layer
	// hidden neurons 2 / 3 * (114 + 57) = 114

	// Second Layer
	// hidden neurons 1 / 3 * (114 + 57) = 57
	
	// 57 outputs (from -1 to 1) * multiplied to apply a force of -1000 to 1000
	
	// Forces (output)
	UPROPERTY(EditAnywhere)
	FVector force[19];

	// Positions (input)
	UPROPERTY(EditAnywhere)
	FVector position[19];

	// Velocities (input)
	UPROPERTY(EditAnywhere)
	FVector velocity[19];

	UPROPERTY(EditAnywhere)
	float InputLayerToFirstHiddenLayerWeight[12996];

	UPROPERTY(EditAnywhere)
	float FirstHiddenLayerToSecondHiddenLayerWeight[6498];

	UPROPERTY(EditAnywhere)
	float SecondHiddenLayerToOutputWeight[3249];

	// Rotations
	// UPROPERTY(EditAnywhere)
	// FVector forwardVector[19];

	// // UPROPERTY(EditAnywhere)
	// FVector rightVector[19];

	// // UPROPERTY(EditAnywhere)
	// FVector upVector[19];

	UFUNCTION(BlueprintCallable)
	void SetPosition(const int index, const FVector _position);
	
	UFUNCTION(BlueprintCallable)
	void SetVelocity(const int index, const FVector _velocity);

	// UFUNCTION(BlueprintCallable)
	// void SetOrientationalVectors(const int index, const FVector _forwardVector, const FVector _rightVector, const FVector _upVector);

	void randomizeWeights();

	// the big mama
	void CalculateOutput();

	UFUNCTION(BlueprintCallable)
	FVector GetForce(const int index);
};


