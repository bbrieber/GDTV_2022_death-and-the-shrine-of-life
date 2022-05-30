// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsulePawn.h"

#include "Components/CapsuleComponent.h"


// Sets default values
ACapsulePawn::ACapsulePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
}
