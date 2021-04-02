// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConvesrationManager.generated.h"

class AConversationPartner;
class AConversationPlayer;

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class MISSEDCONNECTION_API UConvesrationManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UConvesrationManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AConversationPlayer* player;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AConversationPartner* partner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) 
	FString ReadFile(FString filename);


private:
	bool partner_speaking = true;

	FString text;

		
};
