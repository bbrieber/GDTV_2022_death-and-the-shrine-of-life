// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MeleeCombatAttacker.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMeleeCombatAttacker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GDTV_JAM_2022_API IMeleeCombatAttacker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void MeleeAttack();
	virtual void MeleeAttack_Implementation();
	
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	uint8 IsInAttackRange();
	virtual uint8 IsInAttackRange_Implementation();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	uint8 CanAttack();
	virtual uint8 CanAttack_Implementation();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnMeleeTriggerActivate();
	virtual void OnMeleeTriggerActivate_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnMeleeTriggerDeactivate();
	virtual void OnMeleeTriggerDeactivate_Implementation();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnMeleeAttackEnd();
	virtual void OnMeleeAttackEnd_Implementation();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnMeleeAttackComboStart();
	virtual void OnMeleeAttackComboStart_Implementation();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnMeleeAttackComboEnd();
	virtual void OnMeleeAttackComboEnd_Implementation();
};
