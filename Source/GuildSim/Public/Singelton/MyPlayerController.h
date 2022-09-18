// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AHUDMenager;

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

private:

	UPROPERTY(BlueprintGetter = "GetMyHudMenager")
	AHUDMenager* MyHudMenager;

protected:

	void BeginPlay() override;

};
