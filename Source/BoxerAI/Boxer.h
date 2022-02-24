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
	// landing on feet +50 p (+ cm from the center of the ring)
	// landing on your other bodyparts -20 points
	// landing a punch on the opponent +500 points (* ForceFactor)

	// 95 inputs (let's try with 38 inputs instead)
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
	// hidden neurons 2 / 3 * (95 + 19)

	// Second Layer
	// hidden neurons 1 / 3 * (95 + 19)
	
	// 19 outputs (from -1 to 1) * multiplied to apply a force of -1000 to 1000
	
	// Forces
	UPROPERTY(EditAnywhere)
	FVector force[19];

	// Positions
	UPROPERTY(EditAnywhere)
	FVector position[19];

	// Velocities
	UPROPERTY(EditAnywhere)
	FVector velocity[19];

	// Rotations
	// UPROPERTY(EditAnywhere)
	FVector forwardVector[19];

	// UPROPERTY(EditAnywhere)
	FVector rightVector[19];

	// UPROPERTY(EditAnywhere)
	FVector upVector[19];

	UFUNCTION(BlueprintCallable)
	void SetPosition(const int index, const FVector _position);
	
	UFUNCTION(BlueprintCallable)
	void SetVelocity(const int index, const FVector _velocity);

	UFUNCTION(BlueprintCallable)
	void SetDirectionalVectors(const int index, const FVector _forwardVector, const FVector _rightVector, const FVector _upVector);

	UFUNCTION(BlueprintCallable)
	FVector GetForce(const int index);
};


