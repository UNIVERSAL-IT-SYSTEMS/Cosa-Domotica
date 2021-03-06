/**
 * @file Domotica/RF433.hh
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
 * This file is part of the Arduino Che Cosa project.
 */

#ifndef COSA_DOMOTICA_RF433_HH
#define COSA_DOMOTICA_RF433_HH

/**
 * RF433 Configuration.
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
 * (RX/D7/D1)----------3-|DATA        |
 * (GND)---------------4-|GND         |
 *                       +------------+
 *
 *                         RF433/TX
 *                       +------------+
 * (TX/D6/D0)----------1-|DATA        |
 * (VCC)---------------2-|VCC         |                    V
 * (GND)---------------3-|GND         |                    |
 *                       |ANT       0-|--------------------+
 *                       +------------+       17.3 cm
 */

#ifndef SPEED
#define SPEED 4000
#endif

#if defined(BOARD_ATTINY)
#define RX Board::D1
#define TX Board::D0
#else
#define RX Board::D7
#define TX Board::D6
#endif

#endif
