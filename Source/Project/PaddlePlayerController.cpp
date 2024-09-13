#include "PaddlePlayerController.h"
#include "PaddlePawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerState.h"
#include "ScoreWidget.h"

void APaddlePlayerController::BeginPlay()
{
    Super::BeginPlay();

    PaddlePawn = Cast<APaddlePawn>(GetPawn());

    SetupInput();
    SetupCamera();
    CreateScoreWidgetIfLocal();
}

void APaddlePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

void APaddlePlayerController::AddScore(EPlayerID PlayerID)
{
    switch (PlayerID)
    {
    case EPlayerID::Player1:
        Player1Score++;
        break;
    case EPlayerID::Player2:
        Player2Score++;
        break;
    }

    UpdateScoreUI();
}

void APaddlePlayerController::SetupInput()
{
    if (!PaddlePawn)
        return;

    if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(PlayerMappingContext, 0);
    }

    if (InputComponent)
    {
        if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APaddlePlayerController::Move);
        }
    }
}

void APaddlePlayerController::SetupCamera()
{
    if (!PaddlePawn)
        return;

    const FRotator PawnRotation = PaddlePawn->GetActorRotation();

    const FVector OffsetBehindPawn = -PawnRotation.Vector() * 1000.f + FVector(0.f, 0.f, 500.f);

    const FVector CameraLocation = PaddlePawn->GetActorLocation() + OffsetBehindPawn;

    ACameraActor* FixedCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraLocation, PawnRotation);
    SetViewTarget(FixedCamera);
}

void APaddlePlayerController::CreateScoreWidgetIfLocal()
{
    if (!IsLocalController())
        return;

    if (ScoreWidgetClass)
    {
        ScoreWidget = CreateWidget<UScoreWidget>(this, ScoreWidgetClass);
        if (ScoreWidget)
        {
            ScoreWidget->AddToViewport();
        }
    }
}

void APaddlePlayerController::UpdateScoreUI()
{
    if (ScoreWidget)
    {
        ScoreWidget->SetPlayer1Score(Player1Score);
        ScoreWidget->SetPlayer2Score(Player2Score);
    }
}

void APaddlePlayerController::Move(const FInputActionValue& Value)
{
    if (PaddlePawn)
    {
        PaddlePawn->Move(Value);
    }
}
