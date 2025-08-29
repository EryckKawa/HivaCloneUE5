// Eryck Torres Project


#include "AnimInstances/HivaCharacterAnimInstance.h"
#include "Characters/HivaBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHivaCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AHivaBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UHivaCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter | !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
