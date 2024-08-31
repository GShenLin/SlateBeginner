// Fill out your copyright notice in the Description page of Project Settings.


#include "SFirstCompoundWidget.h"
#include "SlateOptMacros.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Layout/SBackgroundBlur.h"

#define LOCTEXT_NAMESPACE "SFirstCompoundWidget"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFirstCompoundWidget::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUDArg;
	OtherWidget = InArgs._OtherWidgetArg;
	
	const FMargin ContentPadding = FMargin(500.0f,300.f); // Padding around the content
	const FMargin ButtonPadding = FMargin(20.0f); // Padding around the buttons
	const FText TitleText = LOCTEXT("SlateTest","Just Slate Test");  //  Text for the title
	const FText PlayText = LOCTEXT("Play","Play"); // Text for the play button
	const FText QuitText = LOCTEXT("Quit","Quit"); // Text for the play button

	// 字体的控制
	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.0f;

	FSlateFontInfo TitleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleTextStyle.Size = 60.0f;

	// 开始创建布局
	ChildSlot
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor(0.f,0.f,0.f,127))
		]

		+SOverlay::Slot()
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SBackgroundBlur)
			.BlurStrength(0.5f)
		]

		// 添加其他UMG元素的示例
		/*+SOverlay::Slot()
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			OtherWidget.Get()->TakeWidget()
		]*/

		+SOverlay::Slot()
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		.Padding(ContentPadding)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(TitleTextStyle)
				.Text(TitleText)
			]

			+ SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				SNew(SButton)
				.Text(PlayText)
				.OnClicked(this,&SFirstCompoundWidget::OnPlayClicked)
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(PlayText)
					.Justification(ETextJustify::Center)
				]
			]

			+ SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				SNew(SButton)
				.OnClicked(this,&SFirstCompoundWidget::OnQuitClicked)
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(QuitText)
					.Justification(ETextJustify::Center)
				]
			]
		]
	];
}

FReply SFirstCompoundWidget::OnPlayClicked() const
{
	if (OwnerHUD.IsValid())
	{
		OwnerHUD->RemoveSlate();
	}
	return FReply::Handled();
}

FReply SFirstCompoundWidget::OnQuitClicked() const
{
	if (OwnerHUD.IsValid())
	{
		OwnerHUD->PlayerOwner->ConsoleCommand("quit");
	}
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE