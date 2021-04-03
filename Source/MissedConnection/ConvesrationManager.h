// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConvesrationManager.generated.h"

UENUM(BlueprintType)
enum class EConversationAnimation : uint8 {
	SURPRISE	UMETA(DisplayName = "Surprise"),
	LAUGH		UMETA(DisplayName = "Laugh")
};

class AConversationPartner;
class AConversationPlayer;

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class MISSEDCONNECTION_API UConvesrationManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UConvesrationManager();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	AConversationPlayer* player;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	AConversationPartner* partner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	typedef bool (UConvesrationManager::*Command)(FString);

	bool ResolveCommand(FString command, FString args);

	bool Look(FString args);

	bool PlayAnimation(FString args);

	bool Me(FString args);

	bool You(FString args);

	bool Branch(FString args);

	bool End(FString args);

	bool Wait(FString args);

	void SetupLabels();

	void WaitFor(float seconds);

public:	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Continue();

	UFUNCTION(BlueprintCallable) 
	FString ReadFile(FString filename);


private:
	FString text;

	bool wait_timer_active = false;

	float wait_timer = 0;

	int read_index = 0;

	TMap<FString, EConversationAnimation> animation_map = {
		{TEXT("surprise"), EConversationAnimation::SURPRISE},
		{TEXT("laugh"), EConversationAnimation::LAUGH}
	};

	TMap<FString, Command> command_map = {
		{TEXT("look"), &UConvesrationManager::Look},
		{TEXT("animate"), &UConvesrationManager::PlayAnimation},
		{TEXT("you"), &UConvesrationManager::You},
		{TEXT("me"), &UConvesrationManager::Me},
		{TEXT("wait"), &UConvesrationManager::Wait},
		{TEXT("end"), &UConvesrationManager::End},
		{TEXT("branch"), &UConvesrationManager::Branch}
	};

	TMap<FString, int> label_map;

	//const FRegexPattern new_line_regex;
	//const FRegexPattern branch_regex;

		
};
