// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpawner.h"

#include "Kismet/GameplayStatics.h"


ABaseSpawner::ABaseSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseSpawner::SnapToGrid(UObject* TargetObject, float ZOffset)
{
	// Check if the target object is valid
	if (!IsValid(TargetObject)) return;

	// Initialize variables for the location and bounds
	FVector TargetLocation;
	FVector TargetExtent;

	// Determine if the target is an actor or a component
	if (AActor* Actor = Cast<AActor>(TargetObject))
	{
		// Get the actor's location and bounds
		TargetLocation = Actor->GetActorLocation();
		TargetExtent = Actor->GetComponentsBoundingBox().GetExtent();
	}
	else if (USceneComponent* Component = Cast<USceneComponent>(TargetObject))
	{
		// Get the component's world location and bounds
		TargetLocation = Component->GetComponentLocation();
		TargetExtent = Component->Bounds.BoxExtent;
	}
	else
	{
		// Unsupported object type
		UE_LOG(LogTemp, Warning, TEXT("SnapToGrid: Unsupported object type"));
		return;
	}

	// Calculate the snapped position in world space
	FVector SnappedLocation;
	SnappedLocation.X = FMath::RoundToInt(TargetLocation.X / 100.0f) * 100.0f;
	SnappedLocation.Y = FMath::RoundToInt(TargetLocation.Y / 100.0f) * 100.0f;
	SnappedLocation.Z = FMath::RoundToInt(TargetLocation.Z / 100.0f) * 100.0f + ZOffset;

	// Adjust for the target's size to align its edges with the grid cells
	SnappedLocation.X -= FMath::Fmod(TargetExtent.X, 100.0f);
	SnappedLocation.Y -= FMath::Fmod(TargetExtent.Y, 100.0f);
	SnappedLocation.Z -= FMath::Fmod(TargetExtent.Z, 100.0f);

	// Apply the snapped location
	if (AActor* Actor = Cast<AActor>(TargetObject))
	{
		// Set actor's location directly
		Actor->SetActorLocation(SnappedLocation);
	}
	else if (USceneComponent* Component = Cast<USceneComponent>(TargetObject))
	{
		// Set the component's relative location to achieve the snap
		FVector RelativeLocation = SnappedLocation - Component->GetOwner()->GetActorLocation();
		Component->SetRelativeLocation(RelativeLocation);
	}
}

FVector ABaseSpawner::SnapLocationToGrid(const FVector& Location, const FVector& BoundsExtent, float ZOffset)
{
	// Ensure the grid step is not zero to avoid division errors
	if (GridStep <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("GridStep must be greater than 0. Returning original location."));
		return Location;
	}

	// Calculate the snapped position in world space
	FVector SnappedLocation;

	// Helper lambda to calculate the snapping logic
	auto SnapToGrid = [](float Value, float GridStep, float BoundsExtent) -> float {
		// Determine the offset based on BoundsExtent being a multiple of 50
		float Offset = FMath::RoundToFloat(BoundsExtent / 50.0f) * 50.0f;

		// Snap to the nearest grid step with the calculated offset
		float SnappedValue = FMath::RoundToFloat((Value - Offset) / GridStep) * GridStep + Offset;

		// Adjust snapping if necessary
		if (SnappedValue > Value + GridStep / 2.0f)
		{
			SnappedValue -= GridStep;
		}
		else if (Value - SnappedValue >= GridStep / 2.0f)
		{
			SnappedValue += GridStep;
		}

		return SnappedValue;
	};

	// Apply snapping logic for X and Y
	SnappedLocation.X = SnapToGrid(Location.X, GridStep, BoundsExtent.X);
	SnappedLocation.Y = SnapToGrid(Location.Y, GridStep, BoundsExtent.Y);

	// Set Z to the specified offset
	SnappedLocation.Z = ZOffset;

	return SnappedLocation;
}


FVector ABaseSpawner::SnapScaleToGrid(const FVector& Scale)
{
	// Ensure the grid step is not zero to avoid division errors
	if (GridStep <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("GridStep must be greater than 0. Returning original scale."));
		return Scale;
	}

	// Calculate the snapped scale by rounding each component to the nearest grid step
	FVector SnappedScale;
	SnappedScale.X = FMath::RoundToInt(Scale.X / GridStep) * GridStep;
	SnappedScale.Y = FMath::RoundToInt(Scale.Y / GridStep) * GridStep;
	SnappedScale.Z = FMath::RoundToInt(Scale.Z / GridStep) * GridStep;

	return SnappedScale;
}

FVector ABaseSpawner::GetTouchToZWorld(const FVector2D& ScreenPosition, float TargetZHeight)
{
	FVector WorldLocation;
	FVector WorldDirection;

	UGameplayStatics::GetPlayerController(this, 0)->DeprojectScreenPositionToWorld(
		ScreenPosition.X, ScreenPosition.Y, WorldLocation, WorldDirection);

	// Ensure the direction is not zero to avoid division by zero
	if (WorldDirection.IsZero() || FMath::IsNearlyZero(WorldDirection.Z))
	{
		UE_LOG(LogTemp, Warning, TEXT("Direction vector must not be zero. Returning StartLocation."));
		return WorldLocation;
	}

	// Calculate the difference in Z between the target height and the start location
	float ZDifference = TargetZHeight - WorldLocation.Z;

	// Compute the projected position
	return WorldLocation + WorldDirection * ZDifference / WorldDirection.Z;
}
