// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLevelWidget.h"

#include "Components/Border.h"
#include "Kismet/KismetMathLibrary.h"


void UItemLevelWidget::UpdateWidget()
{
	
	ItemNameText = FText::FromString(
		FString::FromInt(UKismetMathLibrary::Min(MaxValue, CurrentValue)) + "/" + FString::FromInt(MaxValue));
	
	Super::UpdateWidget();
	
	TextBorder->SetBrushColor(FLinearColor::White);
	TextBorder->SetBrushFromMaterial(ProgressMaterial);
	UMaterialInstanceDynamic* DynamicMat = TextBorder->GetDynamicMaterial();
	DynamicMat->SetScalarParameterValue(FName("value"),(UKismetMathLibrary::FMin(MaxValue, CurrentValue)/MaxValue));
	DynamicMat->SetVectorParameterValue(FName("BGColor"),BGColor);
	DynamicMat->SetVectorParameterValue(FName("ProgressColor"),ProgressColor);
}
