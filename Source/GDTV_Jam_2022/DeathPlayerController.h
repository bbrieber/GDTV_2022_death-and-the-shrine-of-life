// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DeathPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GDTV_JAM_2022_API ADeathPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

	UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> LooseWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinWidgetClass;
	
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	FTimerHandle RestartTImer;

	UFUNCTION(BlueprintCallable)
	void OpenStartGameMenu();


	
	UFUNCTION(BlueprintCallable)
	void CloseStartGameMenu();


	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainMenuClass;


	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PauseMenuClass;

	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HudWidgetClass;
	
	UFUNCTION(BlueprintCallable)
	void OpenPauseMenu();
	
	UFUNCTION(BlueprintCallable)
	void ClosePauseMenu();


	UFUNCTION(BlueprintCallable)
	void AddHudWidget();


	UFUNCTION(BlueprintCallable)
	void RemoveHudWidget();
	
	UFUNCTION(BlueprintCallable)
	void TriggerRestart();


	
private:
	UPROPERTY()
	UUserWidget *StartGameScreen;
	UPROPERTY()
	UUserWidget *PauseGameScreen;
	UPROPERTY()
	UUserWidget *DialogWidget;
	UPROPERTY()
	UUserWidget *HudWidget;
};
