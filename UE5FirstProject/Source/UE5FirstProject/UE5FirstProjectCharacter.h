// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE5FirstProjectCharacter.generated.h"

UCLASS()
class UE5FIRSTPROJECT_API AUE5FirstProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUE5FirstProjectCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//handles movement along z-axis
	UFUNCTION()
	void MoveForward(float value);

	//handles movement along x-axis
	UFUNCTION()
	void MoveRight(float value);

	//Set jump flag on key-press
	UFUNCTION()
	void StartJump();

	//Clear jump flag on key-release
	UFUNCTION()
	void StopJump();
};
