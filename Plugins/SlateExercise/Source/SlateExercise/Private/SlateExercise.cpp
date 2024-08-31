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

#define LOCTEXT_NAMESPACE "FSlateExerciseModule"

void FSlateExerciseModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// 初始化样式 加载图片
	FSlateExerciseStyle::Initialize();
	FSlateExerciseStyle::ReloadTextures();

	// 注册命令
	FSlateExerciseCommands::Register();
	
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
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FSlateExerciseModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("SlateExercise.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
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