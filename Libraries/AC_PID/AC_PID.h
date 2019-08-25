#pragma once

/// @file	AC_PID.h
/// @brief	Generic PID algorithm, with EEPROM-backed storage of constants.

#include <stdlib.h>
#include <AP_Math.h>
#include <Logger.h>

#define AC_PID_TFILT_HZ_DEFAULT  0.0f   // default input filter frequency
#define AC_PID_EFILT_HZ_DEFAULT  0.0f   // default input filter frequency
#define AC_PID_DFILT_HZ_DEFAULT  20.0f   // default input filter frequency

/// @class	AC_PID
/// @brief	Copter PID control class
class AC_PID {
public:

    // Constructor for PID
    AC_PID(float initial_p, float initial_i, float initial_d, float initial_ff, float initial_imax, float initial_filt_T_hz, float initial_filt_E_hz, float initial_filt_D_hz, float dt);

    // set_dt - set time step in seconds
    void set_dt(float dt);

    //  update_all - set target and measured inputs to PID controller and calculate outputs
    //  target and error are filtered
    //  the derivative is then calculated and filtered
    //  the integral is then updated based on the setting of the limit flag
    float update_all(float target, float measurement, bool limit = false);

    //  update_error - set error input to PID controller and calculate outputs
    //  target is set to zero and error is set and filtered
    //  the derivative then is calculated and filtered
    //  the integral is then updated based on the setting of the limit flag
    //  Target and Measured must be set manually for logging purposes.
    // todo: remove function when it is no longer used.
    float update_error(float error, bool limit = false);

    //  update_i - update the integral
    //  if the limit flag is set the integral is only allowed to shrink
    void update_i(bool limit);

    // get_pid - get results from pid controller
    float get_pid() const;
    float get_pi() const;
    float get_p() const;
    float get_i() const;
    float get_d() const;
    float get_ff();

    // todo: remove function when it is no longer used.
    float get_ff(float target);

    // reset_I - reset the integrator
    void reset_I();

    // reset_filter - input filter will be reset to the next value provided to set_input()
    void reset_filter() {
        _flags._reset_filter = true;
    }

    /// operator function call for easy initialisation
    void operator()(float p_val, float i_val, float d_val, float ff_val, float imax_val, float input_filt_T_hz, float input_filt_E_hz, float input_filt_D_hz, float dt);

    // get accessors
    float &kP() { return _kp; }
    float &kI() { return _ki; }
    float &kD() { return _kd; }
    float &ff() { return _kff;}
    float &filt_T_hz() { return _filt_T_hz; }
    float &filt_E_hz() { return _filt_E_hz; }
    float &filt_D_hz() { return _filt_D_hz; }
    float imax() const { return _kimax; }
    float get_filt_alpha(float filt_hz) const;
    float get_filt_T_alpha() const;
    float get_filt_E_alpha() const;
    float get_filt_D_alpha() const;

    // set accessors
    void kP(const float v) { _kp = v; }
    void kI(const float v) { _ki = v; }
    void kD(const float v) { _kd = v; }
    void ff(const float v) { _kff = v; }
    void imax(const float v) { _kimax = fabsf(v); }
    void filt_T_hz(const float v);
    void filt_E_hz(const float v);
    void filt_D_hz(const float v);

    // set the desired and actual rates (for logging purposes)
    void set_target_rate(float target) { _pid_info.target = target; }
    void set_actual_rate(float actual) { _pid_info.actual = actual; }

    // integrator setting functions
    void set_integrator(float target, float measurement, float i);
    void set_integrator(float error, float i);
    void set_integrator(float i) { _integrator = constrain_float(i, -_kimax, _kimax); }

    const PID_Info& get_pid_info(void) const { return _pid_info; }

protected:

    // parameters
    float _kp;
    float _ki;
    float _kd;
    float _kff;
    float _kimax;
    float _filt_T_hz;         // PID target filter frequency in Hz
    float _filt_E_hz;         // PID error filter frequency in Hz
    float _filt_D_hz;         // PID derivative filter frequency in Hz

    // flags
    struct ac_pid_flags {
        bool _reset_filter :1; // true when input filter should be reset during next call to set_input
    } _flags;

    // internal variables
    float _dt;                // timestep in seconds
    float _integrator;        // integrator value
    float _target;            // target value to enable filtering
    float _error;             // error value to enable filtering
    float _derivative;        // derivative value to enable filtering

    PID_Info _pid_info;
};
