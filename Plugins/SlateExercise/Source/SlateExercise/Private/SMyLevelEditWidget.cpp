// Fill out your copyright notice in the Description page of Project Settings.


#include "SMyLevelEditWidget.h"

#include "MyCommands.h"
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

	// 注册命令
	FMyCommands::Register();

	// 创建命令队列
	MyCommandList = MakeShareable(new FUICommandList);
	
	// 行为与命令的绑定 ExecuteAction 实际上是触发一个函数
	MyCommandList->MapAction(FMyCommands::Get().FileCommand,FExecuteAction::CreateRaw(this, &SMyLevelEditWidget::OnFileCommandExecute),FCanExecuteAction());

	MyCommandList->MapAction(FMyCommands::Get().EditCommand,FExecuteAction::CreateRaw(this, &SMyLevelEditWidget::OnEditCommandExecute),FCanExecuteAction());

	MyCommandList->MapAction(FMyCommands::Get().WindowCommand,FExecuteAction::CreateRaw(this, &SMyLevelEditWidget::OnWindowCommandExecute),FCanExecuteAction());

	// 注册一个Tab生成器 演示Lambda写法
	FGlobalTabmanager::Get()->RegisterTabSpawner("3DViewer1", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args) -> TSharedRef<SDockTab>
	{
		// 创建一个DockTab
		return SNew(SDockTab)
			.Label(LOCTEXT("3DViewer", "3DViewer"))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeToolBar()
				]
				+ SVerticalBox::Slot()
				[
					SNew(SButton)
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
		// 菜单栏  确保在命令已经与行为绑定后 再创建 否则点击无效
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.HeightOverride(30)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					// 菜单栏
					MakeMenuBar()
				]
			]
		]
		
		+SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			LevelEditWidget
		]
	];
}


void SMyLevelEditWidget::OnFileCommandExecute()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("File Command Executed", "FileCommand"));
}

void SMyLevelEditWidget::OnEditCommandExecute()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Edit Command Executed", "EditCommand"));
}

void SMyLevelEditWidget::OnWindowCommandExecute()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Window Command Executed", "WindowCommand"));
}

TSharedRef<SWidget> SMyLevelEditWidget::MakeMenuBar()
{
	// 这里就用上了之前创建的命令队列  先申明一个菜单栏的建筑师
	FMenuBarBuilder MenuBarBuilder(MyCommandList);

	// 然后通过这个建筑师 往里边加三个下拉菜单  文件 编辑 窗口
	MenuBarBuilder.AddPullDownMenu(
		LOCTEXT("File", "File"),
		LOCTEXT("File_ToolTip", "File ToolTip"),
		FNewMenuDelegate::CreateRaw(this, &SMyLevelEditWidget::AddPullDownMenu));

	MenuBarBuilder.AddPullDownMenu(
		LOCTEXT("Edit", "Edit"),
		LOCTEXT("Edit_ToolTip", "Edit ToolTip"),
		FNewMenuDelegate::CreateRaw(this, &SMyLevelEditWidget::AddPullDownMenu));

	MenuBarBuilder.AddPullDownMenu(
		LOCTEXT("Window", "Window"),
		LOCTEXT("Window_ToolTip", "Window ToolTip"),
		FNewMenuDelegate::CreateRaw(this, &SMyLevelEditWidget::AddPullDownMenu));

	return MenuBarBuilder.MakeWidget();
}

void SMyLevelEditWidget::AddPullDownMenu(FMenuBuilder& Builder)
{
	//弄个分隔符
	Builder.BeginSection("CustomSection", LOCTEXT("CustomSection", "My Custom Section"));
	{
		// 添加一个按钮菜单 这样就和命令对应上了 命令也是按钮的形式
		Builder.AddMenuEntry(FMyCommands::Get().FileCommand);
		// 添加一个分隔符
		Builder.AddMenuSeparator("My Seperator1");
		Builder.AddMenuEntry(FMyCommands::Get().EditCommand);
		Builder.AddMenuSeparator("My Seperator2");
		Builder.AddMenuEntry(FMyCommands::Get().WindowCommand);

		// 下拉菜单的子菜单
		Builder.AddSubMenu(
			LOCTEXT("SubMenu", "SubMenu"),
			LOCTEXT("SubMenu_ToolTip", "SubMenu_ToolTip"),
			FNewMenuDelegate::CreateRaw(this, &SMyLevelEditWidget::AddSubMenuExtension),
			false, // 这个是用来控制是否显示下拉箭头的
			FSlateIcon(), // 这个是用来设置图标的 可以用自己的Style  FSlateIcon(FMyStyle::GetStyleSetName(), "MyIconName.Icon")
			false,
			"SubMenuHook"
		);

		Builder.EndSection();
	}
}

void SMyLevelEditWidget::AddSubMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMyCommands::Get().FileCommand);
}

TSharedRef<SWidget> SMyLevelEditWidget::MakeToolBar()
{
	FToolBarBuilder ToolBarBuilder(MyCommandList, FMultiBoxCustomization::None);
	ToolBarBuilder.BeginSection("MyToolBarSection");
	ToolBarBuilder.AddToolBarButton(FMyCommands::Get().FileCommand);
	ToolBarBuilder.AddToolBarButton(FMyCommands::Get().EditCommand);
	ToolBarBuilder.AddToolBarButton(FMyCommands::Get().WindowCommand);
	ToolBarBuilder.EndSection();
	return ToolBarBuilder.MakeWidget();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
