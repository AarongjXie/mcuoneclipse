/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : LCD1.h
**     Project     : tinyK22_SGP30
**     Processor   : MK22FN512VLH12
**     Component   : SSD1351
**     Version     : Component 01.043, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-10-06, 08:17, # CodeGen: 61
**     Abstract    :
**
Display driver for the SSD1351 (e.g. found on Hexiwear).
**     Settings    :
**          Component name                                 : LCD1
**          Type                                           : 128x128
**          Orientation                                    : landscape
**          Width                                          : 128
**          Height                                         : 128
**          Bytes in rows                                  : yes
**          Bytes in x direction                           : yes
**          MSB first                                      : no
**          Bits per pixel                                 : 16
**          Window capability                              : no
**          Display Memory Write                           : no
**          Display Memory Read                            : no
**          Use RAM Buffer                                 : yes
**          Clear display in init                          : no
**          Initialize on Init                             : no
**          HW                                             : 
**            HW SPI Delay (us)                            : 0
**            SW SPI                                       : Disabled
**            LDD HW SPI                                   : Enabled
**              HW SPI                                     : SM1
**            HW SPI                                       : Disabled
**            Slave Select                                 : Enabled
**              SCE                                        : SCE
**            Reset                                        : Enabled
**              Reset                                      : RES
**              D_C                                        : D_C
**            Power                                        : Disabled
**          System                                         : 
**            Wait                                         : WAIT1
**            SDK                                          : MCUC1
**     Contents    :
**         GetWidth              - LCD1_PixelDim LCD1_GetWidth(void);
**         GetHeight             - LCD1_PixelDim LCD1_GetHeight(void);
**         GetLongerSide         - LCD1_PixelDim LCD1_GetLongerSide(void);
**         GetShorterSide        - LCD1_PixelDim LCD1_GetShorterSide(void);
**         GetDisplayOrientation - LCD1_DisplayOrientation LCD1_GetDisplayOrientation(void);
**         WriteData             - void LCD1_WriteData(uint8_t data);
**         WriteDataWord         - void LCD1_WriteDataWord(uint16_t data);
**         WriteDataWordRepeated - void LCD1_WriteDataWordRepeated(uint16_t data, size_t nof);
**         WriteDataBlock        - void LCD1_WriteDataBlock(uint8_t *data, size_t dataSize);
**         WriteCommand          - void LCD1_WriteCommand(uint8_t cmd);
**         OpenWindow            - void LCD1_OpenWindow(LCD1_PixelDim x0, LCD1_PixelDim y0, LCD1_PixelDim x1,...
**         CloseWindow           - void LCD1_CloseWindow(void);
**         Clear                 - void LCD1_Clear(void);
**         UpdateFull            - void LCD1_UpdateFull(void);
**         UpdateRegion          - void LCD1_UpdateRegion(LCD1_PixelDim x, LCD1_PixelDim y, LCD1_PixelDim w,...
**         InitCommChannel       - void LCD1_InitCommChannel(void);
**         GetLCD                - void LCD1_GetLCD(void);
**         GiveLCD               - void LCD1_GiveLCD(void);
**         OnDataReceived        - void LCD1_OnDataReceived(void);
**         PutPixel              - void LCD1_PutPixel(LCD1_PixelDim x, LCD1_PixelDim y, LCD1_PixelColor color);
**         GetPixel              - LCD1_PixelColor LCD1_GetPixel(LCD1_PixelDim x, LCD1_PixelDim y);
**         Init                  - void LCD1_Init(void);
**
** * Copyright (c) 2014-2018, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file LCD1.h
** @version 01.00
** @brief
**
Display driver for the SSD1351 (e.g. found on Hexiwear).
*/         
/*!
**  @addtogroup LCD1_module LCD1 module documentation
**  @{
*/         

/* MODULE LCD1. */

#include "LCD1.h"

#if LCD1_CONFIG_USE_RAM_BUFFER
  LCD1_PixelColor LCD1_DisplayBuf[LCD1_DISPLAY_HW_NOF_ROWS][LCD1_DISPLAY_HW_NOF_COLUMNS]; /* buffer for the display */
#endif
/*
- RESET is low active
- D_C high is data, low is command
*/
#define RESET_INIT()  /* no special init needed, is done during component init */
#define RESET_LOW()   RESpin1_ClrVal()  /* RESET signal low (reset is low active) */
#define RESET_HIGH()  RESpin1_SetVal()  /* RESET signal high */

#define CMD_MODE()   D_Cpin1_ClrVal()   /* switch to command mode, D/C low */
#define DATA_MODE()  D_Cpin1_SetVal()   /* switch to data mode, D/C high */
#define CS_HIGH()    SCEpin1_SetVal()   /* CE signal high */
#define CS_LOW()     SCEpin1_ClrVal()   /* CE signal low */

#define POWER_OFF()  /* no pin defined for OLED power off */
#define POWER_ON()   /* no pin defined for OLED power on */

#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  static LCD1_DisplayOrientation currentOrientation;
#endif

/* OLED specific defines and information */
#if LCD1_HW_HEIGHT==96
  #define OLED_COLUMN_OFFSET (16)
  #define OLED_ROW_OFFSET    (0)
#else /* 128x128 */
  #define OLED_COLUMN_OFFSET (0)
  #define OLED_ROW_OFFSET    (0)
#endif

#define OLED_CMD_SET_COLUMN     (0x15)
#define OLED_CMD_SET_ROW        (0x75)

#define OLED_CMD_STARTLINE      (0xA1)

#define OLED_CMD_WRITERAM       (0x5C)
#define OLED_CMD_READRAM        (0x5D)
#define OLED_CMD_DISPLAYOFFSET  (0xA2)
#define OLED_CMD_DISPLAYALLOFF  (0xA4)
#define OLED_CMD_DISPLAYALLON   (0xA5)
#define OLED_CMD_NORMALDISPLAY  (0xA6)
#define OLED_CMD_INVERTDISPLAY  (0xA7)
#define OLED_CMD_FUNCTIONSELECT (0xAB)
#define OLED_CMD_DISPLAYOFF     (0xAE)
#define OLED_CMD_DISPLAYON      (0xAF)
#define OLED_CMD_PRECHARGE      (0xB1)
#define OLED_CMD_DISPLAYENHANCE (0xB2)
#define OLED_CMD_SETVSL         (0xB4)
#define OLED_CMD_SETGPIO        (0xB5)
#define OLED_CMD_PRECHARGE2     (0xB6)
#define OLED_CMD_SETGRAY        (0xB8)
#define OLED_CMD_USELUT         (0xB9)
#define OLED_CMD_PRECHARGELEVEL (0xBB)
#define OLED_CMD_VCOMH          (0xBE)
#define OLED_CMD_CONTRASTABC    (0xC1)
#define OLED_CMD_CONTRASTMASTER (0xC7)
#define OLED_CMD_MUXRATIO       (0xCA)
#define OLED_CMD_COMMANDLOCK    (0xFD)
#define OLED_CMD_HORIZSCROLL    (0x96)
#define OLED_CMD_STOPSCROLL     (0x9E)
#define OLED_CMD_STARTSCROLL    (0x9F)

/**
 * set lock command
 * the locked OLED driver MCU interface prohibits all commands
 * and memory access, except the 0xFD command
 */
#define OLED_CMD_SET_CMD_LOCK (0xFD)
// unlock OLED driver MCU interface for entering command (default upon reset)
#define OLED_UNLOCK           (0x12)
// lock OLED driver MCU interface for entering command
#define OLED_LOCK             (0x16)
// commands 0xA2, 0xB1, 0xB3, 0xBB, 0xBE, 0xC1 are inaccessible in both lock and unlock state (default upon reset)
#define OLED_ACC_TO_CMD_NO    (0xB0)
// commands 0xA2, 0xB1, 0xB3, 0xBB, 0xBE, 0xC1 are accessible in unlock state
#define OLED_ACC_TO_CMD_YES   (0xB1)

#define OLED_CMD_SET_OSC_FREQ_AND_CLOCKDIV (0xB3)

/* clock divider */
#define OLED_CLOCKDIV_1    (0x00)
#define OLED_CLOCKDIV_2    (0x01)
#define OLED_CLOCKDIV_4    (0x02)
#define OLED_CLOCKDIV_8    (0x03)
#define OLED_CLOCKDIV_16   (0x04)
#define OLED_CLOCKDIV_32   (0x05)
#define OLED_CLOCKDIV_64   (0x06)
#define OLED_CLOCKDIV_128  (0x07)
#define OLED_CLOCKDIV_256  (0x08)
#define OLED_CLOCKDIV_512  (0x09)
#define OLED_CLOCKDIV_1024 (0x0A)

/* set MUX ratio */
#define OLED_CMD_SET_MUX_RATIO (0xCA)

/* set re-map / color depth */
#define OLED_CMD_SET_REMAP     (0xA0)

/* set horizontal or vertical increment */
#define OLED_ADDR_INC_HOR      (0x00)
#define OLED_ADDR_INC_VER      (0x01)

/* remap settings */
#define REMAP_HORIZONTAL_INCREMENT      (0)     /* horizontal address incremented */
#define REMAP_VERTICAL_INCREMENT        (1<<0)  /* vertical address increment */

#define REMAP_COLUMNS_LEFT_TO_RIGHT     (0)     /* column numbering from left to right */
#define REMAP_COLUMNS_RIGHT_TO_LEFT     (1<<1)  /* column numbering from right to left */

#define REMAP_ORDER_ABC                 (0)     /* color oreder is red-green-blue */
#define REMAP_ORDER_CBA                 (1<<2)  /* color order is blue-green-red */

#define REMAP_SCAN_UP_TO_DOWN           (0)
#define REMAP_SCAN_DOWN_TO_UP           (1<<4)

#define REMAP_COM_SPLIT_ODD_EVEN_DIS    (0)
#define REMAP_COM_SPLIT_ODD_EVEN_EN     (1<<5)

#define REMAP_COLOR_RGB565              (1<<6) /* 65k colors, 5 bits for red, 6 for green and 5 for blue */
#define LCD1_SPI_Enable()                   (void)SM1_Enable(SM1_DeviceData)
#define LCD1_SPI_Disable()                  (void)SM1_Disable(SM1_DeviceData)
#define LCD1_SPI_SetShiftClockPolarity(val) /* not needed for LDD */
#define LCD1_SPI_SetIdleClockPolarity(val)  /* not needed for LDD */

static volatile bool LCD1_DataReceivedFlag = FALSE;

void LCD1_SPI_WRITE(unsigned char data) {
#if LCD1_CONFIG_USE_SPI_API==LCD1_CONFIG_SPI_API_SW
  (void)LCD1_CONFIG_SPI_API_FCT_NAME_SEND(data); /* send MSB data byte */
  while(LCD1_CONFIG_SPI_API_FCT_NAME_CHECK_TX()) {}; /* wait until everything is sent */
#elif LCD1_CONFIG_USE_SPI_API==LCD1_CONFIG_SPI_API_HW
  while(LCD1_CONFIG_SPI_API_FCT_NAME_SEND(data)!=ERR_OK) {} /* send MSB data byte */
  while(LCD1_CONFIG_SPI_API_FCT_NAME_CHECK_TX()!=0) {} /* wait until everything is sent */
  WAIT1_Waitus(LCD1_CONFIG_HWSPI_DELAY_US);
#elif LCD1_CONFIG_USE_SPI_API==LCD1_CONFIG_SPI_API_HW_LDD
  LCD1_DataReceivedFlag = FALSE;
  (void)LCD1_CONFIG_SPI_API_FCT_NAME_SEND_BLOCK(LCD1_CONFIG_SPI_API_DEVICE_HANDLE, &data, sizeof(data));
  while(!LCD1_DataReceivedFlag){}
#else
  #error "not supported"
#endif
}

static void LCD1_SPI_WRITE_BLOCK(unsigned char *data, size_t dataSize) {
#if LCD1_CONFIG_USE_SPI_API==LCD1_CONFIG_SPI_API_SW || LCD1_CONFIG_USE_SPI_API==LCD1_CONFIG_SPI_API_HW
  while(dataSize>0) {
    LCD1_SPI_WRITE(*data);
    data++;
    dataSize--;
  }
#elif LCD1_CONFIG_USE_SPI_API==LCD1_CONFIG_SPI_API_HW_LDD
  LCD1_DataReceivedFlag = FALSE;
  (void)LCD1_CONFIG_SPI_API_FCT_NAME_SEND_BLOCK(LCD1_CONFIG_SPI_API_DEVICE_HANDLE, data, dataSize);
  while(!LCD1_DataReceivedFlag){}
#endif
}

static void SetDisplayOrientation(LCD1_DisplayOrientation orientation) {
  uint8_t remap;

  #if MCUC1_CONFIG_CPU_IS_LITTLE_ENDIAN
    #define REMAP_BASE_VALUES           (REMAP_COLOR_RGB565 | REMAP_COM_SPLIT_ODD_EVEN_EN | REMAP_SCAN_UP_TO_DOWN | REMAP_ORDER_CBA)
  #else
    #define REMAP_BASE_VALUES           (REMAP_COLOR_RGB565 | REMAP_COM_SPLIT_ODD_EVEN_EN | REMAP_SCAN_UP_TO_DOWN | REMAP_ORDER_ABC)
  #endif

  switch(orientation) {
    default:
    case LCD1_ORIENTATION_LANDSCAPE:
      remap =  REMAP_BASE_VALUES | REMAP_COLUMNS_RIGHT_TO_LEFT  | REMAP_HORIZONTAL_INCREMENT;
      break;
    case LCD1_ORIENTATION_LANDSCAPE180: /* ??? right lower corner, reverted? */
      remap = REMAP_BASE_VALUES | REMAP_COLUMNS_LEFT_TO_RIGHT  | REMAP_VERTICAL_INCREMENT;
      break;
    case LCD1_ORIENTATION_PORTRAIT180: /* lower left corner, reverted */
      remap = REMAP_BASE_VALUES | REMAP_COLUMNS_RIGHT_TO_LEFT  | REMAP_HORIZONTAL_INCREMENT;
      break;
    case LCD1_ORIENTATION_PORTRAIT:
      remap = REMAP_BASE_VALUES | REMAP_COLUMNS_RIGHT_TO_LEFT  | REMAP_VERTICAL_INCREMENT;
      break;
  } /* switch */
  LCD1_WriteCommand(OLED_CMD_SET_REMAP); /* Remap command */
  LCD1_WriteData(remap);                 /* remap data */
#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  currentOrientation = orientation;
#endif
}
/*
** ===================================================================
**     Method      :  WriteData (component SSD1351)
**
**     Description :
**         Writes a data byte to the bus
**     Parameters  :
**         NAME            - DESCRIPTION
**         data            - data byte to send
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_WriteData(uint8_t data)
{
  DATA_MODE();
  CS_LOW();
  LCD1_SPI_WRITE(data);
#if LCD1_CONFIG_USE_SPI_API!=LCD1_CONFIG_SPI_API_SW
  /* for HW SPI, have to delay as transaction still might be going on! */
  WAIT1_Waitus(LCD1_CONFIG_HWSPI_DELAY_US);
#endif
  CS_HIGH();
}

/*
** ===================================================================
**     Method      :  WriteDataWordRepeated (component SSD1351)
**
**     Description :
**         Sends a data word to the display a number of times
**     Parameters  :
**         NAME            - DESCRIPTION
**         data            - data to write
**         nof             - How many times the data word shall be sent
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_WriteDataWordRepeated(uint16_t data, size_t nof)
{
  DATA_MODE();
  CS_LOW();
#if MCUC1_CONFIG_CPU_IS_LITTLE_ENDIAN
 /* swap bytes */
  data = (data<<8)|(data>>8);
#endif
  while(nof>0) {
    LCD1_SPI_WRITE_BLOCK((uint8_t*)&data, sizeof(data));
    nof--;
  }
#if LCD1_CONFIG_USE_SPI_API!=LCD1_CONFIG_SPI_API_SW
  /* for HW SPI, have to delay as transaction still might be going on! */
  WAIT1_Waitus(LCD1_CONFIG_HWSPI_DELAY_US);
#endif
  CS_HIGH();
}

