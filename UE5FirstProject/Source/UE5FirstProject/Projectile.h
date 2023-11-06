// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Projectile.generated.h"


UCLASS()
class UE5FIRSTPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	//Projectile movement component
	UPROPERTY(VisibleAnywhere, Category=Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	//Projectile mesh
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	UStaticMeshComponent* ProjectileMeshComponent;

	//Projectile material
	UPROPERTY(VisibleDefaultsOnly, Category=Movement)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

	//Function that initializes projectile velocity in shoot direction
	void FireInDirection(const FVector& ShootDirection);
};
