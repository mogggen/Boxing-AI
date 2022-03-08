// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boxer.h"
#include "GameLogic.generated.h"

UCLASS()
class BOXERAI_API AGameLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameLogic();
	
	UPROPERTY(EditAnywhere)
	unsigned int timePerRound = 20;

	float timeElapsedThisRound = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartBatch(const unsigned int batchSize);

	UFUNCTION(BlueprintCallable)
	void StartMatch();

	UFUNCTION(BlueprintCallable)
	void EndMatch();

	void NaturalSelection(const float mortality=.5f, const float mutability=0.01f);
};