/*
** ===================================================================
**     Method      :  WriteDataBlock (component SSD1351)
**
**     Description :
**         Sends a data buffer to the display
**     Parameters  :
**         NAME            - DESCRIPTION
**       * data            - Pointer to data to write
**         dataSize        - 
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_WriteDataBlock(uint8_t *data, size_t dataSize)
{
  DATA_MODE();
  CS_LOW();
  LCD1_SPI_WRITE_BLOCK(data, dataSize);
#if LCD1_CONFIG_USE_SPI_API!=LCD1_CONFIG_SPI_API_SW
  /* for HW SPI, have to delay as transaction still might be going on! */
  WAIT1_Waitus(LCD1_CONFIG_HWSPI_DELAY_US);
#endif
  CS_HIGH();
}

/*
** ===================================================================
**     Method      :  WriteCommand (component SSD1351)
**
**     Description :
**         Sends a command byte to the bus
**     Parameters  :
**         NAME            - DESCRIPTION
**         cmd             - the command to be sent
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_WriteCommand(uint8_t cmd)
{
  CMD_MODE();
  CS_LOW();
  LCD1_SPI_WRITE(cmd);
#if LCD1_CONFIG_USE_SPI_API!=LCD1_CONFIG_SPI_API_SW
  /* for HW SPI, have to delay as transaction still might be going on! */
  WAIT1_Waitus(LCD1_CONFIG_HWSPI_DELAY_US);
