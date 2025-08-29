// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HivaPlayerController.generated.h"

class UCharacterManagerComponent;
/**
 * 
 */
UCLASS()
class HIVA_API AHivaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHivaPlayerController();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Manager", meta = (AllowPrivateAccess = "true"))
	UCharacterManagerComponent* CharacterManagerComponent;
	
};
