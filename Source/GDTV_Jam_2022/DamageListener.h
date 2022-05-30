// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageListener.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDamageListener : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GDTV_JAM_2022_API IDamageListener
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnHit();
	virtual void OnHit_Implementation();
	
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnDeath();
	virtual void OnDeath_Implementation();
};
