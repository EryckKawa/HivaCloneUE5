// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HivaBaseAnimInstance.h"
#include "HivaCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AHivaBaseCharacter;
/**
 * 
 */
UCLASS()
class HIVA_API UHivaCharacterAnimInstance : public UHivaBaseAnimInstance
{
	GENERATED_BODY()

public:
	// Constructor of the class
	virtual void NativeInitializeAnimation() override;
	
	// Called every frame to update the animation instance using other threads than the main thread
	// This is useful for performance reasons, as it allows the animation to be updated without blocking
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	AHivaBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|Movement")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|Movement")
	bool bHasAcceleration;
	
};
