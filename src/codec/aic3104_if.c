/**
 * \file       Aic31_if.c
 *
 * \brief       APIs to configure the AIC31 codec
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

/* ========================================================================== */
/*                            INCLUDE FILES                                   */
/* ========================================================================== */
#include <codec_if.h>
#include "aic31_if.h"
#include <ICodec.h>

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
/*
** Register Address for AIC31 Codec
*/
#define AIC31_P0_REG0               (0)  /* Page Select  */
#define AIC31_P0_REG1               (1)  /* Software Reset */
#define AIC31_P0_REG2               (2)  /* Codec Sample Rate Select */
#define AIC31_P0_REG3               (3)  /* PLL Programming A */
#define AIC31_P0_REG4               (4)  /* PLL Programming B */
#define AIC31_P0_REG5               (5)  /* PLL Programming C */
#define AIC31_P0_REG6               (6)  /* PLL Programming D */
#define AIC31_P0_REG7               (7)  /* Codec Datapath Setup */
#define AIC31_P0_REG8               (8)  /* Audio Serial Data I/f Control A */
#define AIC31_P0_REG9               (9)  /* Audio Serial Data I/f Control B */
#define AIC31_P0_REG10              (10) /* Audio Serial Data I/f Control C */
#define AIC31_P0_REG11              (11) /* Audio Codec Overflow Flag */
#define AIC31_P0_REG12              (12) /* Audio Codec Digital Filter Ctrl */
#define AIC31_P0_REG13              (13) /* Headset / Button Press Detect A */
#define AIC31_P0_REG14              (14) /* Headset / Button Press Detect B */
#define AIC31_P0_REG15              (15) /* Left ADC PGA Gain Control */
#define AIC31_P0_REG16              (16) /* Right ADC PGA Gain Control */
#define AIC31_P0_REG17              (17) /* MIC3L/R to Left ADC Control */
#define AIC31_P0_REG18              (18) /* MIC3L/R to Right ADC Control */
#define AIC31_P0_REG19              (19) /* LINE1L to Left ADC Control */
#define AIC31_P0_REG20              (20) /* LINE2L to Left ADC Control */
#define AIC31_P0_REG21              (21) /* LINE1R to Left ADC Control */
#define AIC31_P0_REG22              (22) /* LINE1R to Right ADC Control */
#define AIC31_P0_REG23              (23) /* LINE2R to Right ADC Control */
#define AIC31_P0_REG24              (24) /* LINE1L to Right ADC Control */
#define AIC31_P0_REG25              (25) /* MICBIAS Control */
#define AIC31_P0_REG26              (26) /* Left AGC Control A */
#define AIC31_P0_REG27              (27) /* Left AGC Control B */
#define AIC31_P0_REG28              (28) /* Left AGC Control C */
#define AIC31_P0_REG29              (29) /* Right AGC Control A */
#define AIC31_P0_REG30              (30) /* Right AGC Control B */
#define AIC31_P0_REG31              (31) /* Right AGC Control C */
#define AIC31_P0_REG32              (32) /* Left AGC Gain */
#define AIC31_P0_REG33              (33) /* Right AGC Gain */
#define AIC31_P0_REG34              (34) /* Left AGC Noise Gate Debounce */
#define AIC31_P0_REG35              (35) /* Right AGC Noise Gate Debounce */
#define AIC31_P0_REG36              (36) /* ADC Flag */
#define AIC31_P0_REG37              (37) /* DAC Power and Output Driver Control */
#define AIC31_P0_REG38              (38) /* High Power Output Driver Control*/
#define AIC31_P0_REG40              (40) /* High Power Output Stage Control*/
#define AIC31_P0_REG41              (41) /* DAC Output Switching Control */
#define AIC31_P0_REG42              (42) /* Output Driver Pop Reduction */
#define AIC31_P0_REG43              (43) /* Left DAC Digital Volume Control */
#define AIC31_P0_REG44              (44) /* Right DAC Digital Volume Control */
#define AIC31_P0_REG45              (45) /* LINE2L to HPLOUT Volume Control */
#define AIC31_P0_REG46              (46) /* PGA_L to HPLOUT Volume Control */
#define AIC31_P0_REG47              (47) /* DAC_L1 to HPLOUT Volume Control */
#define AIC31_P0_REG48              (48) /* LINE2R to HPLOUT Volume Control */
#define AIC31_P0_REG49              (49) /* PGA_R to HPLOUT Volume Control */
#define AIC31_P0_REG50              (50) /* DAC_R1 to HPLOUT Volume Control */
#define AIC31_P0_REG51              (51) /* HPLOUT Output Level Control */
#define AIC31_P0_REG52              (52) /* LINE2L to HPLCOM Volume Control */
#define AIC31_P0_REG53              (53) /* PGA_L to HPLCOM Volume Control */
#define AIC31_P0_REG54              (54) /* DAC_L1 to HPLCOM Volume Control */
#define AIC31_P0_REG55              (55) /* LINE2R to HPLCOM Volume Control */
#define AIC31_P0_REG56              (56) /* PGA_R to HPLCOM Volume Control */
#define AIC31_P0_REG57              (57) /* DAC_R1 to HPLCOM Volume Control */
#define AIC31_P0_REG58              (58) /* HPLCOM Output Level Control */
#define AIC31_P0_REG59              (59) /* LINE2L to HPROUT Volume Control */
#define AIC31_P0_REG60              (60) /* PGA_L to HPROUT Volume Control */
#define AIC31_P0_REG61              (61) /* DAC_L1 to HPROUT Volume Control */
#define AIC31_P0_REG62              (62) /* LINE2R to HPROUT Volume Control */
#define AIC31_P0_REG63              (63) /* PGA_R to HPROUT Volume Control  */
#define AIC31_P0_REG64              (64) /* DAC_R1 to HPROUT Volume Control */
#define AIC31_P0_REG65              (65) /* HPROUT Output Level Control */
#define AIC31_P0_REG66              (66) /* LINE2L to HPRCOM Volume Control  */
#define AIC31_P0_REG67              (67) /* PGA_L to HPRCOM Volume Control */
#define AIC31_P0_REG68              (68) /* DAC_L1 to HPRCOM Volume Control */
#define AIC31_P0_REG69              (69) /* LINE2R to HPRCOM Volume Control */
#define AIC31_P0_REG70              (70) /* PGA_R to HPRCOM Volume Control */
#define AIC31_P0_REG71              (71) /* DAC_R1 to HPRCOM Volume Control */
#define AIC31_P0_REG72              (72) /* HPRCOM Output Level Control */
#define AIC31_P0_REG73              (73) /* LINE2L to MONO_LOP/M Volume Control*/
#define AIC31_P0_REG74              (74) /* PGA_L to MONO_LOP/M Volume Control */
#define AIC31_P0_REG75              (75) /* DAC_L1 to MONO_LOP/M Volume Control */
#define AIC31_P0_REG76              (76) /* LINE2R to MONO_LOP/M Volume Control */
#define AIC31_P0_REG77              (77) /* PGA_R to MONO_LOP/M Volume Control */
#define AIC31_P0_REG78              (78) /* DAC_R1 to MONO_LOP/M Volume Control */
#define AIC31_P0_REG79              (79) /* MONO_LOP/M Output Level Control */
#define AIC31_P0_REG80              (80) /* LINE2L to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG81              (81) /* PGA_L to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG82              (82) /* DAC_L1 to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG83              (83) /* LINE2R to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG84              (84) /* PGA_R to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG85              (85) /* DAC_R1 to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG86              (86) /* LEFT_LOP/M Output Level Control */
#define AIC31_P0_REG87              (87) /* LINE2L to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG88              (88) /* PGA_L to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG89              (89) /* DAC_L1 to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG90              (90) /* LINE2R to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG91              (91) /* PGA_R to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG92              (92) /* DAC_R1 to RIGHT_LOP/M Volume Control*/
#define AIC31_P0_REG93              (93) /* RIGHT_LOP/M Output Level Control */
#define AIC31_P0_REG94              (94) /* Module Power Status */
#define AIC31_P0_REG95              (95) /**< O/P Driver Short Circuit Detection Status*/
#define AIC31_P0_REG96              (96) /* Sticky Interrupt Flags */
#define AIC31_P0_REG97              (97) /* Real-time Interrupt Flags  */
#define AIC31_P0_REG98              (98) /* GPIO1 Control */
#define AIC31_P0_REG99              (99) /* GPIO2 Control */
#define AIC31_P0_REG100             (100)  /* Additional GPIO Control A */
#define AIC31_P0_REG101             (101)  /* Additional GPIO Control B */
#define AIC31_P0_REG102             (102)  /* Clock Generation Control */
#define AIC31_P0_REG109             (109)  /* DAC Quiescent Current Adjustment */

