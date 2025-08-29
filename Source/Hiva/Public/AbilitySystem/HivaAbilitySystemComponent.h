// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HivaTypes/HivaStructTypes.h"
#include "HivaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class HIVA_API UHivaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GrantPlayerWeaponAbilities(const TArray<FHivaPlayerAbilitySet>& InWeaponAbilities, int32 ApplyLevel = 1);
};
