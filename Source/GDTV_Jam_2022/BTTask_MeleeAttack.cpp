// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "AIController.h"
#include "MeleeCombatAttacker.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(! OwnerComp.GetAIOwner())
	{	
		return EBTNodeResult::Type::Failed;		
	}
	
	APawn * ownerPawn = OwnerComp.GetAIOwner()->GetPawn();


	IMeleeCombatAttacker* Attacker = Cast<IMeleeCombatAttacker>(ownerPawn);
	if(!Attacker)
	{
		return EBTNodeResult::Type::Failed;
	}
	Attacker->Execute_MeleeAttack(ownerPawn);
	
	return EBTNodeResult::Type::Succeeded;
	
}
