// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostAiController.h"

#include "VectorTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AGhostAiController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if(BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		if(!GetBlackboardComponent()){
		   UE_LOG(LogTemp,Warning,TEXT("Fuck 1") );
		   return;
        }
		if(!GetPawn()){
		   UE_LOG(LogTemp,Warning,TEXT("Fuck 2") );
		   return;
        }
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
		UE_LOG(LogTemp,Warning,TEXT("Initialized BB ") );
		
	}
}

void AGhostAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE::Geometry::Distance(GetPawn()->GetActorLocation(),PlayerPawn->GetActorLocation());
	
	if(LineOfSightTo(PlayerPawn))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),PlayerPawn->GetActorLocation());
		// SetFocus(PlayerPawn);
		// MoveToActor(PlayerPawn,followAccepptanceRadiius);
		
	}else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		
		// ClearFocus(EAIFocusPriority::Gameplay);
		// StopMovement();
		
	}
}
