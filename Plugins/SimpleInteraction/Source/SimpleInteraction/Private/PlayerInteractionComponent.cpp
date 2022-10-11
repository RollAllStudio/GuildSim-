// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractionComponent.h"

// Sets default values for this component's properties
UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UPlayerInteractionComponent::Init(APlayerController* OwningPlayerController)
{
	PlayerController = OwningPlayerController;
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInteractionComponent::ProcedeCurrentTracedActor()
{
	CurrentTracedActor = CachedMouseHitResult.GetActor();
	OnHoveredNewActor.Broadcast(CurrentTracedActor);
	ProcedeCurrentTracedComponent();
}

void UPlayerInteractionComponent::ProcedeCurrentTracedComponent()
{
	CurrentTracedComponent = CachedMouseHitResult.GetComponent();
	OnHoveredNewComponent.Broadcast(CurrentTracedComponent);
}

// Called when the game starts
void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult TempHitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, TempHitResult);

	if (TempHitResult.GetActor() != CachedMouseHitResult.GetActor())
	{
		if (CurrentTracedActor)
		{
			OnActorUnhovered.Broadcast(CurrentTracedActor);
			OnUnhoverComponent.Broadcast(CurrentTracedComponent);
		}
		CachedMouseHitResult = TempHitResult;
		ProcedeCurrentTracedActor();
		ProcedeCurrentTracedComponent();
	}
	else if (TempHitResult.GetComponent() != CachedMouseHitResult.GetComponent())
	{
		OnUnhoverComponent.Broadcast(CurrentTracedComponent);
		CachedMouseHitResult = TempHitResult;
		ProcedeCurrentTracedComponent();
	}
}

