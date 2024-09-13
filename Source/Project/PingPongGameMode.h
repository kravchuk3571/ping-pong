#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameMode.generated.h"

UCLASS()
class PROJECT_API APingPongGameMode : public AGameModeBase
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void PostLogin(APlayerController* NewPlayer) override;

private:
    void StartMatch();

    const int32 RequiredPlayers = 2;
    bool bGameStarted = false;
    int32 NumPlayers = 0;
};
