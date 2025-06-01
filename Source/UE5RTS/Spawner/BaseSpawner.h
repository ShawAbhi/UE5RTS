// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"

UCLASS()
class UE5RTS_API ABaseSpawner : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
	float GridStep{100.0f};
	
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	static void SnapToGrid(UObject* TargetObject, float ZOffset = 0.0f);

	UFUNCTION(BlueprintPure, Category = "Spawner")
	FVector SnapScaleToGrid(const FVector& Scale);
	
	UFUNCTION(BlueprintPure, Category = "Spawner")
	FVector SnapLocationToGrid(const FVector& Location, const FVector& BoundsExtent, float ZOffset = 0.0f);

	UFUNCTION(BlueprintPure, Category = "Spawner")
	FVector GetTouchToZWorld(const FVector2D& ScreenPosition, float TargetZHeight = 0.0f);

	UFUNCTION(BlueprintPure, Category = "Spawner")
	void GetOppositeDirectionVector(const FHitResult& HitResult, FVector& DirectionVector);

public:
	ABaseSpawner();
	UFUNCTION(BlueprintCallable, Category = "JSON")
	static FString InstancedStructToJsonString(const FInstancedStruct& Struct);
	UFUNCTION(BlueprintCallable, Category = "JSON")
	static FString InstancedStructArrayToJsonString(const TArray<FInstancedStruct>& Structs);
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	static bool JsonStringToInstancedStructArray(
		const FString& JsonString,
		TArray<FInstancedStruct>& OutStructs,
		UScriptStruct* TargetScriptStruct
	);
};
