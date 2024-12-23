# Automated Door Control Using CNN based Face Mask and Temperature Detection for COVID-19 Preventation

## Overview
This repository contains the implementation of a **Mask Detection and Door Control System** designed to enhance public safety during the COVID-19 pandemic. The system uses **deep learning**, **computer vision**, and **image processing** techniques to identify individuals wearing face masks and measure their body temperature. It integrates with automated door control systems to grant or deny access based on health compliance criteria.

The project demonstrates the potential of AI-driven solutions for combating health crises by enabling autonomous and precise monitoring systems.

---

## Features

- **Face Mask Detection**:
  - Real-time detection using TensorFlow and Keras models.
  - Differentiates between individuals wearing and not wearing masks.
  - Implements a two-stage detection process (face detection and mask verification).

- **Temperature Measurement**:
  - Contactless body temperature measurement using an infrared sensor.
  - Integrated with microcontrollers for real-time data collection.

- **Automated Door Control**:
  - Uses stepper motors for opening/closing doors based on detection results.
  - Ensures compliance by combining mask detection and temperature thresholds.

- **Region of Interest (ROI) Optimization**:
  - Ensures accurate detections within a predefined area.

- **Simulation and Testing**:
  - Includes Proteus simulations for hardware components.
  - Tested on real-world datasets for reliability and accuracy.

---

## Methodology

### 1. System Components
- **Hardware**:
  - High-definition USB camera for capturing frames.
  - Infrared temperature sensor (MLX90416) for contactless temperature measurement.
  - Arduino Mega 2560 microcontroller for hardware integration.
  - Stepper motor and ultrasonic sensor for door automation.

- **Software**:
  - Python with TensorFlow, Keras, and OpenCV for AI and image processing.
  - Proteus for hardware simulation.

### 2. Data Pipeline
- **Dataset**:
  - Collected 1900+ images for mask and no-mask classifications.
  - Data annotated using LabelImg for enhanced training.

- **Training**:
  - Face detection trained using MobileNet V2.
  - Mask detection trained using TensorFlow and Keras with a CNN-based approach.

- **Testing**:
  - Tested on live video streams and image datasets for high accuracy.

### 3. Control Logic
- **Face Mask Verification**:
  - Confidence threshold of 98% for mask detection.
- **Temperature Check**:
  - Allows entry for temperatures below 100°F.
- **Gate Operation**:
  - Logical AND gate operation to integrate detection results.
  - Automated motor control for opening/closing gates.

---

## Results

### Key Observations
- Achieved 98.6% accuracy in face mask detection.
- Reduced false negatives using a two-stage detection process.
- Successfully integrated temperature readings with mask detection for enhanced reliability.

### Hardware Performance
- Accurate temperature readings within 6 feet using the MLX90416 sensor.
- Smooth motor operations tested under varying duty cycles.

---

## Prerequisites

- **Hardware Requirements**:
  - Desktop computer with GPU (2GB VRAM minimum).
  - Arduino Mega 2560.
  - MLX90416 infrared sensor.
  - Stepper motor and ultrasonic sensor.

- **Software Requirements**:
  - Python 3.8 or later.
  - TensorFlow, Keras, OpenCV, and other dependencies listed in `requirements.txt`.
  - Proteus for hardware simulation.

---


## Repository Structure

```
mask-detection-door-control/
├── Arduino/
│   └── mask_detector.ino        # Arduino code for motor and sensor control
├── dataset/
│   └── ...                      # Dataset for training and testing
├── Diagrams/
│   └── Proteus files and circuit diagrams
├── Python codes/
│   ├── face_detector.py         # Main detection script
│   ├── train_model.py           # Training script
│   ├── temperature_sensor.py    # Temperature reading script
├── requirements.txt             # Python dependencies
├── LICENSE                      # Project license
└── README.md                    # Project documentation
```

---

## Future Work

- **Integration with Cloud Services**:
  - Real-time data logging and monitoring.
- **Facial Recognition**:
  - Identify individuals for attendance or security purposes.
- **Wireless Communication**:
  - Replace Arduino with ESP32 for wireless capabilities.

---

## License
This project is licensed under the MIT License - see the `LICENSE` file for details.
