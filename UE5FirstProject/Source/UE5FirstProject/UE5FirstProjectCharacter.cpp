// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5FirstProjectCharacter.h"

// Sets default values
AUE5FirstProjectCharacter::AUE5FirstProjectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create first person camera component
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	check(FPSCameraComponent != nullptr);

	//Attach camera component to capsule component
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	//Position camera slightly above eyes
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	//Enable pawn to control camera rotation
	FPSCameraComponent->bUsePawnControlRotation = true;

	//Create FPS Mesh component for owning player
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	//Only owning player sees this mesh
	FPSMesh->SetOnlyOwnerSee(true);

	//Attach FPS mesh to FPS camera
	FPSMesh->SetupAttachment(FPSCameraComponent);

	//Disable environmental shadows to preserve illusion of single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//Stops player from seeing third-person mesh
	GetMesh()->SetOwnerNoSee(true);
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

	//Set up movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AUE5FirstProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUE5FirstProjectCharacter::MoveRight);

	//Set up looking bindings
	PlayerInputComponent->BindAxis("Turn", this, &AUE5FirstProjectCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AUE5FirstProjectCharacter::AddControllerPitchInput);

	//Set up "action" bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUE5FirstProjectCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AUE5FirstProjectCharacter::StopJump);
}

//handles movement backwards/forwards
void AUE5FirstProjectCharacter::MoveForward(float value) {
	//Find which way is forward and then record that player wants to move forward
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

//handles movement left/right
void AUE5FirstProjectCharacter::MoveRight(float value) {
	//Find which way is right and then record that player wants to move right
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

//Sets jump flag
void AUE5FirstProjectCharacter::StartJump() {
	bPressedJump = true;
}

//Clears jump flag
void AUE5FirstProjectCharacter::StopJump() {
	bPressedJump = false;
}