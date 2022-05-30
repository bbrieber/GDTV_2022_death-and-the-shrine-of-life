// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraActor.h"

#include "Kismet/GameplayStatics.h"

void ADeathPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
		RemoveHudWidget();
	UUserWidget *Screen;
	if(bIsWinner)
	{
		Screen =CreateWidget(this,WinWidgetClass);
	}
	else
	{
		Screen =CreateWidget(this,LooseWidgetClass);
	}
	if(Screen){
		Screen->AddToViewport();
		SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this,Screen);
	}
}

void ADeathPlayerController::OpenStartGameMenu()
{
	TArray<AActor*> Cameras;
	ACameraActor *CameraActor;
	UGameplayStatics::GetAllActorsWithTag(this,TEXT("StartGameMenuCam"),Cameras);
	if(Cameras.Num()>= 1)
	{
		CameraActor = Cast<ACameraActor>(Cameras[0]);
	
		if(CameraActor)
		{
			SetViewTarget(CameraActor);			
		}else
		{
			UE_LOG(LogTemp,Warning,TEXT("Camera Cast Failed"));
			
		}
	}else
	{
		UE_LOG(LogTemp,Warning,TEXT("No Camera Found"));
	}
	
	StartGameScreen = CreateWidget(this,MainMenuClass);
	if(StartGameScreen){
		StartGameScreen->AddToViewport();
		SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this,StartGameScreen);
	}else
	{
		UE_LOG(LogTemp,Warning,TEXT("No MainMenuClass Found"));
		
	}
}

void ADeathPlayerController::CloseStartGameMenu()
{


	
	if(StartGameScreen){
		StartGameScreen->RemoveFromViewport();
		SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	}
	
		UE_LOG(LogTemp,Warning,TEXT("HudWidget"));
	AddHudWidget();
	
	Possess(GetPawn());
}


void ADeathPlayerController::OpenPauseMenu()
{

	RemoveHudWidget();
	PauseGameScreen = CreateWidget(this,PauseMenuClass);
	if(PauseGameScreen){
		PauseGameScreen->AddToViewport();
		SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this,PauseGameScreen);
	}
}

void ADeathPlayerController::ClosePauseMenu()
{
	if(PauseGameScreen){
		PauseGameScreen->RemoveFromViewport();
		SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	}
	AddHudWidget();
	
}

void ADeathPlayerController::AddHudWidget()
{
	
	HudWidget = CreateWidget(this,HudWidgetClass);
	if(HudWidget){
		HudWidget->AddToViewport();
	}
}

void ADeathPlayerController::RemoveHudWidget()
{
	if(HudWidget){
		HudWidget->RemoveFromViewport();
	}
}

void ADeathPlayerController::TriggerRestart()
{
	RestartLevel();
}
