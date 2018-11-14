// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSHUD.h"
#include "RTScppCharacter.h"


void ARTSHUD::DrawHUD() { //Same as Tick ();
	if (bStartSelecting == true) {
		if (FoundActors.Num() > 0) {
			for (int32 i = 0; i < FoundActors.Num(); i++) {
				FoundActors[i]->SetDeselected();
			}
		}
		FoundActors.Empty();
		CurrentPoint = GetMousePosition2D(); //Current Mouse Position needs to be updated, because it's current. The value needs to be assigned every "Tick" DrawHUD does this function for us
		DrawRect(FLinearColor(0, 1, 0, .15f), InitialPoint.X, InitialPoint.Y,
			CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
		GetActorsInSelectionRectangle<ARTScppCharacter>(InitialPoint, CurrentPoint, FoundActors, false, false);

		if (FoundActors.Num() > 0) {
			for (int32 i = 0; i < FoundActors.Num(); i++) {
				FoundActors[i]->SetSelected();
			}
		}
	}
}

FVector2D ARTSHUD::GetMousePosition2D() {
	float xpos;
	float ypos;
	GetOwningPlayerController()->GetMousePosition(xpos, ypos);

	return FVector2D(xpos, ypos);
}



