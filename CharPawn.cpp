// Fill out your copyright notice in the Description page of Project Settings.

#include "CharPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Vector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"


// Sets default values
ACharPawn::ACharPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
    UCameraComponent * CameraPawn = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Pawn"));
    VisibleActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Moosh"));
    arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    CharMove = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("Character Movement"));
    //VisibleActor->SetStaticMesh(Cube)
    CameraPawn->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
    CameraPawn->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
    
    arm->AttachTo(RootComponent);
    CameraPawn->AttachTo(VisibleActor);
    VisibleActor->AttachTo(RootComponent);
    
    arm->TargetArmLength = 300.0f;
    arm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
    
    arm->bEnableCameraLag = true;
    arm->CameraLagSpeed = 2;
    arm-> CameraLagMaxDistance = 1.5f;
    
    arm->bEnableCameraRotationLag = true;
    arm->CameraRotationLagSpeed = 4;
    arm->CameraLagMaxTimeStep = 1;
    
    timero = 0.0f;
    ScoreLimit = 0;
    
    CameraPawn->AttachTo(arm, USpringArmComponent::SocketName);
    
    FRotator NewRotation = GetActorRotation();
    
    VisibleScale = VisibleActor->GetComponentScale().X;
    
    ObjRot = GetActorRotation();
    relativeRot = armRot - ObjRot;
    //FRotator NewRotationY = FRotator(1.0f, 0.0f, 0.0f);
    //FQuat QuertRotation = FQuat(NewRotationY);
}

// Called when the game starts or when spawned
void ACharPawn::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ACharPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ForwardVector = VisibleActor->GetForwardVector();
    ForwardVelocity = GetActorForwardVector() + 0, 1000, 0;
    BackVelocity = GetActorForwardVector() - 0, 1, 0;
    
    if(!CurrentVelocity.IsZero())
    {
        FVector NewLocation = GetActorLocation() + (ForwardVelocity * DeltaTime * MovementSpeed);
        SetActorLocation(NewLocation);
    }
    
    ActorLocation = GetActorLocation();
    
    /*NewRotation.Pitch += 1.0f;
     VisibleActor->AddLocalRotation(NewRotation, false, 0, ETeleportType::None);
     NewRotation = GetActorRotation();
     */
    
    if(Growing == true){
        VisibleScale += DeltaTime;
    }
    else{
        VisibleScale -= DeltaTime;
    }
    
    ImpulseValue = 50000000000000000000000.0f;
    
    OffsetVector = GetActorForwardVector() + MovementSpeed;
    
    VisibleScale = FMath::Clamp(VisibleScale, 0.5f, 2.0f);
    VisibleActor->SetWorldScale3D(FVector(VisibleScale));
    
    ImpulseLocation = VisibleActor->GetComponentLocation() - 10.0f, 0.0f, 0.0f;
    if(Score < ScoreLimit){
        if (Done == false)
            timero += DeltaTime;
    }
    if(Score >= ScoreLimit){
        Done == true;
    }
}

// Called to bind functionality to input
void ACharPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
    InputComponent->BindAxis("MoveX", this, &ACharPawn::MoveX);
    InputComponent->BindAxis("MoveY", this, &ACharPawn::MoveY);
    InputComponent->BindAxis("MoveZ", this, &ACharPawn::MoveZ);
    InputComponent->BindAxis("MouseX", this, &ACharPawn::MouseX);
    InputComponent->BindAxis("MouseY", this, &ACharPawn::MouseY);
    //InputComponent->BindAction("Heal", IE_Pressed, this, &APawn::Heal);
    //InputComponent->BindAction("Fire", IE_Pressed, this, &APawn::NoHeal);
}

void ACharPawn::MoveX(float AxisValue)
{
    if(Score < ScoreLimit){
        CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * MovementSpeed;
        SetActorLocation(GetActorLocation() + FVector(AxisValue * MovementSpeed, 0.0f, 0.0f));
        
    }
    //SetActorRelativeLocation(GetActorLocation() + FVector(AxisValue * MovementSpeed, 0.0f, 0.0f));
    //VisibleActor->AddLocalLocation(FVector(AxisValue, 0, 0));
    //VisibleActor->AddLocalRotation(FRotator(AxisValue, 0, 0));
    //arm->AddLocalRotation(FRotator(AxisValue, 0, 0));
}
void ACharPawn::MoveY(float AxisValue)
{
    if(Score < ScoreLimit){
        CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * MovementSpeed;
        SetActorLocation(GetActorLocation() + FVector(0.0f, AxisValue * MovementSpeed, 0.0f));
    }
    //VisibleActor->AddLocalRotation(FRotator(0, AxisValue, 0));
    //arm->AddLocalRotation(FRotator(0, AxisValue, 0));
}
void ACharPawn::MoveZ(float AxisValue)
{
    if(Score < ScoreLimit){
        CurrentVelocity.Z = FMath::Clamp(AxisValue, -1.0f, 1.0f) * MovementSpeed;
        SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, AxisValue * MovementSpeed));
    }
}
void ACharPawn::Heal()
{
    //Growing = true;
    //VisibleActor->AddImpulse(ForwardVector * ImpulseValue * VisibleActor->GetMass());
}
void ACharPawn::NoHeal(){
    //Growing = false;
}
void ACharPawn::MouseX(float value){
    /* float temp = relativeRot.Pitch + value;
     if(temp <  25 && temp > -65){
     arm->AddLocalRotation(FRotator(0, value, 0));
     VisibleActor->AddLocalRotation(FRotator(0, value, 0));
     }*/
}
void ACharPawn::MouseY(float value){
    /*float temp = relativeRot.Yaw + value;
     if(temp <  3 && temp > -5){
     arm->AddLocalRotation(FRotator(value, 0, 0));
     VisibleActor->AddLocalRotation(FRotator(value, 0, 0));
     */
}
void ACharPawn::AddCoins(){
    Score = Score + 1;
    //  SetActorLocation(GetActorLocation() + FVector(100.0f, 100.0f, 100.0f));
    if(GEngine){
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OverlapBegin"));
    }
}

