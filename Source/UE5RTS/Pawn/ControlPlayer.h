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
	virtual void Tick(float DeltaTime) override;

public:
	AControlPlayer();

};
