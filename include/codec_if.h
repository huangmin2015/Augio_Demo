/**
 * \file   codec_if.h
 *
 * \brief   Codec Interface APIs
 *
 *  This file contains the implementation of the AIC31 audio codec driver for
 *  DSP BIOS operating system.
 *
 *  (C) Copyright 2012, Texas Instruments, Inc
 */

/*
* Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef _CODEC_IF_H_
#define _CODEC_IF_H_

/**************************************************************************
**                       Macro Definitions
**************************************************************************/
/*
** Macros for configuring the interface Type
*/
#define CODEC_INTERFACE_I2C  /* Codec interface is I2C */

/**************************************************************************
**                      API function Prototypes
**************************************************************************/
extern void I2CCodecIfInit(unsigned int baseAddr, unsigned int intCh,
                           unsigned int slaveAddr);
/*
** Function to be used by codecs
*/
extern void CodecRegWrite(unsigned int baseAddr,unsigned char slaveAddr, unsigned char regAddr,
                          unsigned char regData);
extern void CodecRegBitSet(unsigned int baseAddr,unsigned char slaveAddr, unsigned char regAddr,
                           unsigned char bitMask);
extern void CodecRegBitClr(unsigned int baseAddr,unsigned char slaveAddr, unsigned char regAddr,
                           unsigned char bitMask);
extern unsigned char CodecRegRead(unsigned int baseAddr,unsigned char slaveAddr,
                                  unsigned char regAddr);
extern void CodecRegWrite_wm8960(unsigned int baseAddr, unsigned char slaveAddr,unsigned char regAddr,
                   unsigned int regData);

#endif

/***************************** End Of File ***********************************/
