<img src=https://user-images.githubusercontent.com/30610197/219515089-ddc62347-1ecf-4351-8793-f94fc709403c.png width=300>

## C++ code for Radian 2023

Build on Platformio; source files stored in `/src`

## Components
| Component | File | Description | Progress |
|-|-|-|-|
| Motion | `motion.h` | Take movement angle and speed and output motor commands | Finished |
| Solenoid | `solenoid.h` | Charge and fire solenoid | Not started |
| Infrared | `infra.h` | Get infrared sensor readings and calculate ball heading/distance | Finished |
| Gyro | `gyro.h` | Get compass (IMU) readings | Finished |
| Line | `line.h` | Read line sensors and calculate line edge | Finished |
| Ultrasound | `ultra.h` | Get ultrasound readings and calculate approximate position | In Progress |
| Camera | `cam.h` | Interface with OpenMV and get goal angles | Not started |
| Bluetooth | `blue.h` | Inter-robot communications | Not started
| Orbit | `orbit.h` | Calculate optimal robot trajectories (Offense) | In Progress |
| Goalie | `goalie.h` | Calculate optimal robot trajectories (Defense) | In Progress |
| Constants | `constants.hpp` | Stores program constants (ex. pin numbers) | In progress |
| Main | `main.cpp` | Main program | In progress |

## Checklist
- [ ] Solenoid
- [ ] Lightgate
- [ ] Bluetooth
- [ ] Ultrasound integration
- [ ] Ultrasound interfacing
- [ ] Line reliability
- [ ] Goalie
- [x] Orbit
- [x] Line Clamping
- [x] Line Sensor reading
- [x] Infrared reliability
- [x] Basic Infrared code
- [x] BNO055 interfacing
- [x] Preliminary motor code
- [x] Set up skeleton