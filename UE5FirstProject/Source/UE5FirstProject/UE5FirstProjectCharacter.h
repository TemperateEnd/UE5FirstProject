// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "LevelUpComponent.h"
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

	//Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	//LevelUpComponent class
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelUp")
	class ULevelUpComponent* LevelUpComponentClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//handles firing projectiles
	UFUNCTION()
	void Fire();

	//Test function for adding XP
	UFUNCTION()
	void AddXP();

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

	//FPS Camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	//First-person mesh (arms), visible only to owning player
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* FPSMesh;

	//Projectile spawn point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector ProjectileSpawn;
};
