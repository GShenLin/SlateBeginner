// Fill out your copyright notice in the Description page of Project Settings.


#include "SMyLevelEditWidget.h"
#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "SlateExercise"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<SDockTab>  SMyLevelEditWidget::SpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// 创建一个DockTab
	return SNew(SDockTab)
		.Label(LOCTEXT("3DViewer", "3DViewer"))
		[
			SNew(SBox)
			[
				SNew(SButton)
				.Text(LOCTEXT("3DViewer", "3DViewer"))
			]
		];
}

void SMyLevelEditWidget::Construct(const FArguments& InArgs)
{
	// 先取消所有的注册
	FGlobalTabmanager::Get()->UnregisterAllTabSpawners();
	// 演示CreateRaw的写法
	//FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer", FOnSpawnTab::CreateRaw(this, &SMyLevelEditWidget::SpawnTab));

	// 注册一个Tab生成器 演示Lambda写法
	FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer1", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		// 创建一个DockTab
		return SNew(SDockTab)
			.Label(LOCTEXT("3DViewer", "3DViewer"))
			[
				SNew(SBox)
				[
					SNew(SButton)
					.Text(LOCTEXT("3DViewer", "3DViewer"))
				]
			];
	}));
	
	FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer2", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		// 创建一个DockTab
		return SNew(SDockTab)
			.Label(LOCTEXT("3DViewer", "3DViewer"))
			[
				SNew(SBox)
				[
					SNew(SButton)
					.Text(LOCTEXT("3DViewer", "3DViewer"))
				]
			];
	}));

	FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer3", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		// 创建一个DockTab
		return SNew(SDockTab)
			.Label(LOCTEXT("3DViewer", "3DViewer"))
			[
				SNew(SBox)
				[
					SNew(SButton)
					.Text(LOCTEXT("3DViewer", "3DViewer"))
				]
			];
	}));

	FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer4", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		// 创建一个DockTab
		return SNew(SDockTab)
			.Label(LOCTEXT("3DViewer", "3DViewer"))
			[
				SNew(SBox)
				[
					SNew(SButton)
					.Text(LOCTEXT("3DViewer", "3DViewer"))
				]
			];
	}));

	FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer5", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		// 创建一个DockTab
		return SNew(SDockTab)
			.Label(LOCTEXT("3DViewer", "3DViewer"))
			[
				SNew(SBox)
				[
					SNew(SButton)
					.Text(LOCTEXT("3DViewer", "3DViewer"))
				]
			];
	}));

	FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer6", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		// 创建一个DockTab
		return SNew(SDockTab)
			.Label(LOCTEXT("3DViewer", "3DViewer"))
			[
				SNew(SBox)
				[
					SNew(SButton)
					.Text(LOCTEXT("3DViewer", "3DViewer"))
				]
			];
	}));

	FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer7", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		// 创建一个DockTab
		return SNew(SDockTab)
			.Label(LOCTEXT("3DViewer", "3DViewer"))
			[
				SNew(SBox)
				[
					SNew(SButton)
					.Text(LOCTEXT("3DViewer", "3DViewer"))
				]
			];
	}));

	// 布局的定义
	TSharedRef<FTabManager::FLayout> MyLayout = FTabManager::NewLayout("MyLayout")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Horizontal) // 设置为朝向水平方向布局
		->Split
		(
			FTabManager::NewSplitter() // 继续进行切割  可以用Spliter不停地切割
			->SetSizeCoefficient(0.8)
			->Split
			(
				FTabManager::NewStack()
				->AddTab("3DViewer1", ETabState::OpenedTab)
				->AddTab("3DViewer2", ETabState::OpenedTab)
				->AddTab("3DViewer3", ETabState::OpenedTab)
				->AddTab("3DViewer4", ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewStack()
				->AddTab("3DViewer5", ETabState::OpenedTab)
				->AddTab("3DViewer6", ETabState::OpenedTab)
				->AddTab("3DViewer7", ETabState::OpenedTab)
			)
			
		)
	);

	// 找个窗口显示出来
	TSharedRef<SWidget> LevelEditWidget = FGlobalTabmanager::Get()->RestoreFrom(MyLayout, TSharedPtr<SWindow>()).ToSharedRef();

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			LevelEditWidget
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
