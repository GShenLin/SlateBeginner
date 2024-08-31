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

	// 移除自己添加的UI
	void RemoveSlate();

private:
	TSharedPtr<SFirstCompoundWidget> UIPtr;
	TSharedPtr<SWeakWidget> WidgetContainer;  // ?? 为什么要用SWeakWidget

	UClass* UMGClass;
	TObjectPtr<UUserWidget> UMGWidget;
};
