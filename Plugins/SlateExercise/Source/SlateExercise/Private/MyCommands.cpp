// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCommands.h"

#include "SlateExerciseStyle.h"

#define LOCTEXT_NAMESPACE "MyCommandName"
FMyCommands::FMyCommands():TCommands(TEXT("MyMenu"),
                                     NSLOCTEXT("Contexts", "MyMenu", "MyMenu"),
                                     NAME_None,
                                     FSlateExerciseStyle::Get().GetStyleSetName())
{
	
}

void FMyCommands::RegisterCommands()
{
	// @Param 1: 命令
	// @Param 2: 命令的名字
	// @Param 3: 命令的描述
	// @Param 4: 命令的类型
	// @Param 5: 命令的快捷键输入方式 这里传入的意思是 Ctrl+O
	UI_COMMAND(FileCommand,"MyFile","File Operation",EUserInterfaceActionType::Button,FInputChord(EModifierKey::Control,EKeys::O));

	UI_COMMAND(EditCommand,"MyEdit","Edito Operation",EUserInterfaceActionType::Button,FInputChord(EModifierKey::Control,EKeys::E));
	UI_COMMAND(WindowCommand,"MyWindow","Window Operation",EUserInterfaceActionType::Button,FInputChord(EModifierKey::Control,EKeys::W));
}
#undef LOCTEXT_NAMESPACE