#endif
  CS_HIGH();
}

/*
** ===================================================================
**     Method      :  WriteDataWord (component SSD1351)
**
**     Description :
**         Sends a data word to the display
**     Parameters  :
**         NAME            - DESCRIPTION
**         data            - data to write
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_WriteDataWord(uint16_t data)
{
  /* writes the data to the bus, most significant byte first */
  DATA_MODE();                         /* DC high */
  CS_LOW();                            /* CS low */
  LCD1_SPI_WRITE(data>>8);             /* high byte */
  LCD1_SPI_WRITE(data);                /* low byte */
#if LCD1_CONFIG_USE_SPI_API!=LCD1_CONFIG_SPI_API_SW
  /* for HW SPI, have to delay as transaction still might be going on! */
  WAIT1_Waitus(LCD1_CONFIG_HWSPI_DELAY_US);
#endif
  CS_HIGH();                           /* CS high */
}

/*
** ===================================================================
**     Method      :  OpenWindow (component SSD1351)
**
**     Description :
**         Opens a window inside the display we want to write to.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x0              - 
**         y0              - 
**         x1              - 
**         y1              - 
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_OpenWindow(LCD1_PixelDim x0, LCD1_PixelDim y0, LCD1_PixelDim x1, LCD1_PixelDim y1)
{
  uint8_t c0,c1; /* column start and end */
  uint8_t r0,r1; /* row start and end */

  if ((x0 >= LCD1_GetWidth()) || (x1 >= LCD1_GetWidth())) {
    return;
  }
  if ((y0 >= LCD1_GetHeight()) || (y1 >= LCD1_GetHeight())) {
    return;
  }
