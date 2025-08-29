// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/HivaBaseAnimInstance.h"
#include "HivaPlayerLinkedAnimLayer.generated.h"

class UHivaPlayerAnimInstance;
/**
 * 
 */
UCLASS()
class HIVA_API UHivaPlayerLinkedAnimLayer : public UHivaBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UHivaPlayerAnimInstance* GetPlayerAnimInstance() const;
};
