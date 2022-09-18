// Fill out your copyright notice in the Description page of Project Settings.


#include "Singelton/MyPlayerController.h"
#include "HUDMenager.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

AHUDMenager* AMyPlayerController::GetMyHudMenager()
{
	if (!MyHudMenager)
	{
		MyHudMenager = Cast<AHUDMenager>(GetHUD());
	}

	return MyHudMenager;
}

void AMyPlayerController::BeginPlay()
{
	GetMyHudMenager();
}
