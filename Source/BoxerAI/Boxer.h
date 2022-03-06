#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <ctime>
#include <string>
#include <fstream>
// #define WIN32_LEAN_AND_MEAN
#include <Windows.h>
// #include <ShellAPI.h>
// #include <KnownFolders.h>
// #include <ShlObj.h>
// #include <comdef.h>
#include "Boxer.generated.h"
UCLASS()
class BOXERAI_API ABoxer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxer();

	int epoch = 0;
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
	
	// points for landing on your:
	// Head 		-40
	// Shoulder 	-80
	// Gloves 		-30
	// Torso		-20
	// Hip			-10
	// Arms			-30
	// Legs			-80
	// feets		+50 (* centimetres from the center of the ring)
	
	// punch on
	// the opponent	+500 (* ForceFactor)

	// +1p for every second without collision with floor
	// standing somewhat up right is also rewarding
	//


	// 95 inputs (let's try with 38 inputs instead, position and velocity)
	// L - R
	//   0
	// 1 2 3
	// 4 5 6
	// 7 8 9
	// A B C
	//  D E
	//  F G
	//  H I

	// First hidden Layer neurons
	//  2 / 3 * (114 + 57) = 114

	// Second hidden Layer neurons
	//  1 / 3 * (114 + 57) = 57
	
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

	void SaveProgress(const char *filename);

	bool LoadProgress(const char *filename);

	UFUNCTION(BlueprintCallable)
	FVector GetForce(const int index);
};




