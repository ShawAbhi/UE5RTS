// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalUtilityFunctions.generated.h"

/**
 * 
 */
UCLASS()
class UE5RTS_API UGlobalUtilityFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Global Utility Functions")
	static bool GetIsEditor();
};
