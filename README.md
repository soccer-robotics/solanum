# Solanum
## C++ code for Radian 2023

Build on Platformio; source files stored in `/src`

## Components
| Component | File | Description | Progress |
|-|-|-|-|
| Motion | `motion.h` | Take movement angle and speed and output motor commands | In progress |
| Solenoid | `solenoid.h` | Charge and fire solenoid | Not started |
| Infrared | `infra.h` | Get infrared sensor readings and calculate ball heading/distance | Not started |
| Gyro | `gyro.h` | Get compass (IMU) readings | Not started |
| Line | `line.h` | Read line sensors and calculate line edge | Not started |
| Ultrasound | `ultra.h` | Get ultrasound readings and calculate approximate position | Not started |
| Camera | `cam.h` | Interface with OpenMV and get goal angles | Not started |
| Bluetooth | `blue.h` | Inter-robot communications | Not started
| Orbit | `orbit.h` | Calculate optimal robot trajectories (Offense) | Not started |
| Goalie | `goalie.h` | Calculate optimal robot trajectories (Defense) | Not started |
| Constants | `constants.h` | Stores program constants (ex. pin numbers) | In progress |
| Main | `main.cpp` | Main program | In progress |

## Checklist
- [ ] The entire codebase is basically empty
- [x] Set up skeleton

Copyright Jieruei Chang 2023