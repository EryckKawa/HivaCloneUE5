// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Abilities/HivaGameplayAbility.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "HivaTypes/HivaStructTypes.h"
#include "MyDataAsset_PlayerStartUpData.generated.h"


/**
 * 
 */
UCLASS()
class HIVA_API UMyDataAsset_PlayerStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta = (TitleProperty = "InputTag"))
	TArray<FHivaPlayerAbilitySet> PlayerStartupAbilitiesSets;
};
