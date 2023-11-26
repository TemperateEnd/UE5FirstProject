// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelUpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5FIRSTPROJECT_API ULevelUpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelUpComponent();
	
	UPROPERTY()
	int currentXP;

	UPROPERTY()
	int maxXP;

	UPROPERTY()
	int levelNumber;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Handles incrementation of XP
	UFUNCTION()
	void AddXP(int value);

	UFUNCTION() 
	void CheckLevelUpStatus();

	UFUNCTION(BlueprintCallable, Category="XP")
	int GetCurrentXP() const;

	UFUNCTION(BlueprintCallable, Category="XP")
	int GetMaxXP() const;

	UFUNCTION(BlueprintCallable, Category="Level")
	int GetCurrentLevel() const;
};
