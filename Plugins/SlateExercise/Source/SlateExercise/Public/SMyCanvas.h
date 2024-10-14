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

	// 想做的是一个单选的多个选项的CheckBox
	TArray<TSharedPtr<SCheckBox>>  MyCheckBoxArray;

	// 在处理多个复选框的时候  当勾选的时候 调用这里的函数 将选中的勾选 其他的设置为未选择的状态
	template<int32 T>
	void OnCheckBoxStateChanged(ECheckBoxState NewCheckState)
	{
		// 如果当前就已经选择了这个单选项 再把状态恢复成选择状态 单选要保持总有一个是勾选的
		if (NewCheckState == ECheckBoxState::Unchecked)
		{
			if (MyCheckBoxArray.IsValidIndex(T))
			{
				MyCheckBoxArray[T]->SetIsChecked(ECheckBoxState::Checked);
			}
			return;
		}
		if (MyCheckBoxArray.IsValidIndex(T))
		{
			// 获取当前CheckBox的状态
			bool bIsChecked = MyCheckBoxArray[T]->IsChecked();
			// 输出当前CheckBox的状态
			UE_LOG(LogTemp,Warning,TEXT("CheckBox %d is %s"),T,bIsChecked ? TEXT("Checked") : TEXT("Unchecked"));
			for (int32 i = 0 ; i < MyCheckBoxArray.Num(); i++)
			{
				if (i == T) // 判断是第几个CheckBox  如果是当前选择的CheckBox 就设置为选中状态
				{
					if (MyCheckBoxArray.IsValidIndex(T) || MyCheckBoxArray[i].Get())
					{
						MyCheckBoxArray[i]->SetIsChecked(NewCheckState);
					}
				}
				else  // 除了当前选择的 其他的都设置为未选中状态
				{
					if (MyCheckBoxArray.IsValidIndex(i) || MyCheckBoxArray[i].Get())
					{
						MyCheckBoxArray[i]->SetIsChecked(ECheckBoxState::Unchecked);
					}
				}
			}
		}
	}
};
