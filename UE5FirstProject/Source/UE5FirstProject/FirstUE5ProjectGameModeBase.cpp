// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstUE5ProjectGameModeBase.h"

void AFirstUE5ProjectGameModeBase::StartPlay() {
	Super::StartPlay();

	check(GEngine != nullptr);

	//Display debug for 5 seconds: That's the 5.0f
	//-1 "Key" value argument stops message from being updated or refreshed
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("REECE IS AWESOME!"));
}