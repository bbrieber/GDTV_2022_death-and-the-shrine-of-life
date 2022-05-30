// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetAttackerValues.h"

#include "AIController.h"
#include "MeleeCombatAttacker.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_SetAttackerValues::UBTService_SetAttackerValues()
{
	NodeName = "Update Player Statistics";
}

void UBTService_SetAttackerValues::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

		APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0 );
	if(!PlayerPawn){
		return;
	}
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());

	if(! OwnerComp.GetAIOwner())
	{	
		return ;		
	}
	
	APawn * ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if(! ownerPawn)
	{	
		return ;		
	}
	IMeleeCombatAttacker* Attacker = Cast<IMeleeCombatAttacker>(ownerPawn);
	if(!Attacker)
	{		
	UE_LOG(LogTemp,Warning,TEXT("Owner %s ist not an attacker"), *ownerPawn->GetName() );
		return;
	}

	UBlackboardComponent *BBComp = OwnerComp.GetBlackboardComponent();
	if(Attacker->Execute_IsInAttackRange(ownerPawn)	)
	{
		BBComp->SetValueAsBool(TEXT("IsInAttackRange"),true);		
	UE_LOG(LogTemp,Warning,TEXT("Set In Range ") );
	}else
	{
		BBComp->SetValueAsBool(TEXT("IsInAttackRange"),false);		
	UE_LOG(LogTemp,Warning,TEXT("Set Not In Range ") );
	}

	if(Attacker->Execute_CanAttack(ownerPawn)	)
	{
		BBComp->SetValueAsBool(TEXT("CanAttack"),true);		
	}else
	{
		BBComp->SetValueAsBool(TEXT("CanAttack"),false);		
	}
	// SetFocus(PlayerPawn);
		// MoveToActor(PlayerPawn,followAccepptanceRadiius);

}
