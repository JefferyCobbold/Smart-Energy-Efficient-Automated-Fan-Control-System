# Motion and Temperature-Based Fan Control System

This project implements an automated dual-fan control system that uses motion detection and temperature monitoring to provide intelligent, energy-efficient cooling. The system integrates a **DHT11 temperature sensor**, **PIR motion sensor**, and **IRFZ44N MOSFET-based PWM fan driver**, along with a **16×2 I2C LCD** for real-time feedback.

## Features
- Automatic fan activation based on temperature or detected motion  
- PWM speed control using IRFZ44N MOSFET  
- Dual-fan setup (main fan + auxiliary cold-air fan)  
- LCD feedback for temperature, motion status, and fan states  
- Energy-efficient operation with motion timeout logic  

## Components
- **Arduino board**  
- **DHT11 Temperature Sensor**  
- **PIR Motion Sensor**  
- **IRFZ44N MOSFET** (PWM fan control)  
- **Main Fan**  
- **Cold-Air Fan**  
- **16×2 I2C LCD**  
- Flyback diode (for fan protection)  

## Circuit Overview
- DHT11 → Digital pin 11  
- PIR Sensor → Digital pin 12  
- Main Fan (PWM):  
  - Gate → Pin 6  
  - Drain → Fan negative  
  - Source → GND  
  - +12 V → Fan positive  
- Cold-Air Fan → Pin 3  
- LCD → I2C  
![FAN_SPEED_CONTROL_bb](https://github.com/user-attachments/assets/650e47b8-3f04-4bbe-a758-77cd82a621b2)



## System Logic

### Motion Control
- Motion detected → Both fans ON  
- No motion for 10 seconds → Fans OFF (unless temperature is high)

### Temperature Control
- Temp > 30°C → Fans ON  
- Temp < 27°C and no motion → Fans OFF  

### Fan Speed (PWM)
- 27–29°C → Medium speed  
- 30–32°C → High speed  
- >32°C → Maximum speed  

## LCD Output Example
Temp: 29C

Motion:YES C:ON




## Applications
- Smart home ventilation  
- Offices and public spaces  
- Equipment rooms  
- Greenhouse cooling systems  

## Advantages of IRFZ44N
- High current handling  
- Low Rds(on) → minimal heat losses  
- Fully logic-level compatible  
- Smooth PWM fan control  

## Conclusion
This system demonstrates an efficient and scalable approach to automated cooling using motion and temperature feedback. The IRFZ44N MOSFET enables reliable, high-performance PWM control, making the design suitable for larger fans and demanding environments.



https://github.com/user-attachments/assets/9f2a8f75-240c-421a-a13c-86358f12d07d



