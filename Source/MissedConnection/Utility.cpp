// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility.h"

DEFINE_LOG_CATEGORY(LogAAAAA);


void Utility::Print(FString text) {
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("--%s--"), *text));
}
