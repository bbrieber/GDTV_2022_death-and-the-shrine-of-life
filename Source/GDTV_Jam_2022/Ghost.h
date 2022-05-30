// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageListener.h"
#include "MeleeCombatAttacker.h"
#include "GameFramework/Character.h"
#include "Ghost.generated.h"

UCLASS()
class GDTV_JAM_2022_API AGhost : public ACharacter,public  IMeleeCombatAttacker, public IDamageListener
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	/** Combat Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* MeleeAttackBox;

	
	/** Combat Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* MeleeInAttackRangeBox;
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Death")
	class UAnimMontage* AttackMontage;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Death")
	class UAnimMontage* HitMontage;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Death")
	class UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,  Category = "Ghost")
	class UHealthComponent *HealthComponent;

	void ActivateMeleeBox(uint8 state);

	virtual void OnMeleeTriggerActivate_Implementation() override;
	virtual void OnMeleeTriggerDeactivate_Implementation() override;
	virtual void OnMeleeAttackEnd_Implementation() override;
	virtual void MeleeAttack_Implementation() override;
	virtual uint8 IsInAttackRange_Implementation() override;
	virtual uint8 CanAttack_Implementation() override;

	UFUNCTION()
	void OnMeleeCombatComponentOverlap( UPrimitiveComponent* SourceComp,AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  ;

	UFUNCTION()
	void OnInMeleeRangeComponentOverlap( UPrimitiveComponent* SourceComp,AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  ;

	UFUNCTION()
	void OnEndMeleeRangeComponentOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Death")
	uint8 IsInRange = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Death")
	uint8 IsDead = false;
	
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Death")
	uint8 CanAttack = true;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Death")
	uint8 IsTargeting = false;


	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Death")
	uint8 IsPeacefull = false;


	UFUNCTION(BlueprintImplementableEvent)
	void OnGhostDied();

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	virtual void OnHit_Implementation() override;
	virtual void OnDeath_Implementation() override;
};
