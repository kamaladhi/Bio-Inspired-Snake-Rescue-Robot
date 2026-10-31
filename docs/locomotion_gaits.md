# Locomotion Gaits and Mathematical Formulations

This document describes the kinematic formulation and wave equations used for controlling the modular snake robot.

---

## 1. Serpenoid Curve (Hirose's Formulation)

Snake locomotion is biologically modelled using Shigeo Hirose's serpenoid curve, where the curvature along the body changes sinusoidally with respect to body length $s$:

$$\kappa(s) = -\frac{2 K_n \pi}{L} \sin\left(\frac{2 \pi s}{L}\right)$$

For discrete modular snake robots with $N$ rigid segments connected by revolute joints, the joint angles $\theta_i(t)$ are controlled via discrete traveling waves.

---

## 2. Lateral Undulation (Slithering)

Lateral undulation is the standard slithering motion where horizontal joints propagate a sinusoidal wave from head to tail.

### Joint Equation

For joint index $j \in \{0, 1, \dots, N-1\}$:

$$\theta_j(t) = A \cdot \sin(\omega t + j \cdot \phi) + \theta_0$$

Where:
- $A$: Wave amplitude (degrees, typically 30°–45°)
- $\omega$: Temporal angular frequency ($2\pi f$)
- $\phi$: Inter-segment spatial phase lag ($\pi / 2$ for 90° phase shift between segments)
- $\theta_0$: Offset angle (neutral position = 90°)
- $t$: Discrete time step index

### Direction Control:
- **Forward**: Wave travels from head to tail ($+j \cdot \phi$).
- **Backward**: Wave travels from tail to head (negate spatial phase offset $-j \cdot \phi$).

---

## 3. Sidewinding Locomotion

Sidewinding utilizes two orthogonal waves: horizontal (yaw) and vertical (pitch) with a phase shift of $\pi/2$ (90°) between them. This lifts alternating segments off the ground while the remaining segments push laterally, ideal for low-friction or sandy terrain.

### Joint Equations

- **Horizontal joints (Yaw):**
  $$\theta_{h, j}(t) = A_h \cdot \sin(\omega t + j \cdot \phi) + \theta_0$$

- **Vertical joints (Pitch):**
  $$\theta_{v, j}(t) = A_v \cdot \sin\left(\omega t + j \cdot \phi + \frac{\pi}{2}\right) + \theta_0$$

Where:
- $A_h$: Horizontal amplitude
- $A_v$: Vertical amplitude (controls ground clearance)
- $\frac{\pi}{2}$: Constant 90° phase difference between vertical and horizontal axes.

---

## 4. Sidewinding Turn (Steering)

Turning during sidewinding is achieved by introducing an angular bias (offset $\Delta\theta$) or differential amplitude between segments:

$$\theta_{h, j}(t) = A_h \cdot \sin(\omega t + j \cdot \phi) + \theta_0 + \Delta\theta_{\text{turn}}$$

- $\Delta\theta_{\text{turn}} > 0$: Steer Right
- $\Delta\theta_{\text{turn}} < 0$: Steer Left

---

## 5. Arduino Implementation Parameter Mapping

| Parameter | Arduino Variable | Typical Value | Notes |
|-----------|------------------|---------------|-------|
| Base offset | `offset` / `neutral` | 90° | Servo zero position |
| Slither Amplitude | `amplitude` | 30° – 40° | Maximum joint deflection |
| Sidewind Horiz Amp | `ampH` | 35° | Lateral sweep |
| Sidewind Vert Amp | `ampV` | 20° | Ground clearance lift |
| Step delay | `delayTime` | 20 – 40 ms | Determines gait speed |
| Phase lag | `lag` | $\pi / 2$ (1.57 rad) | Segment-to-segment phase |
