// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllablePawnMath.h"

float AControllablePawnMath::Angle(FVector V1, FVector V2)
{
	// Normalize the vectors
	V1.Normalize();
	V2.Normalize();

	// Calculate the dot product
	float DotProduct = FVector::DotProduct(V1, V2);

	// Calculate the angle in radians
	float AngleInRadians = FMath::Acos(DotProduct);

	// Convert the angle to degrees
	return FMath::RadiansToDegrees(AngleInRadians);
}

bool AControllablePawnMath::WithinRange(float value, float min, float max)
{
	return value >= min && value <= max;
}