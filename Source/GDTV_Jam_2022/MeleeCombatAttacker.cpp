// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeCombatAttacker.h"


void IMeleeCombatAttacker::MeleeAttack_Implementation()
{
}

uint8 IMeleeCombatAttacker::IsInAttackRange_Implementation()
{
	return false;
}

uint8 IMeleeCombatAttacker::CanAttack_Implementation()
{
	return false;
}

void IMeleeCombatAttacker::OnMeleeTriggerActivate_Implementation()
{
	
}

void IMeleeCombatAttacker::OnMeleeTriggerDeactivate_Implementation()
{
}

// Add default functionality here for any IMeleeCombatAttacker functions that are not pure virtual.
void IMeleeCombatAttacker::OnMeleeAttackEnd_Implementation()
{
}

void IMeleeCombatAttacker::OnMeleeAttackComboStart_Implementation()
{
}

void IMeleeCombatAttacker::OnMeleeAttackComboEnd_Implementation()
{
}
