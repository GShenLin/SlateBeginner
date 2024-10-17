// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class SLATEEXERCISE_API FMyCommands : public TCommands<FMyCommands>
{
public:
	// 这个构造函数的实现比较特殊 也是必须的 会将Style传递过去
	FMyCommands();

	// 注册命令的虚函数 是核心
	virtual void RegisterCommands() override;

	// 文件命令 
	TSharedPtr<FUICommandInfo> FileCommand;

	// 编辑命令
	TSharedPtr<FUICommandInfo> EditCommand;

	// 窗口命令
	TSharedPtr<FUICommandInfo> WindowCommand;
};
