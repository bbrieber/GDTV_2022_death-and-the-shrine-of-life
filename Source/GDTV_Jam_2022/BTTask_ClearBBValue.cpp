// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBBValue.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBBValue::UBTTask_ClearBBValue()
{
	NodeName = TEXT("Clear BB Value");
}

EBTNodeResult::Type UBTTask_ClearBBValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		
	return EBTNodeResult::Type::Succeeded;
}
