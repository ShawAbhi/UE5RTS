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
	// Calculate the snapped position in world space
	FVector SnappedLocation;
	SnappedLocation.X = FMath::RoundToInt(Location.X / 100.0f) * 100.0f;
	SnappedLocation.Y = FMath::RoundToInt(Location.Y / 100.0f) * 100.0f;
	SnappedLocation.Z = FMath::RoundToInt(Location.Z / 100.0f) * 100.0f + ZOffset;

	// Adjust for the target's size to align its edges with the grid cells
	SnappedLocation.X -= FMath::Fmod(BoundsExtent.X, 100.0f);
	SnappedLocation.Y -= FMath::Fmod(BoundsExtent.Y, 100.0f);
	SnappedLocation.Z -= FMath::Fmod(BoundsExtent.Z, 100.0f);

	return SnappedLocation;
}
