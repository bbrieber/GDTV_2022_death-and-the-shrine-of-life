// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_DistanceToPlayer.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"

bool UBTD_DistanceToPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0 );
	if(!PlayerPawn){
		return false;
	}

	float DistanceToPlayer = FVector::Distance(ownerPawn->GetActorLocation(),PlayerPawn->GetActorLocation());


	UE_LOG(LogTemp,Warning,TEXT("WTF is the distance here %f"),DistanceToPlayer);
	return Distance > DistanceToPlayer;
	
}
