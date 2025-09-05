// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "Characters/HivaBaseCharacter.h"
#include "HivaEnemyCharacter.generated.h"

class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class HIVA_API AHivaEnemyCharacter : public AHivaBaseCharacter
{
	GENERATED_BODY()

public:
	AHivaEnemyCharacter();

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;
private:
	void InitEnemyStartupData();
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
