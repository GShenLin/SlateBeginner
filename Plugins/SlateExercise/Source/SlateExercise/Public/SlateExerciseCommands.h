// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SlateExerciseStyle.h"

class FSlateExerciseCommands : public TCommands<FSlateExerciseCommands>
{
public:

	FSlateExerciseCommands()
		: TCommands<FSlateExerciseCommands>(TEXT("SlateExercise"), NSLOCTEXT("Contexts", "SlateExercise", "SlateExercise Plugin"), NAME_None, FSlateExerciseStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};