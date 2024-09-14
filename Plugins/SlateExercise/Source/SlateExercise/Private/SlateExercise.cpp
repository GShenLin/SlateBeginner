// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateExercise.h"
#include "SlateExerciseStyle.h"
#include "SlateExerciseCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName SlateExerciseTabName("SlateExercise");

// 自定义的弹出窗口的名称
static const FName MyWindowTabName1("MyWindow1");
static const FName MyWindowTabName2("MyWindow2");

#define LOCTEXT_NAMESPACE "FSlateExerciseModule"

void FSlateExerciseModule::AddToolbarExtension(FToolBarBuilder& ToolBarBuilder)
{
	// 这里是在拓展菜单栏 拓展后 出现在了Play按钮后边 这里 使用之前已经注册好的 打开插件窗口的命令
	ToolBarBuilder.AddToolBarButton(FSlateExerciseCommands::Get().OpenPluginWindow);
}

void FSlateExerciseModule::AddMenuBarExtension(FMenuBarBuilder& MenuBarBuilder)
{
	// 这里是在拓展工具栏 拓展后 出现在了Play按钮后边 这里 使用之前已经注册好的 打开插件窗口的命令
	MenuBarBuilder.AddMenuEntry(FSlateExerciseCommands::Get().OpenPluginWindow);
}

void FSlateExerciseModule::AddMenuExtension(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FSlateExerciseCommands::Get().OpenPluginWindow);
}

void FSlateExerciseModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// 初始化样式 加载图片
	FSlateExerciseStyle::Initialize();
	FSlateExerciseStyle::ReloadTextures();

	// 注册命令
	FSlateExerciseCommands::Register();

	// 创建命令 命令可以插入各种槽位中 表示点击后是什么样一个操作 响应的方式 比如像按钮一样
	PluginCommands = MakeShareable(new FUICommandList);

	// 绑定命令
	PluginCommands->MapAction(
		FSlateExerciseCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSlateExerciseModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSlateExerciseModule::RegisterMenus));

	// 弹出的窗口
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SlateExerciseTabName, FOnSpawnTab::CreateRaw(this, &FSlateExerciseModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FSlateExerciseTabTitle", "SlateExercise"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	// 自定义弹出的窗口 准备制作有两个界面并排的窗口
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyWindowTabName1, FOnSpawnTab::CreateRaw(this, &FSlateExerciseModule::OnSpawnMyWindow1))
		.SetDisplayName(LOCTEXT("FSlateExerciseWindowTitle1", "SlateExerciseWindow1"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyWindowTabName2, FOnSpawnTab::CreateRaw(this, &FSlateExerciseModule::OnSpawnMyWindow2))
		.SetDisplayName(LOCTEXT("FSlateExerciseWindowTitle2", "SlateExerciseWindow2"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	// 为了往扩展点里添加元素 先要拿到编辑器的模块
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	// 拓展时需要一系列的属性定义
	TSharedPtr<FExtender> ToolBarExtender = MakeShareable(new FExtender); // 工具栏

	// 拓展点的位置 填入位置 和命令 以及回调函数
	ToolBarExtender->AddToolBarExtension("Play", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSlateExerciseModule::AddToolbarExtension));

	// 将当前拓展 添加到工具栏的拓展管理器中
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolBarExtender);

	// 从这里开始是拓展菜单栏的示例
	TSharedPtr<FExtender> MenuBarExtender = MakeShareable(new FExtender); // 菜单栏
	MenuBarExtender->AddMenuBarExtension("Help",EExtensionHook::After,PluginCommands,FMenuBarExtensionDelegate::CreateRaw(this,&FSlateExerciseModule::AddMenuBarExtension));

	// 同样需要添加到管理器中
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtender);

	// 添加到菜单栏的子菜单中
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
	MenuExtender->AddMenuExtension("WindowLayout",EExtensionHook::After,PluginCommands,FMenuExtensionDelegate::CreateRaw(this,&FSlateExerciseModule::AddMenuExtension));

	// 同样需要添加到管理器中
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FSlateExerciseModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSlateExerciseStyle::Shutdown();

	FSlateExerciseCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SlateExerciseTabName);
}

TSharedRef<SDockTab> FSlateExerciseModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	const TSharedRef<SDockTab> NomedTab = SNew(SDockTab).TabRole(NomadTab);

	// 如果自定义的管理器和布局不存在 创建一个  并且将两个窗口添加到布局中
	if (!MyWindowTabManager.IsValid())
	{
		MyWindowTabManager = FGlobalTabmanager::Get()->NewTabManager(NomedTab);
		MyWindowLayout = FTabManager::NewLayout("MyLayout")
			->AddArea
			(
				FTabManager::NewPrimaryArea()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					// 这段是自动提示的 可能这么做也可以？
					/*FTabManager::NewStack()
					->AddTab(MyWindowTabName1, ETabState::OpenedTab)
					->AddTab(MyWindowTabName2, ETabState::OpenedTab)*/
					FTabManager::NewStack()
					->SetSizeCoefficient(0.5f)
					->AddTab(MyWindowTabName1,ETabState::OpenedTab)
				)
				->Split(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.5f)
					->AddTab(MyWindowTabName2,ETabState::OpenedTab)
				)
			);
	}
	
	TSharedRef<SWidget> TabContent = MyWindowTabManager->RestoreFrom(MyWindowLayout.ToSharedRef(),TSharedPtr<SWindow>()).ToSharedRef();
	NomedTab->SetContent(TabContent);
	return NomedTab;
}

TSharedRef<class SDockTab> FSlateExerciseModule::OnSpawnMyWindow2(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab);
}

TSharedRef<class SDockTab> FSlateExerciseModule::OnSpawnMyWindow1(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab);
}

void FSlateExerciseModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(SlateExerciseTabName);
}

void FSlateExerciseModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FSlateExerciseCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSlateExerciseCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSlateExerciseModule, SlateExercise)