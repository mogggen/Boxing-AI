// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	// Head
	UPROPERTY(EditAnywhere)
	FVector headVelocity;

	UFUNCTION(BlueprintCallable)
	void SetHeadVelocity(FVector);


	// Torso
	UPROPERTY(EditAnywhere)
	FVector upperTorsoVelocity;

	UFUNCTION(BlueprintCallable)
	void SetUpperTorsoVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector middleTorsoVelocity;

	UFUNCTION(BlueprintCallable)
	void SetMiddleTorsoVelocity(FVector);

	
	UPROPERTY(EditAnywhere)
	FVector lowerTorsoVelocity;

	UFUNCTION(BlueprintCallable)
	void SetLowerTorsoVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector hipVelocity;

	UFUNCTION(BlueprintCallable)
	void SetHipVelocity(FVector);


	// Left Arm
	UPROPERTY(EditAnywhere)
	FVector leftShoulderVelocity;

	UFUNCTION(BlueprintCallable)
	void SetLeftShoulderVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector leftUpperArmVelocity;

	UFUNCTION(BlueprintCallable)
	void SetleftUpperArmVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector leftForeArmVelocity;

	UFUNCTION(BlueprintCallable)
	void SetLeftForeArmVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector leftGlove;

	UFUNCTION(BlueprintCallable)
	void SetLeftGlove(FVector);



	// Left Leg
	UPROPERTY(EditAnywhere)
	FVector leftUpperLegVelocity;

	UFUNCTION(BlueprintCallable)
	void SetLeftUpperLegVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector leftLowerLegVelocity;

	UFUNCTION(BlueprintCallable)
	void SetLeftLowerLegVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector LeftFootVelocity;

	UFUNCTION(BlueprintCallable)
	void SetLowerTorsoVelocity(FVector);


	// Right Arm
	UPROPERTY(EditAnywhere)
	FVector rightShoulderVelocity;

	UFUNCTION(BlueprintCallable)
	void SetRightShoulderVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector rightUpperArmVelocity;

	UFUNCTION(BlueprintCallable)
	void SetUpperArmVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector rightForeArmVelocity;

	UFUNCTION(BlueprintCallable)
	void SetRightForeArmVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector rightGloveVelocity;

	UFUNCTION(BlueprintCallable)
	void SetRightGloveVelocity(FVector);



	// Right Leg
	UPROPERTY(EditAnywhere)
	FVector rightUpperLegVelocity;

	UFUNCTION(BlueprintCallable)
	void SetRightUpperLegVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector rightLowerLegVelocity;

	UFUNCTION(BlueprintCallable)
	void SetRightLowerLegVelocity(FVector);


	UPROPERTY(EditAnywhere)
	FVector rightFoot;

	UFUNCTION(BlueprintCallable)
	void SetRightFootVelocity(FVector);
};


