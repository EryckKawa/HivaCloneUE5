// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UHivaAbilitySystemComponent;
class UHivaGameplayAbility;
/**
 * 
 */
UCLASS()
class HIVA_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUp Data")
	TArray<TSubclassOf<UHivaGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUp Data")
	TArray<TSubclassOf<UHivaGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UHivaGameplayAbility>>& InAbilitiesToGive, UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, int32 ApplyLevel = 1);
};
