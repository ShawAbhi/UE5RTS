// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemWidget.h"
#include "ItemLevelWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5RTS_API UItemLevelWidget : public UItemWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int64 MaxValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int64 CurrentValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FLinearColor ProgressColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	UMaterialInterface* ProgressMaterial;

	virtual void UpdateWidget() override;
};
