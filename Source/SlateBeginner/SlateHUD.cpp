// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateHUD.h"

#include "SFirstCompoundWidget.h"
#include "Widgets/SWeakWidget.h"

void ASlateHUD::BeginPlay()
{
	Super::BeginPlay();

	// 引擎和视口是否合法
	if (GEngine && GEngine->GameViewport)
	{
		UIPtr = SNew(SFirstCompoundWidget);
		
		// 第一种添加方式
		// GEngine->GameViewport->AddViewportWidgetContent(UIPtr.ToSharedRef());

		// 第二种
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget)
			.PossiblyNullContent(UIPtr.ToSharedRef()));
	}
}
