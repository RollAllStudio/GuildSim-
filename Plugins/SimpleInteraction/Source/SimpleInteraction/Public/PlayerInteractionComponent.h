// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/PlayerController.h"
#include "PlayerInteractionComponent.generated.h"

class UPrimitiveComponent;
class AActor;

// Hover Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoverComponent, class UPrimitiveComponent*, HoveredComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoverActor, class AActor*, HoveredActor);

// Unhover Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnhoveredComponent, class UPrimitiveComponent*, UnhoverComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUnhoveredActor, class AActor*, UnhoverActor);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class SIMPLEINTERACTION_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractionComponent();

	UPROPERTY(BlueprintAssignable)
	FHoverComponent OnHoveredNewComponent;

	UPROPERTY(BlueprintAssignable)
	FHoverActor OnHoveredNewActor;

	UPROPERTY(BlueprintAssignable)
	FUnhoveredComponent OnUnhoverComponent;

	UPROPERTY(BlueprintAssignable)
	FUnhoveredActor OnActorUnhovered;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	APlayerController* GetPlayerController() const {return PlayerController;}

	UFUNCTION(BlueprintCallable)
	void Init(APlayerController* OwningPlayerController);

	FHitResult CachedMouseHitResult;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	AActor* GetCurrentTracedActor() const {return CurrentTracedActor;}


	UFUNCTION(BlueprintGetter, BlueprintPure)
	UPrimitiveComponent* GetCurrentTracedComponent() const {return CurrentTracedComponent;}

private:

	UPROPERTY(BlueprintGetter = "GetPlayerController")
	APlayerController* PlayerController;

	UPROPERTY(BlueprintGetter = "GetCurrentTracedActor")
	AActor* CurrentTracedActor;
	void ProcedeCurrentTracedActor();

	UPROPERTY(BlueprintGetter = "GetCurrentTracedComponent")
	UPrimitiveComponent* CurrentTracedComponent;
	void ProcedeCurrentTracedComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