#define AIC31_RESET                 (0x80)

#define AIC31_SLOT_WIDTH_16         (0u << 4u)
#define AIC31_SLOT_WIDTH_20         (1u << 4u)
#define AIC31_SLOT_WIDTH_24         (2u << 4u)
#define AIC31_SLOT_WIDTH_32         (3u << 4u)
    unsigned int regval=0;
/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
/**
 * \brief   Resets the AIC31 Codec
 *
 * \param   baseAddr     Base Address of the interface connected to AIC31
 *
 * \return  None.
 *
 **/
 void wm8960_init(unsigned int baseAddr)
{


    // ����
    CodecRegWrite1(baseAddr, 0xf, 0x0);
    // ���õ�Դ   /*电源*/
    CodecRegWrite1(baseAddr, 0x19, 1<<8 | 1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1);
   // CodecRegWrite1(baseAddr, 0x19, 1<<8 | 1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1);
    CodecRegWrite1(baseAddr, 0x1a, 1<<8 | 1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1);
    CodecRegWrite1(baseAddr, 0x2F, 1<<5 | 1<<4 | 1<<3 | 1<<2 );

    //ADCLRC/GPIO Pin For GPIO; ADCCLK From  DACClK
    CodecRegWrite1(baseAddr, 0x9, 0x40);
    // ����ʱ��   clk
    //Mclk--div1-->SYSCLK---DIV256--->DAC/ADC sample Freq=11.289(MCLK)/256=44.1KHZ
    //CodecRegWrite(baseAddr, 0x4, 0x0);
	CodecRegWrite1(baseAddr, 0x4, 0x04);  //sysclk=22.5792(MCLK)/(2)=11.289MHz Freq=11.289(MCLK)/256=44.1KHZ

    // ����ADC-DAC
    CodecRegWrite1(baseAddr, 0x5, 0x0);

    CodecRegWrite1(baseAddr, 0x15, 0x1ff);
    CodecRegWrite1(baseAddr, 0x16, 0x1ff);


    // ����audio interface
    /* data format: I2S
       word length: 32 bits  */
    CodecRegWrite1(baseAddr, 0x7, 0x0e);

    // ����OUTPUTS   //volume
    CodecRegWrite1(baseAddr, 0x2, 0xFF | 0x100);
    CodecRegWrite1(baseAddr, 0x3, 0xFF | 0x100);
    //set by pass
    //Letf DAC to Left Output Mixer
    CodecRegWrite1(baseAddr, 0x22,  1 <<8);
    //Right DAC to Right Output Mixer
    CodecRegWrite1(baseAddr, 0x25,  1 <<8 );
    //Reserved
    CodecRegWrite1(baseAddr, 0x26, 1 <<7 );
    CodecRegWrite1(baseAddr, 0x27, 1 <<7 );
    //Letf Speaker Volume
    CodecRegWrite1(baseAddr, 0x28, 0xf9 | 0x100);
    //Right Speaker Volume
    CodecRegWrite1(baseAddr, 0x29, 0xf9 | 0x100);
    //by pass setup
    //CodecRegWrite1(baseAddr, 0x2d, 1 <<7 );
    //CodecRegWrite1(baseAddr, 0x2e, 1 <<7 );
    //class D Control  L/R Speakers enabled
    CodecRegWrite1(baseAddr, 0x31,  1 <<7 | 1<<6 );

    //setup input  INPUT1 INPUT2 INPUT3 CONNECTED TO ADC
    CodecRegWrite1(baseAddr, 0x20, 1<<8 | 1 <<7 | 1 <<6  | 1 <<3);
    CodecRegWrite1(baseAddr, 0x21, 1<<8 | 1 <<7 | 1 <<6  | 1 <<3);

    CodecRegWrite1(baseAddr, 0x00, 0x117);
    CodecRegWrite1(baseAddr, 0x01, 0x117);

    // ����DAC VOLUME
    CodecRegWrite1(baseAddr, 0xa, 0xFF | 0x100);
    CodecRegWrite1(baseAddr, 0xb, 0xFF | 0x100);
    CodecRegWrite1(baseAddr, 0x2c, 0X24);
    CodecRegWrite1(baseAddr, 0x2b, 0X24);




    return;

}
void AIC31Reset(unsigned int baseAddr)
{
    /* Select Page 0 */
    regval=5;

    wm8960_init(baseAddr);
    //CodecRegWrite(baseAddr, AIC31_P0_REG0, 0);

    /* Reset the codec */
   // CodecRegWrite(baseAddr, AIC31_P0_REG1, AIC31_RESET);*/
}

