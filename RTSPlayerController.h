// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "RTSHUD.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTSCPP_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARTSPlayerController();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	ARTSHUD* HUDPtr;

	
protected:

	UFUNCTION()
	void SelectionPressed();
	UFUNCTION()
	void SelectionReleased();
	UFUNCTION()
	void MoveReleased();
	UPROPERTY()
	TArray <ARTScppCharacter*> SelectedActors;


};
	