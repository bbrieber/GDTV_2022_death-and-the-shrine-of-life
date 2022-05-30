// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "InteractionComponent.generated.h"

/**
 * 
 */
UCLASS()
class GDTV_JAM_2022_API UInteractionComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* InteractBox;
	
};
