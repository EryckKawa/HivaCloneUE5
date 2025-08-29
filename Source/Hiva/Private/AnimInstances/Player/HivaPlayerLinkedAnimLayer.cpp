// Eryck Torres Project


#include "AnimInstances/Player/HivaPlayerLinkedAnimLayer.h"
#include "AnimInstances/Player/HivaPlayerAnimInstance.h"

UHivaPlayerAnimInstance* UHivaPlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<UHivaPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
