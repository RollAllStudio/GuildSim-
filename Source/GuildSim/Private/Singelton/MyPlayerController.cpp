// Fill out your copyright notice in the Description page of Project Settings.


#include "Singelton/MyPlayerController.h"
#include "HUDMenager.h"
#include "SimpleInteraction/Public/PlayerInteractionComponent.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerInteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("PlayerInteractionComponent"));
	UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
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
	SetShowMouseCursor(true);
	Super::BeginPlay();
}
