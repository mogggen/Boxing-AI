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

	UPROPERTY(EditAnywhere)
	FVector headVelocity;

	UPROPERTY(EditAnywhere)
	FVector upperTorsoVelocity;

	UFUNCTION(BlueprintCallable)
	void SetHeadVelocity(FVector _headVelocity);
};
