// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConvesrationManager.generated.h"

UENUM(BlueprintType)
enum class EConversationAnimation : uint8 {
	IDLE		UMETA(DisplayName = "Idle"),
	SURPRISE	UMETA(DisplayName = "Surprise"),
	LAUGH		UMETA(DisplayName = "Laugh")
};


USTRUCT(BlueprintType)
struct FBranchInfo {
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString dialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool has_label;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString label;

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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BranchBlueprint(const TArray<FBranchInfo>& branches);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EndBlueprint();	
	

private:
	typedef bool (UConvesrationManager::*Command)(FString);

	bool ResolveCommand(FString command, FString args);

	bool PlayAnimation(FString args);

	bool Look(FString args);

	bool You(FString args);

	bool Wait(FString args);

	bool Branch(FString args);

	bool End(FString args);

	void SetupLabels();

	void WaitFor(float seconds);

public:	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool Me(FString args);
	
	UFUNCTION(BlueprintCallable)
	void Continue();

	UFUNCTION(BlueprintCallable) 
	FString ReadFile(FString filename);

	UFUNCTION(BlueprintCallable)
	void JumpToLabel(FString label);


private:
	FString text;

	bool wait_timer_active = false;

	float wait_timer = 0;

	int read_index = 0;

	TMap<FString, EConversationAnimation> animation_map = {
		{TEXT("surprise"), EConversationAnimation::SURPRISE},
		{TEXT("laugh"), EConversationAnimation::LAUGH},
		{TEXT("idle"), EConversationAnimation::IDLE}
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

		
};