/**
 * \brief   Configures the data format and slot width
 *
 * \param   baseAddr     Base Address of the interface connected to AIC31
 * \param   dataType     Data type for the codec operation
 * \param   slotWidth    Slot width in bits
 * \param   dataOff      The number of clocks from the word clock rising edge
 *                       to capture the actual data
 *            dataType can take the values \n
 *               AIC31_DATATYPE_I2S - for I2S mode \n
 *               AIC31_DATATYPE_DSP - for DSP mode \n
 *               AIC31_DATATYPE_RIGHTJ - for right aligned data \n
 *               AIC31_DATATYPE_LEFTJ - for left aligned data \n
 *
 * \return  None.
 *
 **/
void AIC31DataConfig(unsigned int baseAddr, unsigned char dataType,
                     unsigned char slotWidth, unsigned char dataOff)
{
    unsigned char slot = 0, cDataType = 0;

    /* configure the slot width                                   */
    switch(slotWidth)
    {
        case ICodec_SlotWidth_16:   slot = AIC31_SLOT_WIDTH_16;        break;
        case ICodec_SlotWidth_20:   slot = AIC31_SLOT_WIDTH_20;        break;
        case ICodec_SlotWidth_24:   slot = AIC31_SLOT_WIDTH_24;        break;
        case ICodec_SlotWidth_32:   slot = AIC31_SLOT_WIDTH_32;        break;
        default:                    slot = AIC31_SLOT_WIDTH_16;        break;
    }

    /* Configure the audio serial data interface mode             */
    switch(dataType)
    {
        case ICodec_DataType_I2S    : cDataType = AIC31_DATATYPE_I2S;     break;
        case ICodec_DataType_DSP    : cDataType = AIC31_DATATYPE_DSP;     break;
        case ICodec_DataType_RIGHTJ : cDataType = AIC31_DATATYPE_RIGHTJ;  break;
        case ICodec_DataType_LEFTJ  : cDataType = AIC31_DATATYPE_LEFTJ;   break;
        default                     : cDataType = AIC31_DATATYPE_I2S;     break;
    }

    /* Write the data type and  slot width */
    CodecRegWrite(baseAddr, AIC31_P0_REG9, (cDataType | slot));

    /* valid data after dataOff number of clock cycles */
    CodecRegWrite(baseAddr, AIC31_P0_REG10, dataOff);

#if defined (MCASP_MASTER)
    /* use PLL_CLK_IN as BCLK */
    CodecRegWrite(baseAddr, AIC31_P0_REG102, 0xA2);
#endif

}

