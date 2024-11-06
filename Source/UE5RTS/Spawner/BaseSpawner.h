// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"

UCLASS()
class UE5RTS_API ABaseSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	static void SnapToGrid(UObject* TargetObject, float ZOffset = 0.0f);

	UFUNCTION(BlueprintPure, Category = "Spawner")
	FVector SnapLocationToGrid(const FVector& Location, const FVector& BoundsExtent, float ZOffset = 0.0f);

public:
	ABaseSpawner();
};
