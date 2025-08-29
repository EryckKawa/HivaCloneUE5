// Eryck Torres Project


#include "Controllers/HivaPlayerController.h"

#include "Components/Characters/CharacterManagerComponent.h"

AHivaPlayerController::AHivaPlayerController()
{
	CharacterManagerComponent = CreateDefaultSubobject<UCharacterManagerComponent>(TEXT("CharacterManagerComponent"));
}
