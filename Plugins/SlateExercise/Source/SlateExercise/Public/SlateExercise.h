// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FSlateExerciseModule : public IModuleInterface
{
public:
	void AddToolbarExtension(FToolBarBuilder& ToolBarBuilder);

	void AddMenuBarExtension(FMenuBarBuilder& MenuBarBuilder);

	void AddMenuExtension(FMenuBuilder& MenuBuilder);
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	// 当自定义的弹出窗口1打开时的回调
	TSharedRef<class SDockTab> OnSpawnMyWindow1(const class FSpawnTabArgs& SpawnTabArgs);

	// 当自定义的弹出窗口2打开时的回调
	TSharedRef<class SDockTab> OnSpawnMyWindow2(const class FSpawnTabArgs& SpawnTabArgs);

	// 在点击Tab的关闭按钮时的回调
	bool CanCloseTab();

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	// 自己展开窗口的管理器
	TSharedPtr<FTabManager> MyWindowTabManager;

	// 布局也是要单独保存的
	TSharedPtr<FTabManager::FLayout> MyWindowLayout;

	// 用于显示Canvas的Tab
	TSharedPtr<SDockTab> MainCanvasTab;
};