#if LCD1_CONFIG_USE_RAM_BUFFER
  /* orientation is handled by the writes to the RAM buffer, use default landscape setting */
  c0 = x0+OLED_COLUMN_OFFSET;
  c1 = x1+OLED_COLUMN_OFFSET;
  r0 = y0+OLED_ROW_OFFSET;
  r1 = y1+OLED_ROW_OFFSET;
#elif LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  switch(currentOrientation) {
    default:
    case LCD1_ORIENTATION_LANDSCAPE:
      c0 = x0+OLED_COLUMN_OFFSET; c1 = x1+OLED_COLUMN_OFFSET;
      r0 = y0+OLED_ROW_OFFSET; r1 = y1+OLED_ROW_OFFSET;
      break;
    case LCD1_ORIENTATION_LANDSCAPE180:
      c0 = x0+OLED_COLUMN_OFFSET; c1 = x1+OLED_COLUMN_OFFSET;
      r0 = LCD1_HW_HEIGHT-1-y1+OLED_ROW_OFFSET; r1 = LCD1_HW_HEIGHT-1-y0+OLED_ROW_OFFSET;
      break;
    case LCD1_ORIENTATION_PORTRAIT:
      c0 = LCD1_HW_WIDTH-1-y1+OLED_COLUMN_OFFSET; c1 = LCD1_HW_WIDTH-1-y0+OLED_COLUMN_OFFSET;
      r0 = x0+OLED_ROW_OFFSET; r1 = x1+OLED_ROW_OFFSET;
      break;
    case LCD1_ORIENTATION_PORTRAIT180:
      c0 = y0+OLED_COLUMN_OFFSET; c1 = y1+OLED_COLUMN_OFFSET;
      r0 = LCD1_HW_HEIGHT-1-x1+OLED_ROW_OFFSET; r1 = LCD1_HW_HEIGHT-1-x0+OLED_ROW_OFFSET;
      break;
  } /* switch */
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT
  c0 = LCD1_HW_WIDTH-1-y1+OLED_COLUMN_OFFSET; c1 = LCD1_HW_WIDTH-1-y0+OLED_COLUMN_OFFSET;
  r0 = x0+OLED_ROW_OFFSET; r1 = x1+OLED_ROW_OFFSET;
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT180
  c0 = y0+OLED_COLUMN_OFFSET; c1 = y1+OLED_COLUMN_OFFSET;
  r0 = LCD1_HW_HEIGHT-1-x1+OLED_ROW_OFFSET; r1 = LCD1_HW_HEIGHT-1-x0+OLED_ROW_OFFSET;
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE
  c0 = x0+OLED_COLUMN_OFFSET; c1 = x1+OLED_COLUMN_OFFSET;
  r0 = y0+OLED_ROW_OFFSET; r1 = y1+OLED_ROW_OFFSET;
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  c0 = x0+OLED_COLUMN_OFFSET; c1 = x1+OLED_COLUMN_OFFSET;
  r0 = LCD1_HW_HEIGHT-1-y1+OLED_ROW_OFFSET; r1 = LCD1_HW_HEIGHT-1-y0+OLED_ROW_OFFSET;
