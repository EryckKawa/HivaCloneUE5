// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "HivaAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class HIVA_API UHivaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UHivaAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UHivaAttributeSet, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UHivaAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UHivaAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UHivaAttributeSet, DefensePower)
	
};
