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

	// Combo Box

	// 随便添加几个元素试试
	Options.Add(MakeShareable(new FString("One")));
	Options.Add(MakeShareable(new FString("Two")));
	Options.Add(MakeShareable(new FString("Three")));
	
	AddSlot()
		.Position(FVector2d(300,200))
		.Size(FVector2d(100,50))
		[
			SAssignNew(ComboBox,SComboBox<TSharedPtr<FString>>)
			.OptionsSource(&Options)
			// 当生成选项的Widget时候
			.OnGenerateWidget(this,&SMyCanvas::MakeWidgetForOptions)
			// 当选项改变时
			.OnSelectionChanged(this,&SMyCanvas::OnSelectionChanged)
			// 初始化
			.InitiallySelectedItem(CurrentComboBoxString)
			[
				SNew(STextBlock)
				.Text(this,&SMyCanvas::GetComboBoxCurrentLabel)
			]
		];

	// 水平布局盒子
	AddSlot()
		.Position(FVector2d(300,300))
		.Size(FVector2d(100,50))
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(2.0) // 这个代表占有的比例 默认是1 2.0表示此控件所占权重为2 与下边的两个插槽分别为 2 1 1
			.HAlign(HAlign_Fill) // 填充
			[
				SNew(SButton)
			]
			+SHorizontalBox::Slot()
			[
				SNew(SButton)
			]
			+SHorizontalBox::Slot()
			[
				SNew(SButton)
			]
		];

	// 可编辑文本框
	AddSlot()
		.Position(FVector2d(300,400))
		.Size(FVector2d(200,50))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			[
				SNew(SEditableText)
				.Justification(ETextJustify::Left) // 文本对齐方式
				.HintText(FText::FromString("Name")) // 默认文本
				.Font(FCoreStyle::Get().GetFontStyle("Embossedtext")) // 字体 后续会自定义
				.ToolTipText(FText::FromString("MyCustomEditableText")) // 提示文本
				.ColorAndOpacity(FSlateColor::UseForeground()) // 颜色
			]
			+SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			[
				SNew(SEditableText)
				.Justification(ETextJustify::Left) // 文本对齐方式
				.HintText(FText::FromString("Password")) // 默认文本
				.Font(FCoreStyle::Get().GetFontStyle("Embossedtext")) // 字体 后续会自定义
				.ToolTipText(FText::FromString("MyCustomEditableText")) // 提示文本
				.ColorAndOpacity(FSlateColor::UseForeground()) // 颜色
			]
			
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

TSharedRef<SWidget> SMyCanvas::MakeWidgetForOptions(TSharedPtr<FString> InOption)
{
	return SNew(STextBlock).Text(FText::FromString(*InOption));
}

void SMyCanvas::OnSelectionChanged(TSharedPtr<FString> InOption, ESelectInfo::Type SelectInfo)
{
	CurrentComboBoxString = InOption;
}

FText SMyCanvas::GetComboBoxCurrentLabel() const
{
	if (CurrentComboBoxString.IsValid())
	{
		return FText::FromString(*CurrentComboBoxString);
	}
	return FText::FromString("NULL");
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
