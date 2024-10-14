// Fill out your copyright notice in the Description page of Project Settings.


#include "SMyCanvas.h"

#include "MyMainWidgetStyle.h"
#include "SlateExerciseStyle.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Layout/SConstraintCanvas.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "SMyCanvas"

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

	// 分割器 SSplitter
	AddSlot()
		.Position(FVector2d(300,450))
		.Size(FVector2d(200,200))
		[
			SNew(SSplitter)
			+SSplitter::Slot()
			[
				SNew(SButton)
				[
					SNew(STextBlock)
					.Text(FText::FromString("MyButton1"))
				 ]
			]
			+SSplitter::Slot()
			[
				SNew(SButton)
				[
					SNew(STextBlock)
					.Text(FText::FromString("MyButton2"))
				]
			]
		];

	// 示例使用自己的样式文件
	// 这个Style的加载方式 感觉不太对 先通过插件默认创建的Style 加载了自己的Style 绕了一圈

	const  FMainWidgetStyle* MyWidgetStyle = &FSlateExerciseStyle::Get()
	.GetWidgetStyle<FMainWidgetStyle>(TEXT("NewSlateWidgetStyleAsset"));
	
	AddSlot()
		.Position(FVector2d(100,150))
		.Size(FVector2d(200,200))
	[
		SNew(SImage)
		.Image(&MyWidgetStyle->MyBrush)
	];

	// SOverlay
	AddSlot()
		.Position(FVector2d(100,200))
		.Size(FVector2d(200,200))
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.Image(&MyWidgetStyle->MyBrush)
		]
		
		+SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString("MyText"))
		]
	];

	// STextBlock
	// SOverlay
	AddSlot()
		.Position(FVector2d(100,250))
		.Size(FVector2d(200,200))
	[
		SNew(STextBlock)
		.Text(FText::FromString("MyTextBlock"))
		.Justification(ETextJustify::Left) // 文本对齐方式
		.Font(MyWidgetStyle->MyFontInfo) //字体
		.AutoWrapText(true) // 自动换行
	];

	// SBox SBorder
	AddSlot()
		.Position(FVector2d(100,350))
		.Size(FVector2d(100,100))
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBox)
			.WidthOverride(200)
			.HeightOverride(200)
			[
				SNew(SBorder)
				.BorderImage(&MyWidgetStyle->MyBrush)
				[
					SNew(STextBlock)
					.Text(FText::FromString("MyTextBlock"))
					.Justification(ETextJustify::Left) // 文本对齐方式
					.Font(MyWidgetStyle->MyFontInfo) //字体
					.AutoWrapText(true) // 自动换行
				]
			]
		]
		
	];

	// SButton
	AddSlot()
		.Position(FVector2d(100,450))
		.Size(FVector2d(100,100))
	[
		SNew(SButton)
		.Text(FText::FromString("MyButton010101"))
		.OnHovered_Lambda([](){ UE_LOG(LogTemp,Warning,TEXT("Hovered")); })
		.OnUnhovered_Lambda([](){ UE_LOG(LogTemp,Warning,TEXT("UnHovered")); })
		.OnPressed_Lambda([](){ UE_LOG(LogTemp,Warning,TEXT("Pressed")); })
		.OnReleased_Lambda([](){ UE_LOG(LogTemp,Warning,TEXT("Released")); })
		.OnClicked_Lambda([]()->FReply{ UE_LOG(LogTemp,Warning,TEXT("Clicked")); return FReply::Handled(); })
	];

	// SConstrainCanvas
	AddSlot()
		.Position(FVector2d(100,550))
		.Size(FVector2d(200,200))
	[
		SNew(SConstraintCanvas)
		+SConstraintCanvas::Slot()
		.Anchors(0.f)
		.Offset(FMargin(0,0,100,30))
		.Alignment(FVector2D(0,0))
		.AutoSize(false)
		.ZOrder(0)
		[
			SNew(STextBlock)
			.Text(FText::FromString("MyText1"))
		]
	];

	
	// SCheckBox
	// 提前设置一下CheckBox的数量
	MyCheckBoxArray.SetNum(3);
	
	AddSlot()
		.Position(FVector2d(400,550))
		.Size(FVector2d(200,200))
	[
		// AI的自动提示 一个简单的CheckBox
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		[
			SNew(SCheckBox)
			.OnCheckStateChanged_Lambda([](ECheckBoxState NewState){ UE_LOG(LogTemp,Warning,TEXT("CheckBox State Changed")); })
		]
		

		// 操作一组CheckBox
		+SVerticalBox::Slot()
		[
			// 添加第一个CheckBox
			SAssignNew(MyCheckBoxArray[0],SCheckBox)
			.IsEnabled(true) // 是否是激活状态
			.IsChecked(ECheckBoxState::Checked) // 是否勾选
			.OnCheckStateChanged(this,&SMyCanvas::OnCheckBoxStateChanged<0>) // 当状态改变时的回调
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("MyCheckBox1")))
			]
		]
		
		+SVerticalBox::Slot()
		[
			// 添加第二个CheckBox
			SAssignNew(MyCheckBoxArray[1],SCheckBox)
			.IsEnabled(true) // 是否是激活状态
			.IsChecked(ECheckBoxState::Unchecked) // 是否勾选
			.OnCheckStateChanged(this,&SMyCanvas::OnCheckBoxStateChanged<1>) // 当状态改变时的回调
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("MyCheckBox2")))
			]
		]
		
		+SVerticalBox::Slot()
		[
			// 添加第三个CheckBox
			SAssignNew(MyCheckBoxArray[2],SCheckBox)
			.IsEnabled(true) // 是否是激活状态
			.IsChecked(ECheckBoxState::Unchecked) // 是否勾选
			.OnCheckStateChanged(this,&SMyCanvas::OnCheckBoxStateChanged<2>) // 当状态改变时的回调
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("MyCheckBox3")))
			]
		]
	];

	// SGridPanel
	AddSlot()
		.Position(FVector2d(500,550))
		.Size(FVector2d(200,200))
	[
		SNew(SGridPanel)
		.FillColumn(0,1) // 填充第0列 占比为1
		.FillColumn(1,1) // 填充第1列 占比为1
		.FillRow(0,1) // 填充第0行 占比为1
		.FillRow(1,1)// 填充第1行 占比为1
		+ SGridPanel::Slot(0,0)
		[
			SNew(SButton)
			.Text(FText::FromString("Button1"))
		]

		+ SGridPanel::Slot(0,1)
		[
			SNew(SButton)
			.Text(FText::FromString("Button1"))
		]

		+ SGridPanel::Slot(1,0)
		[
			SNew(SButton)
			.Text(FText::FromString("Button1"))
		]

		+ SGridPanel::Slot(1,1)
		[
			SNew(SButton)
			.Text(FText::FromString("Button1"))
		]
	];

	// SScrollBox
	AddSlot()
		.Position(FVector2d(700,550))
		.Size(FVector2d(200,200))
	[
		SNew(SScrollBox)
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button1"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button2"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button3"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button4"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button5"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button6"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button7"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button8"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button9"))
		]
		+SScrollBox::Slot()
		[
			SNew(SButton)
			.Text(FText::FromString("Button10"))
		]
	];

	// ColorBrush
	static FSlateColorBrush MyColorBrush = FSlateColorBrush(FLinearColor(1.0,1.0,1.0,0.5));
	
	// SMultilineEditableText
	AddSlot()
		.Position(FVector2d(900,550))
		.Size(FVector2d(200,200))
	[
		SNew(SBorder)
		.BorderImage(&MyWidgetStyle->MyBrush)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(SMultiLineEditableTextBox)
				//.Text(FText::FromString("MyMultilineEditableText"))
				.HintText(LOCTEXT("text","请输入你的文本内容"))
				.Font(MyWidgetStyle->MyFontInfo)
				.AutoWrapText(true)
			]
		]
		
	];
}

FReply SMyCanvas::OnClickedButton()
{
	UE_LOG(LogTemp,Warning,TEXT("Button Clicked"));
	FMessageDialog::Open(EAppMsgType::Ok,FText::FromString("Button Clicked"));
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
