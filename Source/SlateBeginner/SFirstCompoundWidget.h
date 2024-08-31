// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLATEBEGINNER_API SFirstCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFirstCompoundWidget)
	{}
		SLATE_ARGUMENT(TWeakObjectPtr<ASlateHUD>, OwnerHUDArg);
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnPlayClicked() const;
	FReply OnQuitClicked() const;
private:
	// 销毁后引擎会自动回收
	TWeakObjectPtr<ASlateHUD> OwnerHUD;
};
