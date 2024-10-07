// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "MyMainWidgetStyle.generated.h"


USTRUCT()
struct FMainWidgetStyle : public FSlateWidgetStyle
{
	GENERATED_BODY()

	// Override
	virtual void GetResources( TArray<const FSlateBrush*> & OutBrushes ) const override;
	virtual const FName GetTypeName() const override;

	// Singleton
	static const FMainWidgetStyle& GetDefault();
	static const FName TypeName;

	// 图片属性
	UPROPERTY(EditAnywhere,Category = "MainWidgetStyle")
	FSlateBrush MyBrush;

	// 字体属性
	UPROPERTY(EditAnywhere,Category = "MainWidgetStyle")
	FSlateFontInfo MyFontInfo;

	// 音效属性
	UPROPERTY(EditAnywhere,Category = "MainWidgetStyle")
	FSlateSound MySound;

	// 颜色属性
	UPROPERTY(EditAnywhere,Category = "MainWidgetStyle")
	FLinearColor MyColor;
};

/**
 * 
 */
UCLASS()
class SLATEEXERCISE_API UMyMainWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category = "MyWidgetTyle" , meta=(ShowOnlyInnerProperties))
	FMainWidgetStyle MyWidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override;
};
