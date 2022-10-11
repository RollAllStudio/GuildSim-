// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDMenager.generated.h"

/**
 * 
 */
UCLASS()
class CONTEXTBASEDHUD_API AHUDMenager : public AHUD
{
	GENERATED_BODY()

	// Main Context Functions

	UFUNCTION(BlueprintCallable)
	void ShowWidget(const TSubclassOf<UUserWidget> WidgetClass, const bool bHideStack, const bool bClearStack, UObject* ContextObject, UUserWidget*& OutWidget);

	UFUNCTION(BlueprintCallable)
	void ClearStack();

	UFUNCTION(BlueprintCallable)
	void RemoveCurrentWidget();

	UFUNCTION(BlueprintCallable)
	void HideStack();

	// HUD Context functions

	UFUNCTION(BlueprintCallable)
	void ToggleHUDContext(const bool InputValue);

	UFUNCTION(BlueprintCallable)
	void AddHUDContextWidget(const TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(BlueprintCallable)
	void RemoveHUDContextWidget(const TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(BlueprintPure)
	bool ShouldShowHUD();

	// Contexts getters

	UFUNCTION(BlueprintGetter, BlueprintPure, Category = "HUD Context")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> GetHUDContext() const {return HUDContext;}

	UFUNCTION(BlueprintGetter, BlueprintPure, Category = "Widgets Stack")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> GetWidgetsList() const {return WidgetsList;}

	UFUNCTION(BlueprintGetter, BlueprintPure, Category = "Widgets Stack")
	TArray<UUserWidget*> GetWidgetsStack() const {return WidgetsStack;}

	UFUNCTION(BlueprintGetter, BlueprintPure, Category = "Widgets Stack")
	UUserWidget* GetCurrentWidget() const {return CurrentWidget;}

	UFUNCTION(BlueprintGetter, BlueprintPure, Category = "Widgets Stack")
	TSubclassOf<UUserWidget> GetCurrentWidgetClass() const { return CurrentWidgetClass; }

	UFUNCTION(BlueprintPure)
	bool FindWidgetInContext(const TSubclassOf<UUserWidget> WidgetClass, TMap<TSubclassOf<UUserWidget>, UUserWidget*> Context, UUserWidget*& OutWidget);

	UFUNCTION(BlueprintGetter, BlueprintPure, Category = "HUD Context")
	bool GetHUDState() const { return HUDState; }

private:

	// Contexts properties

	UPROPERTY(BlueprintGetter = "GetHUDState")
	bool HUDState;

	UPROPERTY(BlueprintGetter = "GetHUDContext")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> HUDContext;

	UPROPERTY()
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> RemovedHUDContext;

	UPROPERTY(BlueprintGetter = "GetWidgetsList")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> WidgetsList;

	UPROPERTY(BlueprintGetter = "GetWidgetsStack")
	TArray<UUserWidget*> WidgetsStack;

	UPROPERTY(BlueprintGetter = "GetCurrentWidget")
	UUserWidget* CurrentWidget;

	UPROPERTY(BlueprintGetter = "GetCurrentWidgetClass")
	TSubclassOf<UUserWidget> CurrentWidgetClass;

	// HELPERS
	bool IsClearingStack;

};
