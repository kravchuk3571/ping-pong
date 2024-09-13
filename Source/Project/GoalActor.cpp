#include "GoalActor.h"
#include "Components/BoxComponent.h"
#include "BallActor.h"
#include "PaddlePlayerController.h"
#include "Kismet/GameplayStatics.h"

AGoalActor::AGoalActor()
{
    PrimaryActorTick.bCanEverTick = true;

    GoalTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("GoalTrigger"));
    RootComponent = GoalTrigger;

    GoalTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    GoalTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AGoalActor::BeginPlay()
{
    Super::BeginPlay();

    GoalTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnGoalOverlapBegin);
}

void AGoalActor::OnGoalOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (ABallActor* Ball = Cast<ABallActor>(OtherActor))
    {
        const EPlayerID PlayerID = (GetActorLocation().X < 0) ? EPlayerID::Player1 : EPlayerID::Player2;

        if (auto* PlayerController = Cast<APaddlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
        {
            PlayerController->AddScore(PlayerID);
        }
    }
}