#endif
  /* Set Window */
  LCD1_WriteCommand(OLED_CMD_SET_COLUMN); /* set column command */
  LCD1_WriteDataWord(c0<<8|c1);        /* start and end column */

  LCD1_WriteCommand(OLED_CMD_SET_ROW); /* set row start address command */
  LCD1_WriteDataWord(r0<<8|r1);        /* start and end row */

  LCD1_WriteCommand(OLED_CMD_WRITERAM); /* now activate writing to RAM */
}

/*
** ===================================================================
**     Method      :  Clear (component SSD1351)
**
**     Description :
**         Clears the whole display memory.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_Clear(void)
{
  LCD1_OpenWindow(0, 0, (LCD1_PixelDim)(LCD1_GetWidth()-1), (LCD1_PixelDim)(LCD1_GetHeight()-1)); /* window for whole display */
  LCD1_WriteDataWordRepeated(LCD1_PIXEL_OFF, LCD1_WIDTH*LCD1_HEIGHT);
  LCD1_CloseWindow();
}

/*
** ===================================================================
**     Method      :  UpdateFull (component SSD1351)
**
**     Description :
**         Updates the whole display. This is only a stub for this
**         display as we are using windowing.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_UpdateFull(void)
{
#if LCD1_CONFIG_USE_RAM_BUFFER
  LCD1_UpdateRegion(0, 0, LCD1_GetWidth(), LCD1_GetHeight()); /* update whole display */
#else
  /* nothing needed in direct display mode (not using RAM buffer) */
#endif
}

/*
** ===================================================================
**     Method      :  UpdateRegion (component SSD1351)
**
**     Description :
**         Updates a region of the display. This is only a stub for
**         this display as we are using windowing.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x coordinate
**         y               - y coordinate
**         w               - width of the region
**         h               - Height of the region
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_UpdateRegion(LCD1_PixelDim x, LCD1_PixelDim y, LCD1_PixelDim w, LCD1_PixelDim h)
{
#if LCD1_CONFIG_USE_RAM_BUFFER
  LCD1_PixelDim xb, yb, wb, hb; /* coordinates in buffer for write operation */

  #if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  /* rotate area to the physical display memory mapping which is using a landscape format */
  switch(currentOrientation) {
    default:
    case LCD1_ORIENTATION_PORTRAIT:
      xb = LCD1_HW_WIDTH-y-h; yb = x;
      wb = h; hb = w;
      break;
    case LCD1_ORIENTATION_PORTRAIT180:
      xb = y; yb = LCD1_HW_HEIGHT-x-w;
      wb = h; hb = w;
      break;
    case LCD1_ORIENTATION_LANDSCAPE:
      xb = x; yb = y;
      wb = w; hb = h;
      break;
    case LCD1_ORIENTATION_LANDSCAPE180:
      xb = LCD1_HW_WIDTH-x-w; yb = LCD1_HW_HEIGHT-y-h;
      wb = w; hb = h;
      break;
  } /* switch */
  #elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT
  xb = LCD1_HW_WIDTH-y-h; yb = x;
  wb = h; hb = w;
  #elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT180
  xb = y; yb = LCD1_HW_HEIGHT-x-w;
  wb = h; hb = w;
  #elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE
  xb = x; yb = y;
  wb = w; hb = h;
  #elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  xb = LCD1_HW_WIDTH-x-w; yb = LCD1_HW_HEIGHT-y-h;
  wb = w; hb = h;
  #endif

  LCD1_OpenWindow(xb, yb, xb+wb-1, yb+hb-1);  /* window for region */
  if (xb==0 && w==LCD1_HW_WIDTH) { /* can write full block */
    LCD1_WriteDataBlock((uint8_t*)(&LCD1_DisplayBuf[yb][xb]), wb*hb*sizeof(LCD1_DisplayBuf[0][0]));
  } else {
    /* need to write memory line by line */
    LCD1_PixelDim i;

    for(i=yb;i<yb+hb-1;i++) {
      LCD1_WriteDataBlock((uint8_t*)(&LCD1_DisplayBuf[i][xb]), wb*sizeof(LCD1_DisplayBuf[0][0]));
    }
  }
  LCD1_CloseWindow();
