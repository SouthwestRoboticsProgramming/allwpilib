// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <wpi/Twine.h>

#include "frc/MotorSafety.h"
#include "frc/PWM.h"
#include "frc/SpeedController.h"
#include "frc/smartdashboard/Sendable.h"
#include "frc/smartdashboard/SendableHelper.h"

namespace wpi {
class raw_ostream;
}  // namespace wpi

namespace frc {

/**
 * Common base class for all PWM Speed Controllers.
 */
class PWMSpeedController : public SpeedController,
                           public MotorSafety,
                           public Sendable,
                           public SendableHelper<PWMSpeedController> {
 public:
  PWMSpeedController(PWMSpeedController&&) = default;
  PWMSpeedController& operator=(PWMSpeedController&&) = default;

  /**
   * Set the PWM value.
   *
   * The PWM value is set using a range of -1.0 to 1.0, appropriately scaling
   * the value for the FPGA.
   *
   * @param speed The speed value between -1.0 and 1.0 to set.
   */
  void Set(double value) override;

  /**
   * Get the recently set value of the PWM. This value is affected by the
   * inversion property. If you want the value that is sent directly to the
   * SpeedController, use {@link PWM#getSpeed()} instead.
   *
   * @return The most recently set value for the PWM between -1.0 and 1.0.
   */
  double Get() const override;

  void SetInverted(bool isInverted) override;

  bool GetInverted() const override;

  void Disable() override;

  // MotorSafety interface
  void StopMotor() override;
  void GetDescription(wpi::raw_ostream& desc) const override;

  int GetChannel() const;

  /**
   * Write out the PID value as seen in the PIDOutput base object.
   *
   * @param output Write out the PWM value as was found in the PIDController
   */
  void PIDWrite(double output) override;

 protected:
  /**
   * Constructor for a PWM Speed Controller connected via PWM.
   *
   * @param name Name to use for SendableRegistry
   * @param channel The PWM channel that the controller is attached to. 0-9 are
   *                on-board, 10-19 are on the MXP port
   */
  PWMSpeedController(const wpi::Twine& name, int channel);

  void InitSendable(SendableBuilder& builder) override;

  PWM m_pwm;

 private:
  bool m_isInverted = false;
};

}  // namespace frc
