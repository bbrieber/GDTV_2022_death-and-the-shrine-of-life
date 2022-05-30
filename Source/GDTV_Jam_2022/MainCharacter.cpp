// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "GDTV_Jam_2022GameModeBase.h"
#include "HealthComponent.h"
#include "InteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	
	
	MeleeAttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeAttackBox"));
	MeleeAttackBox->SetupAttachment(RootComponent);

	
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	InteractBox->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetSpeed();

	DeathPlayerController = Cast<ADeathPlayerController>(GetController());
	if(!DeathPlayerController)
	{
		UE_LOG(LogTemp,Error,TEXT("DeathPlayerController Not Assigned as main Controller"));
	}
	
	RightHandItem = GetWorld()->SpawnActor<AEquipment>(RightHandEquipmentClass);
	RightHandItem->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("Right_Hand_Socket"));


	RightHandItem->SetOwner(this);
	MeleeAttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeAttackBox->OnComponentBeginOverlap.AddDynamic(this, & AMainCharacter::OnMeleeCombatComponentOverlap);

	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float camDistance = CameraBoom->TargetArmLength  - CameraDistance;
	if(camDistance>10)
	{
		CameraBoom->TargetArmLength = FMath::Lerp(
		CameraBoom->TargetArmLength,
		CameraDistance,
		2  *GetWorld()->GetDeltaSeconds()
			);
	}
	if(camDistance< -10)
	{
		CameraBoom->TargetArmLength = FMath::Lerp(
		CameraBoom->TargetArmLength,
		CameraDistance,
		2 *GetWorld()->GetDeltaSeconds()
			);
	}

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("TurnRight", this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRightRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);
	// PlayerInputComponent->BindAction("Target", IE_Pressed,this, &AMainCharacter::StartTargeting);
	// PlayerInputComponent->BindAction("Target", IE_Released,this, &AMainCharacter::StopTargeting);
	// PlayerInputComponent->BindAction("Sprint", IE_Pressed,this, &AMainCharacter::StartSprint);
	// PlayerInputComponent->BindAction("Sprint", IE_Released,this, &AMainCharacter::StopSprint);
	// PlayerInputComponent->BindAction("Slow", IE_Pressed,this, &AMainCharacter::StartSlow);
	// PlayerInputComponent->BindAction("Slow", IE_Released,this, &AMainCharacter::EscapeAction);
	PlayerInputComponent->BindAction("Escape", IE_Pressed,this, &AMainCharacter::QuitAction);


	PlayerInputComponent->BindAction("Attack", IE_Pressed,this, &AMainCharacter::OnAttack);

	CameraBoom->TargetArmLength = CameraDistance;

	StartTargeting();
	

}

void AMainCharacter::MoveForward(float AxisValue)
{
	
	if(!IsTargeting)
	{
		if ((Controller != nullptr) && (AxisValue != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, AxisValue*SpeedFactor);
		}		
	}
	else
	{
		AddMovementInput(GetActorForwardVector(), AxisValue*SpeedFactor);
		
	}
}

void AMainCharacter::MoveRight(float AxisValue)
{
	if(!IsTargeting)
	{
		if ((Controller != nullptr) && (AxisValue != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
		
			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, AxisValue*SpeedFactor);
		}		
	}
	else
	{
		AddMovementInput(GetActorRightVector() , AxisValue*SpeedFactor);			
	}
}

void AMainCharacter::TurnAtRate(float AxisValue)
{
	AddControllerYawInput(AxisValue*RotationRate*GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AMainCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AMainCharacter::LookUpAtRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue*RotationRate*GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::StartTargeting()
{
	IsTargeting = true;
	bUseControllerRotationYaw = true;
	//GetCharacterMovement()->SetJumpAllowed(false);
	CameraDistance = NormalCameraDistance;
	SetSpeed();
}

void AMainCharacter::StopTargeting()
{
	IsTargeting = false;
	//if(!IsAiming) 
	{
		bUseControllerRotationYaw = false;
		
	}
	//GetCharacterMovement()->SetJumpAllowed(true);
	SetSpeed();
}

void AMainCharacter::StartSprint()
{
	IsSprinting = true;
	SetSpeed();
}

void AMainCharacter::StopSprint()
{
	IsSprinting = false;
	SetSpeed();
}

void AMainCharacter::StartSlow()
{
	IsSlow = true;
	SetSpeed();
}

void AMainCharacter::EscapeAction()
{
	IsSlow = false;
	SetSpeed();
}

void AMainCharacter::OnAttack()
{
	if(!AttackMontage)
	{
		return;
	}
	if(InputBlocked)
	{
		return;
	}
	BlockInput();
	PlayAnimMontage(AttackMontage,1);
}

void AMainCharacter::QuitAction()
{
	DeathPlayerController->OpenPauseMenu();
	
	/*
	UKismetSystemLibrary::QuitGame(this,
		nullptr,
		EQuitPreference::Quit,
		false);*/
}

void AMainCharacter::ActivateMeleeBox(uint8 state)
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

void AMainCharacter::OnMeleeTriggerActivate_Implementation()
{	UE_LOG(LogTemp,Warning,TEXT("Activating Trigger"));
	ActivateMeleeBox(true);

}

void AMainCharacter::OnMeleeTriggerDeactivate_Implementation()
{	UE_LOG(LogTemp,Warning,TEXT("Deactivating Trigger"));
	ActivateMeleeBox(false);
}

void AMainCharacter::OnMeleeAttackEnd_Implementation()
{
	
	FreeInput();
}

void AMainCharacter::BlockInput()
{
	GetCharacterMovement()->SetJumpAllowed(false);
//	GetCharacterMovement()->SetMovementMode(MOVE_None);
	InputBlocked = true;
	UE_LOG(LogTemp,Warning,TEXT("Blocking Input"));
}

void AMainCharacter::FreeInput()
{
	GetCharacterMovement()->SetJumpAllowed(true);
//	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	InputBlocked = false;
	UE_LOG(LogTemp,Warning,TEXT("Release Input Block"));
}

void AMainCharacter::OnMeleeCombatComponentOverlap(UPrimitiveComponent* SourceComp, AActor* OtherActor,
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

void AMainCharacter::OnHit_Implementation()
{
	if(!HitMontage)
	{
		return;
	}
	BlockInput();
	PlayAnimMontage(HitMontage,1);
}

void AMainCharacter::OnDeath_Implementation()
{
	/*
	if(!DeathMontage)
	{
		return;
	}
	PlayAnimMontage(DeathMontage,1);
	*/
	AGDTV_Jam_2022GameModeBase *mode = GetWorld()->GetAuthGameMode<AGDTV_Jam_2022GameModeBase>();
	if(mode)
	{
		mode->PawnKilled(this);
	}
	IsDead = true;

	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AMainCharacter::AttachController()
{
}

void AMainCharacter::DettachController()
{
}

void AMainCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	OnDeath_Implementation();
//	Super::FellOutOfWorld(dmgType);
}

void AMainCharacter::OnBlockingMontageEnd_Implementation()
{
	FreeInput();
}

void AMainCharacter::SetSpeed()
{
	if(IsSlow)
	{
		SpeedFactor = WalkMaxSpeedFactor;
		CameraDistance = NormalCameraDistance;
		return;
	}
	if(IsSprinting)
	{
		SpeedFactor = SprintSpeedFactor;
		CameraDistance = SprintCameraDistance;
		return;
	}
	SpeedFactor = NormalMaxSpeedFactor;		
	CameraDistance = NormalCameraDistance;
	
}

