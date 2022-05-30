// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GDTV_Jam_2022GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GDTV_JAM_2022_API AGDTV_Jam_2022GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

UPROPERTY(EditAnywhere)
	FString SpawnName;
UPROPERTY(EditAnywhere)
	int32 SpawnPrio;

	
	virtual void PawnKilled(APawn *pawn);
	
	UFUNCTION(BlueprintCallable)
	void ActivateSpawnPoint(FString Name, int32 Prio);

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;


	
	UPROPERTY()
	int32 AltarsToActivate = 4;

	UPROPERTY()
	int32 AltarsActivated = 0;

	UFUNCTION(BlueprintCallable)
	void ActivateMainShrine();
	UFUNCTION(BlueprintCallable)
	void ActivateAltar();

	

	
	UFUNCTION(BlueprintCallable)
	void ReachedSourceOfLife();
};
