// Eryck Torres Project


#include "AbilitySystem/Abilities/HivaGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/HivaAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UHivaGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EHivaAbilityActivationPolity::OnGiven)
	{
		// This can be used to initialize the ability or set up any necessary state
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
	
}

void UHivaGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EHivaAbilityActivationPolity::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UHivaGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UHivaAbilitySystemComponent* UHivaGameplayAbility::GetHivaAbilitySystemComponentFromActorInfo() const
{
	return Cast<UHivaAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
