// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5FirstProjectCharacter.h"

// Sets default values
AUE5FirstProjectCharacter::AUE5FirstProjectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUE5FirstProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	//Display debug for 5 seconds: That's the 5.0f
	//-1 "Key" value argument stops message from being updated or refreshed
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("REECE IS AWESOME!x2"));
}

// Called every frame
void AUE5FirstProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUE5FirstProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUE5FirstProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUE5FirstProjectCharacter::MoveRight);
}

//handles z-axis movement
void AUE5FirstProjectCharacter::MoveForward(float value) {
	//Find which way is forward and then record that player wants to move forward
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AUE5FirstProjectCharacter::MoveRight(float value) {
	//Find which way is right and then record that player wants to move right
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}