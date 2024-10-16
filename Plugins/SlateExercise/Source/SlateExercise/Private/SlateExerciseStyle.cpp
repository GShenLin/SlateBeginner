// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateExerciseStyle.h"

#include "MyMainWidgetStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FSlateExerciseStyle::StyleInstance = nullptr;

void FSlateExerciseStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FSlateExerciseStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FSlateExerciseStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SlateExerciseStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FSlateExerciseStyle::Create()
{
	/*TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("SlateExerciseStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("SlateExercise")->GetBaseDir() / TEXT("Resources"));

	Style->Set("SlateExercise.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));*/

	// 我这里是放在插件里的 所以是插件的路径
	TSharedRef< FSlateStyleSet > Style = FSlateGameResources::New(
		FMainWidgetStyle::TypeName,
		"/SlateExercise/NewSlateWidgetStyleAsset","/SlateExercise/NewSlateWidgetStyleAsset");

	// 插件的图片设置
	FString ImagePath =  IPluginManager::Get().FindPlugin("SlateExercise")->GetBaseDir() / TEXT("Resources/Snipaste.png");
	Style->Set("SlateExercise.OpenPluginWindow", new FSlateImageBrush(ImagePath, CoreStyleConstants::Icon128x128));
	
	return Style;
}

void FSlateExerciseStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FSlateExerciseStyle::Get()
{
	return *StyleInstance;
}
