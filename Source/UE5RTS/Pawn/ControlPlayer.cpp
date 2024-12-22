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



