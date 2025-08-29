// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HivaCharacterAnimInstance.h"
#include "HivaPlayerAnimInstance.generated.h"

class AHivaPlayerCharacter;
/**
 * 
 */
UCLASS()
class HIVA_API UHivaPlayerAnimInstance : public UHivaCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|References")
	AHivaPlayerCharacter* OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimationData|LocomotionData")
	float EnterRelaxtStateThreshold = 5.f;

	float IdleElpasedTime;
};
