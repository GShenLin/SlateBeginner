// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlateHUD.generated.h"

class SWeakWidget;
class SFirstCompoundWidget;
/**
 * 
 */
UCLASS()
class SLATEBEGINNER_API ASlateHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	TSharedPtr<SFirstCompoundWidget> UIPtr;
	TSharedPtr<SWeakWidget> WidgetContainer;  // ?? 为什么要用SWeakWidget
};