/**
 * \brief   Configures the data format and slot width
 *
 * \param   baseAddr     Base Address of the interface connected to AIC31
 * \param   mode         section of the codec (ADC/DAC) for which the sample
 *                       rate needs to be configured
 * \param   sampleRate   Sample rate in samples per second
 *              mode can take the values \n
 *                AIC31_MODE_ADC - for selecting ADC \n
 *                AIC31_MODE_DAC - for selecting DAC \n
 *                AIC31_MODE_BOTH - for both ADC and DAC \n
 *              sampleRate can be \n
 *                 8000, 11025, 16000, 22050, 24000, 32000, 44100,
 *                 48000 or  96000. \n
 *          The fs is derived from the equation
 *                fs = (PLL_IN * [pllJval.pllDval] * pllRval) /(2048 * pllPval).
 *          So the values are set for PLL_IN = 24576 kHz
 *
 * \return  None.
 *
 **/
void AIC31SampleRateConfig(unsigned int baseAddr, unsigned int mode,
                           unsigned int sampleRate)
{
    unsigned char fs;
    unsigned char ref = 0x0Au;
    unsigned char temp;
    unsigned char pllPval = 2u;
    //unsigned char pllRval = 1u;
    unsigned char pllJval = 8u;
    unsigned short pllDval = 0u;

    /* Select the configuration for the given sampling rate */
    switch(sampleRate)
    {
        case 8000:
            fs = 0xAAu;
        break;

        case 11025:
            fs = 0x66u;
            ref = 0x8Au;
            pllJval = 14u;
            pllDval = 7000u;
        break;

        case 16000:
            fs = 0x44u;
        break;

        case 22050:
            fs = 0x22u;
            ref = 0x8Au;
            pllJval = 14u;
            pllDval = 7000u;
        break;

        case 24000:
            fs = 0x22u;
        break;

        case 32000:
            fs = 0x11u;
        break;

        case 44100:
            ref = 0x8Au;
            fs = 0x00u;
            //pllJval = 14u;
            //pllDval = 7000u;
        break;

        case 48000:
            fs = 0x00u;
        break;

        case 96000:
            ref = 0x6Au;
            fs = 0x00u;
        break;

        default:
            fs = 0x00u;
        break;
    }

    temp = (mode & fs);

    /* Set the sample Rate */
    CodecRegWrite(baseAddr, AIC31_P0_REG2, temp);

    CodecRegWrite(baseAddr, AIC31_P0_REG3, 0xA0 | pllPval);

    /* use PLL_CLK_IN as MCLK */
    CodecRegWrite(baseAddr, AIC31_P0_REG102, 0x02);

    /* Use CLKDIV_OUT as codec CLK IN */
    CodecRegWrite(baseAddr, AIC31_P0_REG101, 0x01);

    /* Select GPIO to output the divided PLL IN */
    //CodecRegWrite(baseAddr, AIC31_P0_REG98, 0x20);
/*
    temp = (pllJval << 2);
    CodecRegWrite(baseAddr, AIC31_P0_REG4, temp); */

    /* Configure the PLL divide registers */
 /*   CodecRegWrite(baseAddr, AIC31_P0_REG5, (pllDval >> 6) & 0xFF);
    CodecRegWrite(baseAddr, AIC31_P0_REG6, (pllDval & 0x3F) << 2);

    temp = pllRval;
    CodecRegWrite(baseAddr, AIC31_P0_REG11, temp); */

    /* Enable the codec to be master for fs and bclk */
    CodecRegWrite(baseAddr, AIC31_P0_REG8, 0xD0);

    CodecRegWrite(baseAddr, AIC31_P0_REG7, ref);
}