#else
  /* nothing needed in direct display mode (not using RAM buffer) */
#endif
}

/*
** ===================================================================
**     Method      :  CloseWindow (component SSD1351)
**
**     Description :
**         Closes a window previously opened with OpenWindow()
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void LCD1_CloseWindow(void)
{
  implemented as macro in LCD1.h
}
*/

/*
** ===================================================================
**     Method      :  GetDisplayOrientation (component SSD1351)
**
**     Description :
**         Returns the current display orientation
**     Parameters  : None
**     Returns     :
**         ---             - current display orientation
** ===================================================================
*/
LCD1_DisplayOrientation LCD1_GetDisplayOrientation(void)
{
#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  return currentOrientation;
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT
  return LCD1_ORIENTATION_PORTRAIT;    /* Portrait mode */
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT180
  return LCD1_ORIENTATION_PORTRAIT180; /* Portrait mode, rotated 180� */
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE
  return LCD1_ORIENTATION_LANDSCAPE;   /* Landscape mode, rotated right 90� */
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  return LCD1_ORIENTATION_LANDSCAPE180; /* Landscape mode, rotated left 90� */
#endif
}

/*
** ===================================================================
**     Method      :  GetWidth (component SSD1351)
**
**     Description :
**         Returns the width of the display in pixels (in x direction)
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
LCD1_PixelDim LCD1_GetWidth(void)
{
  if (currentOrientation==LCD1_ORIENTATION_PORTRAIT || currentOrientation==LCD1_ORIENTATION_PORTRAIT180) {
    return LCD1_HW_SHORTER_SIDE;
  } else { /* LCD1_ORIENTATION_LANDSCAPE or LCD1_ORIENTATION_LANDSCAPE180 */
    return LCD1_HW_LONGER_SIDE;
  }
}
#else
/*
LCD1_PixelDim LCD1_GetWidth(void)
{
  implemented as macro in LCD1.h
}
*/
#endif

/*
** ===================================================================
**     Method      :  GetHeight (component SSD1351)
**
**     Description :
**         Returns the height of the display in pixels (in y direction)
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
LCD1_PixelDim LCD1_GetHeight(void)
{
  if (currentOrientation==LCD1_ORIENTATION_PORTRAIT || currentOrientation==LCD1_ORIENTATION_PORTRAIT180) {
    return LCD1_HW_LONGER_SIDE;
  } else { /* LCD1_ORIENTATION_LANDSCAPE or LCD1_ORIENTATION_LANDSCAPE180 */
    return LCD1_HW_SHORTER_SIDE;
  }
}
#else
/*
LCD1_PixelDim LCD1_GetHeight(void)
{
  implemented as macro in LCD1.h
}
*/
#endif

/*
** ===================================================================
**     Method      :  GetLongerSide (component SSD1351)
**
**     Description :
**         Returns the size of the longer side of the display
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
/*
LCD1_PixelDim LCD1_GetLongerSide(void)
{
  implemented as macro in LCD1.h
}
*/

/*
** ===================================================================
**     Method      :  GetShorterSide (component SSD1351)
**
**     Description :
**         Returns the size of the shorter side of the display
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
/*
LCD1_PixelDim LCD1_GetShorterSide(void)
{
  implemented as macro in LCD1.h
}
*/

/*
** ===================================================================
**     Method      :  GetLCD (component SSD1351)
**
**     Description :
**         Method to be called for mutual exclusive access to the LCD
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_GetLCD(void)
{
  LCD1_InitCommChannel();
}

/*
** ===================================================================
**     Method      :  GiveLCD (component SSD1351)
**
**     Description :
**         Method to be called for mutual exclusive access to the LCD
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_GiveLCD(void)
{
}

/*
** ===================================================================
**     Method      :  InitCommChannel (component SSD1351)
**
**     Description :
**         Method to initialize communication to the LCD. Needed if the
**         bus to the LCD is shared with other components and settings
**         are different.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_InitCommChannel(void)
{
  /* settings:
    - Max 16 MHz
    - Send MSB first
    - Shift clock idle polarity: low
    - Clock edge: falling edge (CPOL=0,CPHA=0)
  */
}

