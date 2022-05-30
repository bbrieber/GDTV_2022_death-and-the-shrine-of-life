// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageListener.h"
#include "DeathPlayerController.h"
#include "EbrMontageListener.h"
#include "Equipment.h"
#include "MeleeCombatAttacker.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class GDTV_JAM_2022_API AMainCharacter : public ACharacter,public  IMeleeCombatAttacker, public IDamageListener, public IEbrMontageListener
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


	/** Combat Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* MeleeAttackBox;
	
	
	/** Combat Components */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	// class UStaticMeshComponent* RightHandItem;
	UPROPERTY(EditDefaultsOnly,Category = Combat)
	TSubclassOf<class AEquipment> RightHandEquipmentClass;
	
	UPROPERTY()
	class AEquipment* RightHandItem;


	/** Interaction Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* InteractBox;
	
	UPROPERTY(EditAnywhere, Category="Death")
	float RotationRate = 70;
	
	UPROPERTY(EditAnywhere, Category="Death")
	float SpeedFactor = 1;

	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	
	void TurnAtRate(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpAtRate(float AxisValue);



	void StartTargeting();
	void StopTargeting();
	void StartSprint();
	void StopSprint();
	void StartSlow();
	void EscapeAction();

	void OnAttack();



	void QuitAction();
	

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Death")
	 class UAnimMontage* AttackMontage;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Death")
	class UAnimMontage* HitMontage;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Death")
	class UAnimMontage* DeathMontage;
	
	
	
	UPROPERTY(EditAnywhere, Category="Death")
	float WalkMaxSpeedFactor = .2;
	
	UPROPERTY(EditAnywhere, Category="Death")
	float NormalMaxSpeedFactor = .6;

	UPROPERTY(EditAnywhere, Category="Death")
	float SprintSpeedFactor = 1;

	UPROPERTY(EditAnywhere, Category="Death")
	float NormalCameraDistance = 400;

	UPROPERTY(EditAnywhere, Category="Death")
	float SprintCameraDistance = 900;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Death")
	uint8 IsSprinting = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Death")
	uint8 IsSlow = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Death")
	uint8 IsTargeting = false;


	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Death")
	uint8 IsDead = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,  Category = "Death")
	class UHealthComponent *HealthComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,  Category = "Death")
	class UInteractionComponent *InteractionComponent;
	
	void ActivateMeleeBox(uint8 state);


	virtual void OnMeleeTriggerActivate_Implementation() override;
	virtual void OnMeleeTriggerDeactivate_Implementation() override;
	virtual void OnMeleeAttackEnd_Implementation() override;

	void BlockInput();
	void FreeInput();

	bool InputBlocked = false; 

	UFUNCTION()
	void OnMeleeCombatComponentOverlap( UPrimitiveComponent* SourceComp,AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  ;


public:
	virtual void OnHit_Implementation() override;
	virtual void OnDeath_Implementation() override;


	void AttachController();
	void DettachController();

	virtual void FellOutOfWorld(const UDamageType& dmgType) override;

	
	virtual void OnBlockingMontageEnd_Implementation() override;
private:
	void SetSpeed();
	float CameraDistance = 400;

	UPROPERTY()
	ADeathPlayerController *DeathPlayerController;
};
