// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttack_AnimNotifyState.h"

#include "MeleeCombatAttacker.h"

void UMeleeAttack_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float TotalDuration)
{
	AActor *Owner = MeshComp->GetOwner();
	
	IMeleeCombatAttacker* Attacker = Cast<IMeleeCombatAttacker>(Owner);
	if(!Attacker)
	{
		UE_LOG(LogTemp,Error,TEXT("MeleeNotify Invalid owner"));
		return;
	}
	UE_LOG(LogTemp,Warning,TEXT("MeleeNotify Begin is called"));
	Attacker->Execute_OnMeleeTriggerActivate(Owner);
}

void UMeleeAttack_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	
	AActor *Owner = MeshComp->GetOwner();
	IMeleeCombatAttacker* Attacker = Cast<IMeleeCombatAttacker>(Owner);
	if(!Attacker)
	{
		UE_LOG(LogTemp,Error,TEXT("MeleeNotify Invalid owner"));
		return;
		
	}
	UE_LOG(LogTemp,Warning,TEXT("MeleeNotify END is called"));
	Attacker->Execute_OnMeleeTriggerDeactivate(Owner);
}
