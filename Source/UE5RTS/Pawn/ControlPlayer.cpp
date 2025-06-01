// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPlayer.h"


AControlPlayer::AControlPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AControlPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AControlPlayer::UpdatePlayerInertialLocation(float DeltaTime, FVector2D PreviousTouchLocation,
	bool bTouching, float MaxVelocity, float Friction)
{
	if (!bTouching && !Touch1Velocity.IsNearlyZero())
	{
		Touch1Velocity = Touch1Velocity.Length() > MaxVelocity
			                                  ? Touch1Velocity.GetSafeNormal() * MaxVelocity
			                                  : Touch1Velocity;
		// Apply movement based on velocity
		FVector Movement(Touch1Velocity.X, Touch1Velocity.Y, 0.f);
		AddActorWorldOffset(Movement * DeltaTime, true);

		// Apply friction (damp velocity)
		const float FrictionAnmount = Touch1Velocity.Length() *Friction;
		FVector2D FrictionForce = Touch1Velocity.GetSafeNormal() * FrictionAnmount * DeltaTime;
        
		if (Touch1Velocity.Size() <= FrictionForce.Size())
		{
			Touch1Velocity = FVector2D::ZeroVector;
		}
		else
		{
			Touch1Velocity -= FrictionForce;
		}
	}
	else
	{
		Touch1Velocity = FVector2D::ZeroVector;
	}
}



