// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <limits>
#include "Boxer.h"
#include "Misc/Paths.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/CString.h"
#include "Misc/FileHelper.h"
#include "Containers/UnrealString.h"
#include "GameLogic.generated.h"

UCLASS()
class BOXERAI_API AGameLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameLogic();
	
	int agentId = 0;
	FFileHelper FileHelper;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartBatch(const unsigned int batchSize);


	UFUNCTION(BlueprintCallable)
	int GetAgentId();
	
	UFUNCTION(BlueprintCallable)
	void SetAgentId(const int agentId);

	UFUNCTION(BlueprintCallable)
	void SaveScore(const float score);

	FString LoadScore();

	UFUNCTION(BlueprintCallable)
	void NaturalSelection(const float mortality=.5f, const float propability = 0.01, const float mutability=0.01f);
};
