// Copyright Epic Games, Inc. All Rights Reserved.


#include "GDTV_Jam_2022GameModeBase.h"

void AGDTV_Jam_2022GameModeBase::PawnKilled(APawn* pawn)
{
	APlayerController * PlayerCon = Cast<APlayerController>(pawn->GetController());
	if(PlayerCon)
	{
		PlayerCon->GameHasEnded(nullptr,false);
	}

	
	
}

void AGDTV_Jam_2022GameModeBase::ActivateMainShrine()
{

}


void AGDTV_Jam_2022GameModeBase::ActivateAltar()
{
	AltarsActivated ++;

	if(AltarsActivated== AltarsToActivate){
		ActivateMainShrine();
	}
}

void AGDTV_Jam_2022GameModeBase::ActivateSpawnPoint(FString Name, int32 Prio)
{
	SpawnName = Name;
	SpawnPrio = Prio;
	
}

AActor* AGDTV_Jam_2022GameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
		return Super::ChoosePlayerStart_Implementation(Player);
	/*AActor * spawnPoint = FindPlayerStart(Player,SpawnName);
	if(spawnPoint == nullptr)
	{
	}
	return spawnPoint;*/
}

void AGDTV_Jam_2022GameModeBase::ReachedSourceOfLife()
{
APlayerController * PlayerCon = GetWorld()->GetFirstPlayerController();
	if(PlayerCon)
	{
		PlayerCon->GameHasEnded(nullptr,true);
	}
}

