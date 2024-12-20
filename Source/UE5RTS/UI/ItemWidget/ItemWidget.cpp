// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateWidget();
}

void UItemWidget::UpdateWidget()
{
	ItemImage->SetBrush(ItemImageBrush);
	ItemName->SetText(ItemNameText);
	TextBorder->SetBrushColor(BGColor);
}
