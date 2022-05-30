// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "DamageListener.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamageTaken);

	// ...
}


void UHealthComponent::OnDamageTaken(AActor* damagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	
	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("HEALTH: %f "), Health);

	if (Health <= 0.f) {
		
		UE_LOG(LogTemp, Error, TEXT("HealthUnder0"));
		IDamageListener* dmgListener = Cast<IDamageListener>(GetOwner());
		if(dmgListener)
		{
			dmgListener->Execute_OnDeath(GetOwner());
		}
		OnNoHealth();
	}else
	{
		IDamageListener* dmgListener = Cast<IDamageListener>(GetOwner());
		if(dmgListener)
		{
			dmgListener->Execute_OnHit(GetOwner());
		}
		
		OnHit();
	}
	
	OnHealthChanged(Health/MaxHealth);
}

void UHealthComponent::AddHealth(float HealthAmount)
{
	
	Health = FMath::Clamp(Health + HealthAmount,0,MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("HEALTH: %f "), Health);

	if (Health <= 0.f) {
		
		UE_LOG(LogTemp, Error, TEXT("HealthUnder0"));
		OnNoHealth();
				
	}
	
}


