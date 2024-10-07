// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMainWidgetStyle.h"

// static member defination
const FName FMainWidgetStyle::TypeName(TEXT("MainWidgetStyle"));

void FMainWidgetStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	FSlateWidgetStyle::GetResources(OutBrushes);
}

const FName FMainWidgetStyle::GetTypeName() const
{
	return TypeName;
}

const FMainWidgetStyle& FMainWidgetStyle::GetDefault()
{
	static FMainWidgetStyle MyWidgetStyle;
	return MyWidgetStyle;
}

const FSlateWidgetStyle* const UMyMainWidgetStyle::GetStyle() const
{
	//return static_cast<const struct FSlateWidgetStyle* >(&MyWidgetStyle);
	return &MyWidgetStyle;
}
