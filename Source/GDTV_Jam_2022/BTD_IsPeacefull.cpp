// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_IsPeacefull.h"

#include "AIController.h"
#include "Ghost.h"

bool UBTD_IsPeacefull::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if(! OwnerComp.GetAIOwner())
	{	
		return false;		
	}
	
	APawn * ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(! ownerPawn)
	{	
		return false;		
	}
	AGhost* Ghost = Cast<AGhost>(ownerPawn);
	return Ghost->IsPeacefull? true :false;
	
}
