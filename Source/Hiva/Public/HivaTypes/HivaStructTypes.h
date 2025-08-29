// Eryck Torres Project

#pragma once
#include "GameplayTagContainer.h"
#include "AbilitySystem/Abilities/HivaGameplayAbility.h"
#include "HivaStructTypes.generated.h"

class UInputMappingContext;
class UHivaPlayerLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FHivaPlayerAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "AbilitySet"))
	TSubclassOf<UHivaGameplayAbility> AbilityToAdd;

	bool IsValid() const
	{
		return InputTag.IsValid() && AbilityToAdd;
	}
};

USTRUCT(BlueprintType)
struct FHivaPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHivaPlayerLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
	TArray<FHivaPlayerAbilitySet> DefaultWeaponAbilities;
};
