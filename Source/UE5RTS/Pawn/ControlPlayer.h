// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ControlPlayer.generated.h"

UCLASS()
class UE5RTS_API AControlPlayer : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Player")
	FVector2D Touch1Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control Player")
	bool bCanUpdateInertialPosition;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Control Player")
	void UpdatePlayerInertialLocation(float DeltaTime, FVector2D PreviousTouchLocation,
	                          bool bTouching = false, float MaxVelocity = 3000.0f, float Friction = 2.0f);

public:
	AControlPlayer();
};
