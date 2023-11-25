// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelUpComponent.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
ULevelUpComponent::ULevelUpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void ULevelUpComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void ULevelUpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULevelUpComponent::AddXP(int value) {
	currentXP += value;
	if (currentXP >= maxXP) {
		CheckLevelUpStatus();
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Current XP: %d"), currentXP);
	UE_LOG(LogTemp, Warning, TEXT("XP increase value: %d"), value);
}

void ULevelUpComponent::CheckLevelUpStatus() {
	if (currentXP >= maxXP) {
		/*
		*Increment level number
		* subtract max XP from current XP
		* increase max XP boundary by doubling previous boundary
		*/
		levelNumber++;
		currentXP -= maxXP; 
		maxXP = (maxXP * 2); 
	}
}

int ULevelUpComponent::GetCurrentXP() const {
	return currentXP;
}

int ULevelUpComponent::GetCurrentLevel() const {
	return levelNumber;
}

int ULevelUpComponent::GetMaxXP() const {
	return maxXP;
}

