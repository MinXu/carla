// CARLA, Copyright (C) 2017 Computer Vision Center (CVC)

#pragma once

#include "CoreMinimal.h"
#include "AI/WheeledVehicleAIController.h"
#include "WheeledVehicleController.generated.h"

class UCameraComponent;
class USpringArmComponent;

/// Wheeled vehicle controller with cameras and optional user input.
UCLASS()
class CARLA_API AWheeledVehicleController : public AWheeledVehicleAIController
{
  GENERATED_BODY()

  // ===========================================================================
  /// @name Constructor
  // ===========================================================================
  /// @{
public:

  AWheeledVehicleController(const FObjectInitializer& ObjectInitializer);

  ~AWheeledVehicleController();

  /// @}
  // ===========================================================================
  /// @name AActor overrides
  // ===========================================================================
  /// @{
public:

  virtual void BeginPlay() override;

  /// @}
  // ===========================================================================
  /// @name APlayerController overrides
  // ===========================================================================
  /// @{
public:

  virtual void SetupInputComponent() override;

  virtual void Possess(APawn *aPawn) override;

  virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

  /// @}
  // ===========================================================================
  /// @name User input
  // ===========================================================================
  /// @{
public:

  /// Enable keyboard control.
  UFUNCTION(Category = "Vehicle User Input", BlueprintCallable)
  void EnableUserInput(bool Enable);

  /// @}
  // ===========================================================================
  /// @name Camera movement
  // ===========================================================================
  /// @{
private:

  void ChangeCameraZoom(float Value);

  void ChangeCameraUp(float Value);

  void ChangeCameraRight(float Value);

  void EnableOnBoardCamera(bool bEnable = true, bool bForce = false);

  void ToggleCamera()
  {
    EnableOnBoardCamera(!bOnBoardCameraIsActive);
  }

  /// @}
  // ===========================================================================
  /// @name Vehicle movement
  // ===========================================================================
  /// @{
private:

  void SetThrottleInput(float Value);

  void SetSteeringInput(float Value);

  void SetBrakeInput(float Value);

  void ToggleReverse();

  void HoldHandbrake();

  void ReleaseHandbrake();

  /// @}
  // ===========================================================================
  // -- Member variables -------------------------------------------------------
  // ===========================================================================
private:

  UPROPERTY(EditAnywhere)
  USpringArmComponent *SpringArm;

  UPROPERTY(EditAnywhere)
  UCameraComponent *PlayerCamera;

  UPROPERTY(EditAnywhere)
  UCameraComponent *OnBoardCamera;

  UPROPERTY()
  bool bOnBoardCameraIsActive = false;

  UPROPERTY(Category = "Vehicle User Input", VisibleAnywhere)
  bool bAllowUserInput = false;
};