/**
 * \brief   Initializes the ADC section of the AIC31 Codec
 *
 * \param   baseAddr     Base Address of the interface connected to AIC31
 *
 * \return  None.
 *
 **/
void AIC31ADCInit(unsigned int baseAddr)
{
    /* enable the programmable PGA for left and right ADC  */
    CodecRegWrite(baseAddr, AIC31_P0_REG15, 0x00);
    CodecRegWrite(baseAddr, AIC31_P0_REG16, 0x00);

    /* MIC1R is not connected to the left ADC PGA */
    CodecRegWrite(baseAddr, AIC31_P0_REG17, 0x0F);

    /* MIC1L is not connected to the right ADC PGA */
    CodecRegWrite(baseAddr, AIC31_P0_REG18, 0xF0);

    /* power on the Line L1R */
    CodecRegWrite(baseAddr, AIC31_P0_REG19, 0x7C);

    /* power on the Line L2R */
    CodecRegWrite(baseAddr, AIC31_P0_REG22, 0x7C);
}

/**
 * \brief   Initializes the DAC section of the AIC31 Codec
 *
 * \param   baseAddr     Base Address of the interface connected to AIC31
 *
 * \return  None.
 *
 **/
void AIC31DACInit(unsigned int baseAddr)
{

	/* Codec Datapath Setup */
	CodecRegWrite(baseAddr, AIC31_P0_REG7, 0x8A);

    /* select the DAC L1 R1 Paths */
    CodecRegWrite(baseAddr, AIC31_P0_REG41, 0x02);
    CodecRegWrite(baseAddr, AIC31_P0_REG42, 0x6C);


    /* DAC L to HPLOUT Is connected */
    CodecRegWrite(baseAddr, AIC31_P0_REG47, 0x80);
    CodecRegWrite(baseAddr, AIC31_P0_REG51, 0x09);

    /* DAC R to HPROUT is connected */
    CodecRegWrite(baseAddr, AIC31_P0_REG64, 0x80);
    CodecRegWrite(baseAddr, AIC31_P0_REG65, 0x09);

    /* DACL1 connected to LINE1 LOUT */
    CodecRegWrite(baseAddr, AIC31_P0_REG82, 0x80);
    CodecRegWrite(baseAddr, AIC31_P0_REG86, 0x09);

    /* DACR1 connected to LINE1 ROUT */
    CodecRegWrite(baseAddr, AIC31_P0_REG92, 0x80);
    CodecRegWrite(baseAddr, AIC31_P0_REG93, 0x09);

    /* unmute the DAC */
    CodecRegWrite(baseAddr, AIC31_P0_REG43, 0x00);
    CodecRegWrite(baseAddr, AIC31_P0_REG44, 0x00);

    /* DAC Quiescent Current Adjustment */
    //CodecRegWrite(baseAddr, AIC31_P0_REG109, 0xC0);

	/* power up the left and right DACs */
    CodecRegWrite(baseAddr, AIC31_P0_REG37, 0xE0);
}

