// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CapsulePawn.generated.h"

UCLASS()
class GDTV_JAM_2022_API ACapsulePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACapsulePawn();

protected:
public:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComp;

};
