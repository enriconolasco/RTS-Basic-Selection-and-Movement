// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


//Base constructor that enables mouse being showed
ARTSPlayerController :: ARTSPlayerController (){
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ARTSPlayerController::BeginPlay() {
	Super::BeginPlay();
	HUDPtr = Cast<ARTSHUD>(GetHUD()); //GetHUD gets A hud, the one assigned to this Player Controller. Cast checks if this hud is RTSHUD, and if it is, assignes it to the pointer I made.
}

void ARTSPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

//Gives action (InputComponent -> BindAction) to given inputs (left and right mouse clicks, if released or pressed (IE_), in which class (this) and the action (which method will be activated))
void ARTSPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ARTSPlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &ARTSPlayerController::SelectionReleased);

	InputComponent->BindAction("RightMouseClick", IE_Released, this, &ARTSPlayerController::MoveReleased);
}

void ARTSPlayerController::SelectionPressed() {
	if (HUDPtr != nullptr) {
		HUDPtr->InitialPoint = HUDPtr->GetMousePosition2D();
		HUDPtr->bStartSelecting = true;
	}
	
}

void ARTSPlayerController::SelectionReleased() {
	HUDPtr->bStartSelecting = false;
	SelectedActors = HUDPtr->FoundActors;
}

//Happens when right mouse click is pressed
void ARTSPlayerController::MoveReleased() {
	if (SelectedActors.Num() > 0) {
		for (int32 i = 0; i < SelectedActors.Num(); i++) {
			FHitResult	Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
			FVector MoveLocation = Hit.Location + FVector(i/2*80, i%2*80, 0);
			DrawDebugSphere(GetWorld(), MoveLocation, 25, 10, FColor::Green, 3.0f);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);//Use Behavior Tree - AI controller
			}
		}
	}

