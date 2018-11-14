// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTScppCharacter.h"
#include "RTSHUD.generated.h"

/**
 * 
 */
UCLASS()
class RTSCPP_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
	
public: 
	virtual void DrawHUD() override; // same as Tick(); (?)

	//2 points to create the rectangle of selection box
	FVector2D InitialPoint; //Position of first point (when we click in the screen and start holding)
	FVector2D CurrentPoint; //Position of second point (cursor position while holding)
	FVector2D GetMousePosition2D(); 
	
	UPROPERTY()
	bool bStartSelecting = false;

	UPROPERTY()
	TArray <ARTScppCharacter*> FoundActors;
};
