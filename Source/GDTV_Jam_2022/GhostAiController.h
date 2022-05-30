// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GhostAiController.generated.h"

/**
 * 
 */
UCLASS()
class GDTV_JAM_2022_API AGhostAiController : public AAIController
{
	GENERATED_BODY()


public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	class APawn *PlayerPawn;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float followAccepptanceRadiius = 200;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	class UBehaviorTree *BehaviorTree;

};
