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
};
