// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HivaGameplayAbility.generated.h"

class UHivaAbilitySystemComponent;
class UPawnCombatComponent;

UENUM()
enum class EHivaAbilityActivationPolity : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class HIVA_API UHivaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface
	
	UPROPERTY(EditDefaultsOnly, Category = "HivaAbilityPolicy")
	EHivaAbilityActivationPolity AbilityActivationPolicy = EHivaAbilityActivationPolity::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "HivaAbility")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "HivaAbility")
	UHivaAbilitySystemComponent* GetHivaAbilitySystemComponentFromActorInfo() const;
};

