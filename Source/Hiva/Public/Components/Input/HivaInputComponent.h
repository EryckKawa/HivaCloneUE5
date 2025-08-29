// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "HivaInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class HIVA_API UHivaInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
	                           UserObject* ContextObject, CallbackFunc CallbackFunction);

	template <class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc AbilityInputPressedCallbackFunction, CallbackFunc AbilityInputReleasedCallbackFunction);
};

template <class UserObject, typename CallbackFunc>
inline void UHivaInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
                                                       UserObject* ContextObject, CallbackFunc CallbackFunction)
{
	checkf(InInputConfig, TEXT("Input Config must not be null when binding native input action."));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, CallbackFunction);
	}
}

template <class UserObject, typename CallbackFunc>
void UHivaInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
	CallbackFunc AbilityInputPressedCallbackFunction, CallbackFunc AbilityInputReleasedCallbackFunction)
{
	checkf(InInputConfig, TEXT("Input Config must not be null when binding ability input action."));

	for (const FHivaInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (AbilityInputActionConfig.IsValid())
		{
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, AbilityInputPressedCallbackFunction, AbilityInputActionConfig.InputTag);
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, AbilityInputReleasedCallbackFunction, AbilityInputActionConfig.InputTag);
		}
		
	}
};
