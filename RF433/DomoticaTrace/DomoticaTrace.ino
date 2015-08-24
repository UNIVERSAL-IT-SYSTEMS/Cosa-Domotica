/**
 * @file DomoticaTrace.ino
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2015, Mikael Patel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * @section Description
 * Domotica demonstration sketch; Recieve messages and print to UART.
 *
 * @section Circuit
 * @code
 *                         RF433/RX                       V
 *                       +------------+                   |
 *                       |0-----------|-------------------+
 *                       |ANT         |       17.3 cm
 *                       |            |
 *                       |            |
 *                       |            |
 *                       |            |
 * (VCC)---------------1-|VCC         |
 *                     2-|DATA        |
 * (RX/D7)-------------3-|DATA        |
 * (GND)---------------4-|GND         |
 *                       +------------+
 * @endcode
 *
 * This file is part of the Arduino Che Cosa project.
 */

#include <Domotica.h>
#include <Domotica/RF433.h>

// Default device address
#define DEVICE 0x01

// RF433 includes; Virtual Wire Wireless Interface and Huffman(7,4) codec
#include <VWI.h>
#include <HammingCodec_7_4.h>

HammingCodec_7_4 codec;
VWI rf(NETWORK, DEVICE, SPEED, RX, TX, &codec);

// Sketch includes
#include "Cosa/RTC.hh"
#include "Cosa/Time.hh"
#include "Cosa/Trace.hh"
#include "Cosa/IOStream/Driver/UART.hh"

void setup()
{
  Domotica::begin(&rf);
  uart.begin(9600);
  trace.begin(&uart, PSTR("DomoticaTrace: started"));
  time_t::epoch_year(2015);
  rf.powerup();
}

void loop()
{
  const uint32_t TIMEOUT = 60000L;
  Domotica::msg_t msg;
  uint8_t src;
  uint8_t port;
  int res = rf.recv(src, port, &msg, sizeof(msg), TIMEOUT);
  if (res < 0) return;

  trace << RTC::millis()
	<< PSTR(":src=") << hex << src
	<< PSTR(",port=") << hex << port
	<< PSTR(",dest=")
	<< hex << (rf.is_broadcast() ? 0 : rf.get_device_address())
	<< PSTR(",id=") << msg.id
	<< PSTR(",nr=") << msg.nr
	<< PSTR(",vcc=") << msg.battery
	<< PSTR(",len=") << res
	<< PSTR(":");

  switch (port) {
  case Domotica::INFO_STRING_MSG:
    trace << (Domotica::InfoString::msg_t*) &msg;
    break;
  case Domotica::DIGITAL_PIN_MSG:
    trace << (Domotica::DigitalPin::msg_t*) &msg;
    break;
  case Domotica::DIGITAL_PINS_MSG:
    trace << (Domotica::DigitalPins::msg_t*) &msg;
    break;
  case Domotica::ANALOG_PIN_MSG:
    trace << (Domotica::AnalogPin::msg_t*) &msg;
    break;
  case Domotica::TEMPERATURE_SENSOR_MSG:
    trace << (Domotica::TemperatureSensor::msg_t*) &msg;
    break;
  case Domotica::HUMIDITY_TEMPERATURE_SENSOR_MSG:
    trace << (Domotica::HumidityTemperatureSensor::msg_t*) &msg;
    break;
  case Domotica::REALTIME_CLOCK_MSG:
    trace << (Domotica::RealTimeClock::msg_t*) &msg;
    break;
  default:
    ;
  }
  trace << endl;
  trace.print((uint32_t) &msg, &msg, res, IOStream::hex);
}
