// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UBorder;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class UE5RTS_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ItemName;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UBorder* TextBorder;
	
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FSlateBrush ItemImageBrush;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FLinearColor BGColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ItemNameText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	bool bInvertLayout{false};
	
	UFUNCTION(BlueprintCallable)
	virtual void UpdateWidget();
};
