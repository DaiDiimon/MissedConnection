// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationPlayer.h"

// Sets default values
AConversationPlayer::AConversationPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConversationPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConversationPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AConversationPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

