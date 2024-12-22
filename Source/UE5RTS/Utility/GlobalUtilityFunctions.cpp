// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalUtilityFunctions.h"

bool UGlobalUtilityFunctions::GetIsEditor()
{
    bool bIsEditor = false;
#if UE_EDITOR
    bIsEditor = true;
#endif
    return bIsEditor;
}
