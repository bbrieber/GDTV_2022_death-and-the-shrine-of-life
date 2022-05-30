// Fill out your copyright notice in the Description page of Project Settings.


#include "StopBlockedMovement_AnimNotify.h"

#include "EbrMontageListener.h"

void UStopBlockedMovement_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	
	AActor *Owner = MeshComp->GetOwner();
	
	IEbrMontageListener* MontageListener = Cast<IEbrMontageListener>(Owner);
	if(!MontageListener)
	{
		//UE_LOG(LogTemp,Warning,TEXT("StopBlockedMovement_AnimNotify Invalid owner"));
		return;
	}
	MontageListener->Execute_OnBlockingMontageEnd(Owner);
}
