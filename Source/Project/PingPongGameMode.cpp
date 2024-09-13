#include "PingPongGameMode.h"

#include "PingPongGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PaddlePawn.h"
#include "BallActor.h"

void APingPongGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void APingPongGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    TArray<AActor*> FoundPawns;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APaddlePawn::StaticClass(), FoundPawns);

    for (auto* FoundPawn : FoundPawns)
    {
        if (auto* PaddlePawn = Cast<APaddlePawn>(FoundPawn))
        {
            if (PaddlePawn->GetController())
                continue;

            NewPlayer->SetIgnoreMoveInput(true);
            NewPlayer->Possess(PaddlePawn);
            break;
        }
    }

    NumPlayers++;

    if (NumPlayers != RequiredPlayers)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Waiting for players... %d/%d connected"), NumPlayers, RequiredPlayers));
        return;
    }

    StartMatch();
}

void APingPongGameMode::StartMatch()
{
    if (bGameStarted)
        return;

    bGameStarted = true;

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Match Started!"));

    for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (auto* PC = It->Get())
        {
            PC->SetIgnoreMoveInput(false);
        }
    }

    TArray<AActor*> FoundBalls;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABallActor::StaticClass(), FoundBalls);
    for (auto* Ball : FoundBalls)
    {
        if (auto* BallActor = Cast<ABallActor>(Ball))
        {
            BallActor->StartGame();
        }
    }
}
