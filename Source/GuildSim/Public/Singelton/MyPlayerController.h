// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPlayerInteractionComponent* GetInteractionComponent() { return PlayerInteractionComponent; }

private:

	UPROPERTY(BlueprintGetter = "GetMyHudMenager")
	AHUDMenager* MyHudMenager;

	UPROPERTY(BlueprintGetter = "GetInteractionComponent")
	UPlayerInteractionComponent* PlayerInteractionComponent;

protected:

	void BeginPlay() override;

};
