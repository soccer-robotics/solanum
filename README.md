<img src=https://user-images.githubusercontent.com/30610197/219515089-ddc62347-1ecf-4351-8793-f94fc709403c.png width=300>

## C++ code for Radian 2023

Build on Platformio; source files stored in `/src`

## Components
| Component | File | Description | Progress |
|-|-|-|-|
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/motion.cpp>Motion</a> | `motion.h` | Take movement angle and speed and output motor commands | Finished |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/solenoid.cpp>Solenoid</a> | `solenoid.h` | Charge and fire solenoid | Not started |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/infra.cpp>Infrared</a> | `infra.h` | Get infrared sensor readings and calculate ball heading/distance | Finished |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/gyro.cpp>Gyro</a> | `gyro.h` | Get compass (IMU) readings | Finished |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/line.cpp>Line</a> | `line.h` | Read line sensors and calculate line edge | Finished |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/ultra.cpp>Ultrasound</a> | `ultra.h` | Get ultrasound readings and calculate approximate position | In Progress |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/cam.cpp>Camera</a> | `cam.h` | Interface with OpenMV and get goal angles | Not started |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/blue.cpp>Bluetooth</a> | `blue.h` | Inter-robot communications | Not started
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/orbit.cpp>Orbit</a> | `orbit.h` | Calculate optimal robot trajectories (Offense) | In Progress |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/goalie.cpp>Goalie</a> | `goalie.h` | Calculate optimal robot trajectories (Defense) | In Progress |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/constants.hpp>Constants</a> | `constants.hpp` | Stores program constants (ex. pin numbers) | In progress |
| <a href=https://github.com/soccer-robotics/solanum/blob/master/src/main.cpp>Main</a> | `main.cpp` | Main program | In progress |

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
