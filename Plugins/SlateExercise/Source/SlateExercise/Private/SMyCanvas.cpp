// Fill out your copyright notice in the Description page of Project Settings.


#include "SMyCanvas.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMyCanvas::Construct(const FArguments& InArgs)
{
	// 就像蓝图的Canvas控件一样 SCanvas支持多个Slot
	AddSlot()
		.Position(FVector2d(100,100))
		.Size(FVector2d(100,50))
		[
			SNew(SButton)
			.OnClicked(this,&SMyCanvas::OnClickedButton)
		];

	AddSlot()
		.Position(FVector2d(300,100))
		.Size(FVector2d(100,50))
		[
			SNew(SButton)
			.OnClicked(this,&SMyCanvas::OnClickedButton)
		];
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

FReply SMyCanvas::OnClickedButton()
{
	UE_LOG(LogTemp,Warning,TEXT("Button Clicked"));
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
