// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

#include "GDTV_Jam_2022GameModeBase.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AGhost::AGhost()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	MeleeAttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeAttackBox"));
	MeleeAttackBox->SetupAttachment(RootComponent);
	
	MeleeInAttackRangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeInAttackRangeBox"));
	MeleeInAttackRangeBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	
	MeleeAttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeAttackBox->OnComponentBeginOverlap.AddDynamic(this, & AGhost::OnMeleeCombatComponentOverlap);


	MeleeInAttackRangeBox->OnComponentBeginOverlap.AddDynamic(this, & AGhost::OnInMeleeRangeComponentOverlap);
	MeleeInAttackRangeBox->OnComponentEndOverlap.AddDynamic(this, & AGhost::OnEndMeleeRangeComponentOverlap);



}

void AGhost::ActivateMeleeBox(uint8 state)
{
	if(!MeleeAttackBox)
	{
		return;
	}
	if(!state)
	{
		MeleeAttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}
	MeleeAttackBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

void AGhost::OnMeleeTriggerActivate_Implementation()
{
	ActivateMeleeBox(true);
}

void AGhost::OnMeleeTriggerDeactivate_Implementation()
{
	ActivateMeleeBox(false);
}

void AGhost::OnMeleeAttackEnd_Implementation()
{
	CanAttack = true;
}

void AGhost::MeleeAttack_Implementation()
{
	if(!AttackMontage)
	{
		return;
	}
	CanAttack = false;
	PlayAnimMontage(AttackMontage,1);
}

uint8 AGhost::IsInAttackRange_Implementation()
{
	return IsInRange;
}

uint8 AGhost::CanAttack_Implementation()
{
	return CanAttack;
}

void AGhost::OnMeleeCombatComponentOverlap(UPrimitiveComponent* SourceComp, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor==this)
	{
		return;
	}

	if(!OtherComp->ComponentHasTag(TEXT("DamageCollider")))
	{
		return;
		
	}
	UE_LOG(LogTemp,Warning,TEXT("Hit something %s "),*OtherActor->GetName() );
	FPointDamageEvent DmgEvent(10,SweepResult,FVector::ForwardVector,nullptr);

	OtherActor->TakeDamage(10,DmgEvent,Controller,this);
}

void AGhost::OnInMeleeRangeComponentOverlap(UPrimitiveComponent* SourceComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor==this)
	{
		return;
	}
	UE_LOG(LogTemp,Warning,TEXT("In Range ") );
	IsInRange = true;
}

void AGhost::OnEndMeleeRangeComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor==this)
	{
		return;
	}
	UE_LOG(LogTemp,Warning,TEXT("Not In Range ") );
	IsInRange = false;
}


// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGhost::OnHit_Implementation()
{
	if(!HitMontage)
	{
		return;
	}
	PlayAnimMontage(HitMontage,1);
}

void AGhost::OnDeath_Implementation()
{
	/*
	if(!DeathMontage)
	{
		return;
	}
	PlayAnimMontage(DeathMontage,1);
	*/
	//Destroy();
	AGDTV_Jam_2022GameModeBase *mode = GetWorld()->GetAuthGameMode<AGDTV_Jam_2022GameModeBase>();
	if(mode)
	{
		mode->PawnKilled(this);
	}IsDead = true;
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

