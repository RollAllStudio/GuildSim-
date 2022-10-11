// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/HUDMenager.h"
#include "Blueprint/UserWidget.h"
#include "../Public/ContextBaseHUDInterface.h"

void AHUDMenager::ShowWidget(const TSubclassOf<UUserWidget> WidgetClass, const bool bHideStack, const bool bClearStack, UObject* ContextObject, UUserWidget*& OutWidget)
{
	if (WidgetsStack.Num() == 0)
	{
		ToggleHUDContext(false);
	}

	if (bClearStack)
	{
		IsClearingStack = true;
		ClearStack();
		IsClearingStack = false;
	}

	if (bHideStack)
	{
		HideStack();
	}

	FindWidgetInContext(WidgetClass, WidgetsList, OutWidget);
	
	if (!OutWidget)
	{
		OutWidget = CreateWidget(GetOwningPlayerController(), WidgetClass);
		WidgetsList.Add(WidgetClass, OutWidget);
	}

	CurrentWidget = OutWidget;
	CurrentWidgetClass = WidgetClass;
	WidgetsStack.Add(CurrentWidget);
	CurrentWidget->AddToViewport();

	if (CurrentWidgetClass->StaticClass()->ImplementsInterface(UContextBaseHUDInterface::StaticClass()))
	{
		IContextBaseHUDInterface::Execute_OnShowWidget(CurrentWidget);
		IContextBaseHUDInterface::Execute_SetContextObject(CurrentWidget, ContextObject);
	}

}

void AHUDMenager::ClearStack()
{
	while (WidgetsStack.Num() > 0)
	{
		RemoveCurrentWidget();
	}
}

void AHUDMenager::RemoveCurrentWidget()
{
	if (GetCurrentWidget()->IsInViewport())
	{
		GetCurrentWidget()->RemoveFromViewport();
	}

	if (CurrentWidgetClass->StaticClass()->ImplementsInterface(UContextBaseHUDInterface::StaticClass()))
	{
		IContextBaseHUDInterface::Execute_OnHideWidget(CurrentWidget);
	}

	WidgetsStack.Remove(GetCurrentWidget());

	if (WidgetsStack.Num() > 0 && !IsClearingStack)
	{
		CurrentWidget = WidgetsStack.Last();
		CurrentWidgetClass = CurrentWidget->GetClass();

		if (!CurrentWidget->IsInViewport() && !IsClearingStack)
		{
			CurrentWidget->AddToViewport();
		}
		return;
	}
	
	ToggleHUDContext(true);
	CurrentWidget = nullptr;
	CurrentWidgetClass = nullptr;
	
}

void AHUDMenager::HideStack()
{
	for (int i = 0; i < WidgetsStack.Num(); i ++)
	{
		if (WidgetsStack[i]->IsInViewport())
		{
			WidgetsStack[i]->RemoveFromViewport();
		}
	}
}

void AHUDMenager::ToggleHUDContext(const bool InputValue)
{
	
	TArray<TSubclassOf<UUserWidget>> KeysArray;
	HUDContext.GetKeys(KeysArray);

	for (int i = 0; i < KeysArray.Num(); i++)
	{
		UUserWidget* LocalWidget = nullptr;

		if (FindWidgetInContext(KeysArray[i], HUDContext, LocalWidget))
		{
			if (!LocalWidget->IsInViewport() && InputValue)
			{
				LocalWidget->AddToViewport();
			}
			if (LocalWidget->IsInViewport() && !InputValue)
			{
				LocalWidget->RemoveFromViewport();
			}
		}
	}
}

void AHUDMenager::AddHUDContextWidget(const TSubclassOf<UUserWidget> WidgetClass)
{
	UUserWidget* LocalWidget = nullptr;
	FindWidgetInContext(WidgetClass, RemovedHUDContext, LocalWidget);
	if (!LocalWidget)
	{
		LocalWidget = CreateWidget(GetOwningPlayerController(), WidgetClass);
	}

	HUDContext.Add(WidgetClass, LocalWidget);
	if (ShouldShowHUD())
	{
		LocalWidget->AddToViewport();
	}
}

void AHUDMenager::RemoveHUDContextWidget(const TSubclassOf<UUserWidget> WidgetClass)
{

	UUserWidget* LocalWidget = nullptr;
	FindWidgetInContext(WidgetClass, HUDContext, LocalWidget);
	if (LocalWidget)
	{
		LocalWidget->RemoveFromViewport();
		RemovedHUDContext.Add(WidgetClass, LocalWidget);
	}

}

bool AHUDMenager::ShouldShowHUD()
{
	return WidgetsStack.Num() == 0;
}

bool AHUDMenager::FindWidgetInContext(const TSubclassOf<UUserWidget> WidgetClass, TMap<TSubclassOf<UUserWidget>, UUserWidget*> Context, UUserWidget*& OutWidget)
{
	OutWidget = Context.FindRef(WidgetClass);
	if (OutWidget)
	{
		return true;
	}
	return false;
}