void AIC31ADCDeInit (unsigned int baseAddr)
{
    /* Write the reset values to ADC registers                                */
    CodecRegWrite (baseAddr, AIC31_P0_REG15, (uint8_t)0x00);
    CodecRegWrite (baseAddr, AIC31_P0_REG16, (uint8_t)0x00);
    CodecRegWrite (baseAddr, AIC31_P0_REG17, (uint8_t)0xFF);
    CodecRegWrite (baseAddr, AIC31_P0_REG18, (uint8_t)0xFF);
    CodecRegWrite (baseAddr, AIC31_P0_REG19, (uint8_t)0x78);
    CodecRegWrite (baseAddr, AIC31_P0_REG22, (uint8_t)0x78);
    CodecRegWrite (baseAddr, AIC31_P0_REG26, (uint8_t)0x00);
    CodecRegWrite (baseAddr, AIC31_P0_REG27, (uint8_t)0xFE);
    CodecRegWrite (baseAddr, AIC31_P0_REG28, (uint8_t)0x00);
    CodecRegWrite (baseAddr, AIC31_P0_REG29, (uint8_t)0x00);
    CodecRegWrite (baseAddr, AIC31_P0_REG30, (uint8_t)0xFE);
    CodecRegWrite (baseAddr, AIC31_P0_REG31, (uint8_t)0x00);
}

void AIC31DACDeInit (unsigned int baseAddr)
{
    /* Write the reset values to DAC registers                                */

    CodecRegBitClr (baseAddr, AIC31_P0_REG101, (uint8_t)0x1E);
    CodecRegWrite  (baseAddr, AIC31_P0_REG37,  (uint8_t)0x00);
    CodecRegWrite  (baseAddr, AIC31_P0_REG38,  (uint8_t)0x00);
    CodecRegWrite  (baseAddr, AIC31_P0_REG41,  (uint8_t)0x00);
    CodecRegWrite  (baseAddr, AIC31_P0_REG42,  (uint8_t)0x00);
    CodecRegWrite  (baseAddr, AIC31_P0_REG43,  (uint8_t)0x80);
    CodecRegWrite  (baseAddr, AIC31_P0_REG44,  (uint8_t)0x80);
    CodecRegWrite  (baseAddr, AIC31_P0_REG51,  (uint8_t)0x04);
    CodecRegWrite  (baseAddr, AIC31_P0_REG64,  (uint8_t)0x00);
    CodecRegWrite  (baseAddr, AIC31_P0_REG65,  (uint8_t)0x04);
    CodecRegWrite  (baseAddr, AIC31_P0_REG82,  (uint8_t)0x00);
    CodecRegWrite  (baseAddr, AIC31_P0_REG86,  (uint8_t)0x00);
    CodecRegWrite  (baseAddr, AIC31_P0_REG92,  (uint8_t)0x00);
    CodecRegWrite  (baseAddr, AIC31_P0_REG93,  (uint8_t)0x00);
}

/***************************** End Of File ***********************************/