// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLATEEXERCISE_API SMyLevelEditWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyLevelEditWidget)
	{}
	SLATE_END_ARGS()

	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// 用于演示CreateRaw时绑定的函数 实际并未调用
	TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& SpawnTabArgs);

	// 命令队列
	TSharedPtr<class FUICommandList> MyCommandList;

	// 文件操作后的回调函数
	void OnFileCommandExecute();

	// 编辑操作后的回调函数
	void OnEditCommandExecute();
	
	// 窗口操作后的回调函数
	void OnWindowCommandExecute();

	// 用来创建菜单栏
	TSharedRef<SWidget> MakeMenuBar();

	// 下拉菜单
	void AddPullDownMenu(FMenuBuilder& Builder);

	// 下拉菜单的子菜单
	void AddSubMenuExtension(FMenuBuilder& Builder);

	// 用于创建工具栏
	TSharedRef<SWidget> MakeToolBar();
};
