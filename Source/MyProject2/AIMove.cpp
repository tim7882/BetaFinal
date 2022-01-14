// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMove.h"
#include "DrawDebughelpers.h"
#include "Engine/World.h"

float FPIDController::CalcNewInput(float Error, float Pos)
{

	ErrorSum = FMath::Clamp(Error + ErrorSum, ErrorMin, ErrorMax);
	float Input = Error * Proportional + ErrorSum * Integral + Derivative * (LastPos - Pos);
	LastPos = Pos;
	return Input;
}

void UAIMove::RequestDirectMove(const FVector& MoveVelocity, bool ForceMaxSpeed)
{
	Super::RequestDirectMove(MoveVelocity, ForceMaxSpeed);


	FVector VehicleLocation = GetOwner()->GetActorLocation();
	FVector Destination = VehicleLocation + MoveVelocity * GetWorld()->GetDeltaSeconds();

	FVector Distance = Destination - VehicleLocation;
	FVector InitialDistance = Destination - InitialLocation;
	FVector VehicleDirection = GetOwner()->GetActorForwardVector();

	// Throttle Controller

	float ForwardFactor = FVector::DotProduct(VehicleDirection, Distance.GetSafeNormal());

	float Error = Distance.Size() / InitialDistance.Size() * FMath::Sign(ForwardFactor);
	float Pos = 1 - Error;

	float Input = ThrottleController.CalcNewInput(Error, Pos);

	const float TURN_AROUND_FACTOR = turningAround ? 0.3f : 0.1f;
	if (ForwardFactor < TURN_AROUND_FACTOR && (ForceMaxSpeed || Distance.Size() > 300.f))
	{
		turningAround = true;
		SetThrottleInput(-1.f);

	}
	else
	{
		turningAround = false;
		SetThrottleInput(ForceMaxSpeed ? ForwardFactor : Input);
	}

	// steering controller

	float InitialYaw = InitialDistance.Rotation().Yaw - InitialDirection.Rotation().Yaw;
	if (InitialYaw < -180)
	{
		InitialYaw += 360;
	}
	else if (InitialYaw < 180)
	{
		InitialYaw -= 360;
	}

	float CurrentYaw = Distance.Rotation().Yaw - VehicleDirection.Rotation().Yaw;
	if (CurrentYaw < -180)
	{
		CurrentYaw += 360;
	}
	else if (CurrentYaw > 180)
	{
		CurrentYaw -= 360;
	}

	float SteeringPos = (-CurrentYaw + 180) / 180;
	float SteeringError = 1 - SteeringPos;

	float SteerInput = SteeringController.CalcNewInput(SteeringError, SteeringPos);
	if (turningAround)
	{
		SetSteeringInput(SteeringError > 0 ? -1.f : 1.f);
	}
	else
	{
		SetSteeringInput(SteerInput);
	}
	SetHandbrakeInput(false);
}

void UAIMove::StopActiveMovement()
{
	Super::StopActiveMovement();
	InitialLocation = GetOwner()->GetActorLocation();
	InitialDirection = GetOwner()->GetActorForwardVector();
	SetHandbrakeInput(true);
	SetThrottleInput(0.f);
}
