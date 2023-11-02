// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstUE5ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5FIRSTPROJECT_API AFirstUE5ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

	virtual void StartPlay() override;
};
