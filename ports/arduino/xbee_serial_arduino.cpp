/*
 * Copyright (c) 2010-2012 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */
/**
    @addtogroup hal_posix
    @{
    @file xbee_serial_posix.c
    Serial Interface for XBee Module (POSIX Platform)

    This file was created by Tom Collins <Tom.Collins@digi.com> based on
    information from:

    http://www.easysw.com/~mike/serial/serial.html

    Serial Programming Guide for POSIX Operating Systems
    5th Edition, 6th Revision
    Copyright 1994-2005 by Michael R. Sweet

    @todo missing a way to hold Tx in break condition
*/
// NOTE: Documentation for these functions can be found in xbee/serial.h.

#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <xbee/serial.h>

#include <Arduino.h>

#define XBEE_SER_CHECK(ptr) \
    do { if (xbee_ser_invalid(ptr)) return -EINVAL; } while (0)


int xbee_ser_invalid( xbee_serial_t *serial)
{
    if (serial)
    {
        return 0;
    }
    return 1;
}


const char *xbee_ser_portname( xbee_serial_t *serial)
{
    if (serial == NULL)
    {
        return "(invalid)";
    }

    return "ArduinoStream";
}


int xbee_ser_write( xbee_serial_t *serial, const void FAR *buffer,
    int length)
{
    XBEE_SER_CHECK( serial);

    if (length < 0) 
    {
        return -EINVAL;
    }

    return Serial.write((const uint8_t*)buffer, length);
}


int xbee_ser_read( xbee_serial_t *serial, void FAR *buffer, int bufsize)
{
    int result;

    XBEE_SER_CHECK( serial);

    if (! buffer || bufsize < 0)
    {
        #ifdef XBEE_SERIAL_VERBOSE
            printf( "%s: buffer=%p, bufsize=%d; return -EINVAL\n", __FUNCTION__,
                buffer, bufsize);
        #endif
        return -EINVAL;
    }

    result = Serial.readBytes((uint8_t*)buffer, bufsize);

    #ifdef XBEE_SERIAL_VERBOSE
        printf( "%s: read %d bytes\n", __FUNCTION__, result);
        hex_dump( buffer, result, HEX_DUMP_FLAG_TAB);
    #endif

    return result;
}


int xbee_ser_putchar( xbee_serial_t *serial, uint8_t ch)
{
    int retval;

    retval = xbee_ser_write( serial, &ch, 1);
    if (retval == 1)
    {
        return 0;
    }
    else if (retval == 0)
    {
        return -ENOSPC;
    }
    else
    {
        return retval;
    }
}


int xbee_ser_getchar( xbee_serial_t *serial)
{
    uint8_t ch = 0;
    int retval;

    retval = xbee_ser_read( serial, &ch, 1);
    if (retval != 1)
    {
        return retval ? retval : -ENODATA;
    }

    return ch;
}


int xbee_ser_tx_free( xbee_serial_t *serial)
{
    XBEE_SER_CHECK( serial);
    return Serial.availableForWrite();
}


int xbee_ser_tx_used( xbee_serial_t *serial)
{
    XBEE_SER_CHECK( serial);
    return 0;
}


int xbee_ser_tx_flush( xbee_serial_t *serial)
{
    XBEE_SER_CHECK( serial);
    Serial.flush();
    return 0;
}


int xbee_ser_rx_free( xbee_serial_t *serial)
{
    XBEE_SER_CHECK( serial);
    return INT_MAX;
}


int xbee_ser_rx_used( xbee_serial_t *serial)
{
    XBEE_SER_CHECK( serial);
    return Serial.available();
}


int xbee_ser_rx_flush( xbee_serial_t *serial)
{
    XBEE_SER_CHECK( serial);
    // Do nothing.
    return 0;
}


int xbee_ser_baudrate( xbee_serial_t *serial, uint32_t baudrate)
{
    XBEE_SER_CHECK( serial);
    // Do nothing.
    return 0;
}


int xbee_ser_open( xbee_serial_t *serial, uint32_t baudrate)
{
    if (serial == NULL)
    {
        #ifdef XBEE_SERIAL_VERBOSE
            printf( "%s: NULL parameter, return -EINVAL\n", __FUNCTION__);
        #endif
        return -EINVAL;
    }

    Serial.begin(baudrate);

    return 0;
}


int xbee_ser_close( xbee_serial_t *serial)
{
    XBEE_SER_CHECK( serial);
    Serial.end();
    return 0;
}


int xbee_ser_break( xbee_serial_t *serial, int enabled)
{
    XBEE_SER_CHECK( serial);
    // Ignore this for now
    return 0;
}


int xbee_ser_flowcontrol( xbee_serial_t *serial, int enabled)
{
    XBEE_SER_CHECK( serial);
    // Ignore this for now
    return 0;
}


int xbee_ser_set_rts( xbee_serial_t *serial, int asserted)
{
    XBEE_SER_CHECK( serial);
    // Ignore this for now
    return 0;
}


int xbee_ser_get_cts( xbee_serial_t *serial)
{
    XBEE_SER_CHECK( serial);
    // Ignore this for now
    return 1; // clear to send
}

///@}
