// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCanvas.h"

/**
 * 自定义Canvas演示
 */
class SLATEEXERCISE_API SMyCanvas : public SCanvas
{
public:
	SLATE_BEGIN_ARGS(SMyCanvas)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnClickedButton();

	// Combo Box
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;

	// Combo Box 当前选择的字符串
	TSharedPtr<FString> CurrentComboBoxString{0};

	// 一组ComboBox的选项
	TArray<TSharedPtr<FString>> Options;

	// 根据字符串 返回一个TextBlock文本块
	TSharedRef<SWidget> MakeWidgetForOptions(TSharedPtr<FString> InOption);

	// 当选择发生改变的时候触发的回调函数
	void OnSelectionChanged(TSharedPtr<FString> InOption, ESelectInfo::Type SelectInfo);

	// 当选择变化时 显示的文本
	FText GetComboBoxCurrentLabel() const;
};