/*
** ===================================================================
**     Method      :  Init (component SSD1351)
**
**     Description :
**         Display driver initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_Init(void)
{
  /* 3-Wire SPI:
     CLK: Data needs to be valid at rising clock edge.
     MOSI: shift MSB first
  */
  typedef struct {
    uint8_t cmd, type;
  } init_cmd_t;
  int i;

  #define CMD_BYTE   (1)
  #define DATA_BYTE  (0)

  /* Not all displays are the same. They differ in brightness, speed, capacitance
     Things to consider or tune:
     OLED_CMD_PRECHARGE
     SSD1351_CMD_VCOMH
     SSD1351_CMD_CONTRASTABC
     SSD1351_CMD_CONTRASTMASTER
     SSD1351_CMD_SETVSL
     SSD1351_CMD_PRECHARGE2
     Additionally, powering the Adafruit from 5V or 3.3V makes a difference!
  */
  static const init_cmd_t seq[] = {
    /* 0xFD */ {OLED_CMD_SET_CMD_LOCK,   CMD_BYTE},
               {OLED_UNLOCK,             DATA_BYTE}, /* 0x12 */
    /* 0xFD */ {OLED_CMD_SET_CMD_LOCK,   CMD_BYTE},
               {OLED_ACC_TO_CMD_YES,     DATA_BYTE}, /* 0xB1 */
    /* 0xAE */ {OLED_CMD_DISPLAYOFF,     CMD_BYTE},
    /* 0xB3 */ {OLED_CMD_SET_OSC_FREQ_AND_CLOCKDIV, CMD_BYTE},
               {0xF1,                    DATA_BYTE}, /* 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16) */
               /* reset:
                 [7:4] 1101 (oszillator frequency, frequency increases as level increases
                 [3:0] 0001 (divide by DIVSET, 0001 means divide by 2
                 */
    /* 0xCA */ {OLED_CMD_SET_MUX_RATIO,  CMD_BYTE},
               {(LCD1_HW_WIDTH-1), DATA_BYTE},
    /* 0x15 */ {OLED_CMD_SET_COLUMN,     CMD_BYTE},
               {0x00,                    DATA_BYTE},
               {(LCD1_HW_WIDTH-1), DATA_BYTE},
    /* 0x75 */ {OLED_CMD_SET_ROW,        CMD_BYTE},
               {0x00,                    DATA_BYTE},
               {(LCD1_HW_HEIGHT-1),DATA_BYTE},
    /* 0xA1 */ {OLED_CMD_STARTLINE,      CMD_BYTE},
         #if LCD1_HW_HEIGHT==96
               {0x80, DATA_BYTE},
         #else
               {0x00,                    DATA_BYTE},
         #endif
    /* 0xA2 */ {OLED_CMD_DISPLAYOFFSET,  CMD_BYTE},
         #if LCD1_HW_HEIGHT==96
               {LCD1_HW_HEIGHT, DATA_BYTE},
         #else
               {0x00,                    DATA_BYTE},
         #endif
    /* 0xB5 */ {OLED_CMD_SETGPIO,        CMD_BYTE},
               {0x00,                    DATA_BYTE}, /* disable GPIO pins */
    /* 0xAB */ {OLED_CMD_FUNCTIONSELECT, CMD_BYTE},
               {0x01,                    DATA_BYTE}, /* enable internal Vdd regulator (diode drop) */
    /* 0xB1 */ {OLED_CMD_PRECHARGE,      CMD_BYTE},
               {0x32,                    CMD_BYTE},
    /* 0xBE */ {OLED_CMD_VCOMH,          CMD_BYTE},
               {0x05,                    CMD_BYTE},
    /* 0xA6 */ {OLED_CMD_NORMALDISPLAY,  CMD_BYTE},
    /* 0xC1 */ {OLED_CMD_CONTRASTABC,    CMD_BYTE},
    #if 0
               {0x8A,                    DATA_BYTE},
               {0x51,                    DATA_BYTE},
               {0x8A,                    DATA_BYTE},
    #else /* Adafruit contrast settings: https://github.com/adafruit/Adafruit-SSD1351-library/blob/master/Adafruit_SSD1351.cpp */
               {0xC8,                    DATA_BYTE},
               {0x80,                    DATA_BYTE},
               {0xC8,                    DATA_BYTE},
    #endif
    /* 0xC7 */ {OLED_CMD_CONTRASTMASTER, CMD_BYTE},
               {0xCF,                    DATA_BYTE}, /* 0x0F */
    /* 0xB4 */ {OLED_CMD_SETVSL,         CMD_BYTE},
               {0xA0,                    DATA_BYTE},
               {0xB5,                    DATA_BYTE},
               {0x55,                    DATA_BYTE},
    /* 0xB6 */ {OLED_CMD_PRECHARGE2,     CMD_BYTE},
               {0x01,                    DATA_BYTE},
    /* 0xAF */ {OLED_CMD_DISPLAYON,      CMD_BYTE}
    };

  POWER_OFF();
  WAIT1_Waitms(1);
  RESET_LOW();
  WAIT1_Waitms(1);
  RESET_HIGH();
  WAIT1_Waitms(1);
  POWER_ON();

  for (i=0;i<sizeof(seq)/sizeof(init_cmd_t);i++) {
    if (seq[i].type==CMD_BYTE) {
      LCD1_WriteCommand(seq[i].cmd);
    } else {
      LCD1_WriteData(seq[i].cmd);
    }
  }
