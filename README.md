levitating_pingpong
===================

Levitating ping-pong ball in a transparent plastic tube using a ventilator, an infrared sensor and a MSP430 microcontroller, that implements a fuzzy regulator alogrithm.

The goal is to make a ping-pong ball float in a transparent plastic tube at a specified distance relative to the proximity sensor (infrared). The ball should float with minimum oscillations. A small ventilator at the base of the tube is used to push the ball up.

The fan has a brushless motor controlled through a driver that accepts a PWM signal from a microcontroller. The driver is basically a low-pass filter and a bipolar transistor that works in the active region. The fan datasheet specifically said that it can't be controlled directly with a PWM signal.

The infrared sensor outputs an analog signal that is read by the ADC of the microcontroller. Serial communication with the PC allows a user to specify the floating distance and view the distance read from sensor for debugging purposes.

The tube is about 35 cm long, 4.6 cm in diameter. The ball has 4 cm in diameter. The sensor is placed at the top of the tube, right on the top hole of the tube, letting the air to pass by. The sensor can measure distances from 4 cm to 30 cm. I have placed a thin wire in the tube to limit the ball from ever reaching distances below 4 cm relative to the sensor.
