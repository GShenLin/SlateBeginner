// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateExerciseCommands.h"

#define LOCTEXT_NAMESPACE "FSlateExerciseModule"

void FSlateExerciseCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "SlateExercise", "Bring up SlateExercise window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
