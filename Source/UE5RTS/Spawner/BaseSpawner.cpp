// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpawner.h"


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
	SnappedLocation.X = FMath::RoundToInt(Location.X / GridStep) * GridStep;
	SnappedLocation.Y = FMath::RoundToInt(Location.Y / GridStep) * GridStep;
	//SnappedLocation.Z = FMath::RoundToInt(Location.Z / GridStep) * GridStep + ZOffset;
	SnappedLocation.Z = ZOffset;

	// Adjust for the target's size to align its edges with the grid cells
	SnappedLocation.X -= FMath::Fmod(BoundsExtent.X, GridStep);
	SnappedLocation.Y -= FMath::Fmod(BoundsExtent.Y, GridStep);
	SnappedLocation.Z -= FMath::Fmod(BoundsExtent.Z, GridStep);

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