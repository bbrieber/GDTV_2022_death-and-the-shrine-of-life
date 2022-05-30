// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class GDTV_JAM_2022_API UBTTask_MoveInAttackRange : public UBTTask_MoveTo
{
	GENERATED_BODY()

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
