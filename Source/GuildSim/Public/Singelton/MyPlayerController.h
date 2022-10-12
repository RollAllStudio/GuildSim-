// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AHUDMenager;
class UPlayerInteractionComponent;

/**
 * 
 */
UCLASS()
class GUILDSIM_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AMyPlayerController();

	UFUNCTION(BlueprintGetter, BlueprintPure)
	AHUDMenager* GetMyHudMenager();

	UFUNCTION(BlueprintGetter, BlueprintPure)
	UPlayerInteractionComponent* GetInteractionComponent() const { return PlayerInteractionComponent; }

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	UPrimitiveComponent* GetCurrentTracedComponent() const;

	UFUNCTION(BlueprintPure)
	AActor* GetCurrentTracedActor() const;

	UFUNCTION(BlueprintPure)
	UObject* GetCurrentInteractionObject() const;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetInteractionPressedTime() const {return InteractionPressedTime;}

private:

	UPROPERTY(BlueprintGetter = "GetMyHudMenager")
	AHUDMenager* MyHudMenager;

	UPROPERTY(BlueprintGetter = "GetInteractionComponent")
	UPlayerInteractionComponent* PlayerInteractionComponent;

	void OnInteractionPressed();
	void OnInteractionReleased();

	UPROPERTY()
	bool bIsInteractionPressed;

	UPROPERTY(BlueprintGetter = "GetInteractionPressedTime")
	float InteractionPressedTime;

protected:

	void BeginPlay() override;

};
