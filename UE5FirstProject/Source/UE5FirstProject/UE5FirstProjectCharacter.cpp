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

	//Create LevelUpComponent component
	LevelUpComponentClass = CreateDefaultSubobject<ULevelUpComponent>(TEXT("LevelUpComponent")); 
	LevelUpComponentClass->maxXP = 100;
	LevelUpComponentClass->currentXP = 0;
	LevelUpComponentClass->levelNumber = 1;

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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUE5FirstProjectCharacter::Fire);

	PlayerInputComponent->BindAction("XPIncreaseTest", IE_Pressed, this, &AUE5FirstProjectCharacter::AddXP);
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

void AUE5FirstProjectCharacter::Fire() {
	if (ProjectileClass) {
		//Get camera transform
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//Set ProjectileSpawn to spawn projectiles slightly in front of camera
		ProjectileSpawn.Set(100.0f, 0.0f, 0.0f);

		//Transform ProjectileSpawn from camera space to world space
		FVector SpawnLocation = CameraLocation + FTransform(CameraRotation).TransformVector(ProjectileSpawn);

		//Skew aim to be slightly upwards
		FRotator SpawnRotation = CameraRotation;
		SpawnRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();

		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			//Spawn projectile at projectile spawn
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

			if (Projectile) {
				//Set initial trajectory
				FVector LaunchDirection = SpawnRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AUE5FirstProjectCharacter::AddXP() {
	LevelUpComponentClass->AddXP(15);
}