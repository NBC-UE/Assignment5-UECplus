// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyActor::Turn(const FRotator& DeltaRotation)
{
	AddActorLocalRotation(DeltaRotation);
}

void AMyActor::Move(const FVector& DeltaMove)
{
	AccumulatedMoveDistance += DeltaMove;
	AddActorLocalOffset(DeltaMove);
}

void AMyActor::ExecuteEvent()
{
	RandomEventCount++;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Random으로 이벤트가 발생되었습니다.!"));
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	RandomEventCount = 0;
	AccumulatedMoveDistance = FVector::ZeroVector;
	
	for (int i = 0; i < 10; i++)
	{
		RandomTurnAndMove();
		const bool bShouldRandomEvent = FMath::RandBool();
		if (bShouldRandomEvent)
		{
			ExecuteEvent();
		}
		if (GEngine)
		{
			FRotator Rotation = GetActorRotation();
			FVector Location = GetActorLocation();
			
			FString MyInfo = FString::Printf(TEXT("위치: %s, 회전: %s"), *Location.ToString(), *Rotation.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, MyInfo);
		}
	}
	
	FString ResultString = FString::Printf(TEXT("총 이벤트 발생 횟수: %d, 총 이동 거리: %s"), RandomEventCount, *AccumulatedMoveDistance.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, ResultString);
	AccumulatedMoveDistance = FVector::ZeroVector;
}

void AMyActor::RandomTurnAndMove()
{
	const FRotator DeltaRotator = FRotator(
			FMath::FRandRange(-RotationRange, RotationRange),
			FMath::FRandRange(-RotationRange, RotationRange),
			FMath::FRandRange(-RotationRange, RotationRange));

	Turn(DeltaRotator);

	const FVector DeltaLocation = FVector(
		FMath::FRandRange(-MoveRange, MoveRange),
		FMath::FRandRange(-MoveRange, MoveRange),
		FMath::FRandRange(-MoveRange, MoveRange));
	Move(DeltaLocation);
}