#if LCD1_CONFIG_USE_RAM_BUFFER
  /* if using RAM buffer, display orientation is handled by the memory buffer itself */
  SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE);
#else
  SetDisplayOrientation(LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION);
#endif

#if LCD1_CONFIG_CLEAR_DISPLAY_IN_INIT
  LCD1_Clear();
#endif
}

/*
** ===================================================================
**     Method      :  OnDataReceived (component SSD1351)
**
**     Description :
**         callback to be called from SPI interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_OnDataReceived(void)
{
  LCD1_DataReceivedFlag = TRUE;
}

/*
** ===================================================================
**     Method      :  PutPixel (component SSD1351)
**
**     Description :
**         Writes a pixel to the display memory buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x coordinate
**         y               - 
**         color           - pixel color
**     Returns     : Nothing
** ===================================================================
*/
void LCD1_PutPixel(LCD1_PixelDim x, LCD1_PixelDim y, LCD1_PixelColor color)
{
#if LCD1_CONFIG_USE_RAM_BUFFER
  #if MCUC1_CONFIG_CPU_IS_LITTLE_ENDIAN
  color = (color<<8)|(color>>8);
  #endif

#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  switch(currentOrientation) {
    default:
    case LCD1_ORIENTATION_PORTRAIT:
      LCD1_DisplayBuf[x][LCD1_HW_WIDTH-1-y] = color;
      break;
    case LCD1_ORIENTATION_PORTRAIT180:
      LCD1_DisplayBuf[LCD1_HW_HEIGHT-1-x][y] = color;
      break;
    case LCD1_ORIENTATION_LANDSCAPE:
      LCD1_DisplayBuf[y][x] = color;
      break;
    case LCD1_ORIENTATION_LANDSCAPE180:
      LCD1_DisplayBuf[LCD1_HW_HEIGHT-1-y][LCD1_HW_WIDTH-1-x] = color;
      break;
  } /* switch */
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT
  LCD1_DisplayBuf[x][LCD1_HW_HEIGHT-1-y] = color;
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT180
  LCD1_DisplayBuf[LCD1_HW_HEIGHT-1-x][y] = color;
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE
  LCD1_DisplayBuf[y][x] = color;
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  LCD1_DisplayBuf[LCD1_HW_HEIGHT-1-y][LCD1_HW_WIDTH-1-x] = color;
#endif
#else
  LCD1_OpenWindow(x, y, x, y);          /* window for one pixel */
  LCD1_WritePixel(color);
  LCD1_CloseWindow();
#endif /* LCD1_CONFIG_USE_RAM_BUFFER */
}

/*
** ===================================================================
**     Method      :  GetPixel (component SSD1351)
**
**     Description :
**         Returns a pixel from the memory buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x coordinate
**         y               - y coordinate
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
LCD1_PixelColor LCD1_GetPixel(LCD1_PixelDim x, LCD1_PixelDim y)
{
#if LCD1_CONFIG_USE_RAM_BUFFER
  LCD1_PixelColor pix;

#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  switch(currentOrientation) {
    default:
    case LCD1_ORIENTATION_PORTRAIT:
      pix = LCD1_DisplayBuf[x][LCD1_HW_HEIGHT-1-y];
      break;
    case LCD1_ORIENTATION_PORTRAIT180:
      pix = LCD1_DisplayBuf[LCD1_HW_HEIGHT-1-x][y];
      break;
    case LCD1_ORIENTATION_LANDSCAPE:
      pix = LCD1_DisplayBuf[y][x];
      break;
    case LCD1_ORIENTATION_LANDSCAPE180:
      pix = LCD1_DisplayBuf[LCD1_HW_HEIGHT-1-y][LCD1_HW_WIDTH-1-x];
      break;
  } /* switch */
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT
  pix = LCD1_DisplayBuf[x][y];
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT180
  pix = LCD1_DisplayBuf[LCD1_HW_HEIGHT-1-x][y];
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE
  pix = LCD1_DisplayBuf[y][x];
#elif LCD1_CONFIG_INITIAL_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  pix = LCD1_DisplayBuf[LCD1_HW_HEIGHT-1-y][LCD1_HW_WIDTH-1-x];
#endif
  #if MCUC1_CONFIG_CPU_IS_LITTLE_ENDIAN
  pix = (pix<<8)|(pix>>8);
  #endif
  return pix;
#else
  return 0; /* not able to read from display! */
#endif /* LCD1_CONFIG_USE_RAM_BUFFER */
}

/* END LCD1. */

/*!
** @}
*/
