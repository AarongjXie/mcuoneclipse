/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : RTC1.h
**     Project     : tinyK22_SGP30
**     Processor   : MK22FN512VLH12
**     Component   : RTC_Maxim
**     Version     : Component 01.018, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-10-01, 21:35, # CodeGen: 20
**     Abstract    :
**
**     Settings    :
**          Component name                                 : RTC1
**          Device                                         : DS3231
**          I2C                                            : GI2C1
**          Utility                                        : UTIL1
**          Shell                                          : Enabled
**            Shell                                        : CLS1
**     Contents    :
**         GetRTCTimeDate - uint8_t RTC1_GetRTCTimeDate(RTC1_TTIME *time, RTC1_TDATE *date);
**         SetRTCTimeDate - uint8_t RTC1_SetRTCTimeDate(RTC1_TTIME *time, RTC1_TDATE *date);
**         GetRTCTime     - uint8_t RTC1_GetRTCTime(RTC1_TTIME *time);
**         SetRTCTime     - uint8_t RTC1_SetRTCTime(RTC1_TTIME *time);
**         GetRTCDate     - uint8_t RTC1_GetRTCDate(RTC1_TDATE *date);
**         SetRTCDate     - uint8_t RTC1_SetRTCDate(RTC1_TDATE *date);
**         GetTime        - uint8_t RTC1_GetTime(TIMEREC *time);
**         SetTime        - uint8_t RTC1_SetTime(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100);
**         GetDate        - uint8_t RTC1_GetDate(DATEREC *date);
**         SetDate        - uint8_t RTC1_SetDate(uint16_t Year, uint8_t Month, uint8_t Day);
**         Read           - uint8_t RTC1_Read(uint8_t addr, uint8_t *buf, uint8_t bufSize);
**         Write          - uint8_t RTC1_Write(uint8_t addr, uint8_t *buf, uint8_t bufSize);
**         ReadByte       - uint8_t RTC1_ReadByte(uint8_t addr, uint8_t *buf);
**         WriteByte      - uint8_t RTC1_WriteByte(uint8_t addr, uint8_t buf);
**         ReadBlock      - uint8_t RTC1_ReadBlock(uint8_t addr, uint8_t *buf, uint8_t bufSize);
**         WriteBlock     - uint8_t RTC1_WriteBlock(uint8_t addr, uint8_t *buf, uint8_t bufSize);
**         ParseCommand   - uint8_t RTC1_ParseCommand(const unsigned char *cmd, bool *handled, const...
**         Init           - void RTC1_Init(void);
**         Deinit         - void RTC1_Deinit(void);
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
** @file RTC1.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup RTC1_module RTC1 module documentation
**  @{
*/         

/* MODULE RTC1. */

#include "RTC1.h"

static uint8_t AddHWRTCDate(uint8_t *buf, size_t bufSize) {
  RTC1_TDATE tdate;
  const char *const weekDays[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  if (RTC1_GetRTCDate(&tdate)!=ERR_OK) {
    return ERR_FAILED;
  }
  if (tdate.dayOfWeek<=6) {
    UTIL1_strcat(buf, bufSize, (unsigned char*)weekDays[tdate.dayOfWeek]);
  }
  UTIL1_chcat(buf, bufSize, ' ');
  UTIL1_strcatNum16uFormatted(buf, bufSize, tdate.day, '0', 2);
  UTIL1_chcat(buf, bufSize, '.');
  UTIL1_strcatNum16uFormatted(buf, bufSize, tdate.month, '0', 2);
  UTIL1_chcat(buf, bufSize, '.');
  UTIL1_strcatNum16u(buf, bufSize, (uint16_t)tdate.year+2000);
  return ERR_OK;
}

static uint8_t AddHWRTCTime(uint8_t *buf, size_t bufSize) {
  RTC1_TTIME ttime;

  if (RTC1_GetRTCTime(&ttime)!=ERR_OK) {
    return ERR_FAILED;
  }
  UTIL1_strcatNum16sFormatted(buf, bufSize, ttime.hour, '0', 2);
  UTIL1_chcat(buf, bufSize, ':');
  UTIL1_strcatNum16sFormatted(buf, bufSize, ttime.min, '0', 2);
  UTIL1_chcat(buf, bufSize, ':');
  UTIL1_strcatNum16sFormatted(buf, bufSize, ttime.sec, '0', 2);
  if (ttime.mode==RTC1_TTIME_MODE_24H) {
    UTIL1_strcat(buf, bufSize, (unsigned char*)" (24h)");
  } else {
    if (ttime.am_pm==RTC1_TTIME_AMPM_AM) {
    UTIL1_strcat(buf, bufSize, (unsigned char*)"am");
    } else {
      UTIL1_strcat(buf, bufSize, (unsigned char*)"pm");
    }
  }
  return ERR_OK;
}

static uint8_t DateCmd(const unsigned char *cmd, CLS1_ConstStdIOType *io) {
  /* precondition: cmd points to "RTC1 date" */
  uint8_t day, month;
  uint16_t year;
  const unsigned char *p;
  uint8_t res = ERR_OK;

  p = cmd + sizeof("RTC1 date")-1;
  if (*p==' ') { /* ok, have an argument */
    if (UTIL1_ScanDate(&p, &day, &month, &year) == ERR_OK) { /* ok, format fine */
      /* update real time clock */
      res = RTC1_SetDate(year, month, day);
      if (res!=ERR_OK) {
        CLS1_SendStr((unsigned char*)"*** Failure setting RTC\r\n", io->stdErr);
        res = ERR_FAILED;
      } else {
        /* note: spending some time here, as the RTC is busy writing data, we will read data back below */
        CLS1_SendStr((unsigned char*)"Reading date from RTC: ", io->stdOut);
      }
    } else {
      CLS1_SendStr((unsigned char*)"*** Error while reading command! ***", io->stdErr);
      CLS1_SendStr((void *)cmd, io->stdErr);
      CLS1_SendStr((unsigned char*)"\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } /* has an argument */
  /* print now current date */
  if (res==ERR_OK) {
    unsigned char buf[sizeof("Wednesday dd:mm:yyyy\\r\\n")];

    buf[0]='\0';
    if (AddHWRTCDate(buf, sizeof(buf))!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"*** Failed to get RTC date\r\n", io->stdErr);
      res = ERR_FAILED;
    } else {
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      CLS1_SendStr(buf, io->stdOut);
    }
  }
  return res;
}

static uint8_t TimeCmd(const unsigned char *cmd, CLS1_ConstStdIOType *io) {
  uint8_t hour, minute, second, hSecond;
  const unsigned char *p;
  uint8_t res = ERR_OK;

  p = cmd + sizeof("RTC1 time")-1;
  if (*p==' ') { /* has an argument */
    if (UTIL1_ScanTime(&p, &hour, &minute, &second, &hSecond)==ERR_OK) { /* format fine */
      /* set RTC time */
      res = RTC1_SetTime(hour, minute, second, hSecond);
      if (res != ERR_OK) {
        CLS1_SendStr((unsigned char*)"*** Failure setting RTC time\r\n", io->stdErr);
        res = ERR_FAILED;
      } else {
        /* note: spending some time here, as the RTC is busy writing data, we will read data back below */
        CLS1_SendStr((unsigned char*)"Reading time from RTC: ", io->stdOut);
      }
    } else {
      CLS1_SendStr((unsigned char*)"*** Error while reading command: ", io->stdErr);
      CLS1_SendStr(cmd, io->stdErr);
      CLS1_SendStr((unsigned char*)"\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  }
  /* print now current time */
  if (res==ERR_OK) {
    unsigned char buf[sizeof("hh:mm:ss.hh (24h)\\r\\n")];

    buf[0] = '\0';
    if (AddHWRTCTime(buf, sizeof(buf))!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"*** Failed to get RTC time\r\n", io->stdErr);
      res = ERR_FAILED;
    } else {
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      CLS1_SendStr(buf, io->stdOut);
    }
  }
  return res;
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[32];

  CLS1_SendStatusStr((unsigned char*)"RTC1", (const unsigned char*)"\r\n", io->stdOut);
  buf[0] = '\0';
  if (AddHWRTCDate(buf, sizeof(buf))!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"*** Failed to get RTC date!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  date", buf, io->stdOut);
  buf[0] = '\0';
  if (AddHWRTCTime(buf, sizeof(buf))!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"*** Failed to get RTC time!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  time", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"DS3231");
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)", Addr 0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), RTC1_DEVICE_ADDRESS);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  device", buf, io->stdOut);

#if RTC1_MEM_SIZE==0 /* no RAM on device */
  /* there is no RAM for this device */
#else
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), RTC1_MEM_RAM_START_ADDR);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"..0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), RTC1_MEM_RAM_END_ADDR);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  RAM", buf, io->stdOut);
#endif

  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Read (component RTC_Maxim)
**
**     Description :
**         Read from the device
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - device memory address
**       * buf             - Pointer to read buffer
**         bufSize         - Size of read buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_Read(uint8_t addr, uint8_t *buf, uint8_t bufSize)
{
  return GI2C1_ReadAddress(RTC1_DEVICE_ADDRESS, &addr, 1, buf, bufSize);
}

/*
** ===================================================================
**     Method      :  Write (component RTC_Maxim)
**
**     Description :
**         Write from the device
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - device memory address
**       * buf             - Pointer to read buffer
**         bufSize         - 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_Write(uint8_t addr, uint8_t *buf, uint8_t bufSize)
{
  return GI2C1_WriteAddress(RTC1_DEVICE_ADDRESS, &addr, 1, buf, bufSize);
}

/*
** ===================================================================
**     Method      :  ReadByte (component RTC_Maxim)
**
**     Description :
**         Read from the device RAM
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - device memory address, with zero as the
**                           RAM start address
**       * buf             - Pointer to read buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_ReadByte(uint8_t addr, uint8_t *buf)
{
#if RTC1_MEM_SIZE==0 /* no RAM on device */
  (void)addr; /* unused */
  (void)buf;  /* unused */
  return ERR_FAILED; /* there is no RAM for this device */
#else
  if (addr>RTC1_MAX_ADDRESS) {
    return ERR_RANGE; /* memory address out of range */
  }
  addr += RTC1_MEM_RAM_START_ADDR;
  return GI2C1_ReadAddress(RTC1_DEVICE_ADDRESS, &addr, 1, buf, 1);
#endif
}

/*
** ===================================================================
**     Method      :  WriteByte (component RTC_Maxim)
**
**     Description :
**         Read from the device RAM
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - device memory address, with zero as the
**                           RAM memory start address
**         buf             - value to write
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_WriteByte(uint8_t addr, uint8_t buf)
{
#if RTC1_MEM_SIZE==0 /* no RAM on device */
  (void)addr; /* unused */
  (void)buf;  /* unused */
  return ERR_FAILED; /* there is no RAM for this device */
#else
  if (addr>RTC1_MAX_ADDRESS) {
    return ERR_RANGE; /* memory address out of range */
  }
  addr += RTC1_MEM_RAM_START_ADDR;
  return GI2C1_WriteAddress(RTC1_DEVICE_ADDRESS, &addr, 1, &buf, 1);
#endif
}

/*
** ===================================================================
**     Method      :  ReadBlock (component RTC_Maxim)
**
**     Description :
**         Read from the device RAM
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - device memory address, with zero as the
**                           RAM start address
**       * buf             - Pointer to read buffer
**         bufSize         - Size of read buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_ReadBlock(uint8_t addr, uint8_t *buf, uint8_t bufSize)
{
#if RTC1_MEM_SIZE==0 /* no RAM on device */
  (void)addr; /* unused */
  (void)buf;  /* unused */
  (void)bufSize; /* unused */
  return ERR_FAILED; /* there is no RAM for this device */
#else
  if (addr>RTC1_MAX_ADDRESS || (addr+bufSize)>RTC1_MEM_SIZE) {
    return ERR_RANGE; /* memory address out of range */
  }
  addr += RTC1_MEM_RAM_START_ADDR;
  return GI2C1_ReadAddress(RTC1_DEVICE_ADDRESS, &addr, 1, buf, bufSize);
#endif
}

/*
** ===================================================================
**     Method      :  WriteBlock (component RTC_Maxim)
**
**     Description :
**         Read from the device RAM
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - device memory address, with zero as the
**                           RAM memory start address
**       * buf             - Pointer to read buffer
**         bufSize         - 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_WriteBlock(uint8_t addr, uint8_t *buf, uint8_t bufSize)
{
#if RTC1_MEM_SIZE==0 /* no RAM on device */
  (void)addr; /* unused */
  (void)buf;  /* unused */
  (void)bufSize; /* unused */
  return ERR_FAILED; /* there is no RAM for this device */
#else
  if (addr>RTC1_MAX_ADDRESS || (addr+bufSize)>RTC1_MEM_SIZE) {
    return ERR_RANGE; /* memory address out of range */
  }
  addr += RTC1_MEM_RAM_START_ADDR;
  return GI2C1_WriteAddress(RTC1_DEVICE_ADDRESS, &addr, 1, buf, bufSize);
#endif
}

/*
** ===================================================================
**     Method      :  GetRTCTimeDate (component RTC_Maxim)
**
**     Description :
**         Returns the time and date from the device.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * time            - Pointer to time
**       * date            - Pointer to date
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_GetRTCTimeDate(RTC1_TTIME *time, RTC1_TDATE *date)
{
  uint8_t buf[RTC1_MEM_TIME_DATE_STRUCT_SIZE];

  if (RTC1_Read(RTC1_MEM_TIME_DATE_STRUCT_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  time->sec = (uint8_t)(((buf[0]&0x70)>>4)*10 + (buf[0]&0x0F));
  time->min = (uint8_t)((buf[1]>>4)*10 + (buf[1]&0x0F));
  if (buf[2]&0x40) {
    time->hour =(uint8_t)(buf[2]&0x1F);
    time->mode = RTC1_TTIME_MODE_12H;
    time->am_pm =(uint8_t)((buf[2]&0x20)>>5);
  } else {
    time->hour = (uint8_t)(buf[2]&0x3F);
    time->mode = RTC1_TTIME_MODE_24H;
  }
  time->hour = (uint8_t)((time->hour>>4)*10 + (buf[2]&0x0F));
  date->dayOfWeek =(uint8_t)(buf[3]-1);
  date->day = (uint8_t)((buf[4]>>4)*10 + (buf[4]&0x0F));
  date->month = (uint8_t)((buf[5]>>4)*10 + (buf[5]&0x0F));
  date->year = (uint8_t)((buf[6]>>4)*10 + (buf[6]&0x0F));
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SetRTCTimeDate (component RTC_Maxim)
**
**     Description :
**         Sets the date and time.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * time            - Pointer to time to be set
**       * date            - Pointer to date to be set
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_SetRTCTimeDate(RTC1_TTIME *time, RTC1_TDATE *date)
{
  uint8_t buf[RTC1_MEM_TIME_DATE_STRUCT_SIZE];

  if (   ((time->mode==RTC1_TTIME_MODE_12H)&&((time->hour>12)||(time->hour==0)))
      || ((time->mode==RTC1_TTIME_MODE_24H)&&(time->hour>23))
      || (time->min>59)||(time->sec>59)
      || (date->year>99)||(date->month>12)||(date->month==0)
      || (date->day>31)||(date->day==0)
      || (date->dayOfWeek>6))
  {
    return ERR_RANGE;
  }
  buf[0] = (uint8_t)(((time->sec/10)<<4) | (time->sec%10));
  buf[1] = (uint8_t)(((time->min/10)<<4) | (time->min%10));
  buf[2] = (uint8_t)(((time->hour/10)<<4) | (time->hour%10));
  if (time->mode==RTC1_TTIME_MODE_12H) {
    buf[2] |= (time->am_pm)?0x60:0x40;
  }
  buf[3] = (uint8_t)(date->dayOfWeek+1);
  buf[4] = (uint8_t)(((date->day/10)<<4) | (date->day%10));
  buf[5] = (uint8_t)(((date->month/10)<<4) | (date->month%10));
  buf[6] = (uint8_t)(((date->year/10)<<4) | (date->year%10));
  if (RTC1_Write(RTC1_MEM_TIME_DATE_STRUCT_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SetRTCTime (component RTC_Maxim)
**
**     Description :
**         Sets the time using the RTC low level information.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * time            - Pointer to time to be set
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_SetRTCTime(RTC1_TTIME *time)
{
  uint8_t buf[RTC1_MEM_TIME_STRUCT_SIZE];

  if (   ((time->mode==RTC1_TTIME_MODE_12H)&&((time->hour>12)||(time->hour==0)))
      || ((time->mode==RTC1_TTIME_MODE_24H)&&(time->hour>23))
      || (time->min>59) || (time->sec>59)
     )
  {
    return ERR_RANGE;
  }
  buf[0] = (uint8_t)(((time->sec/10)<<4) | (time->sec%10));
  buf[1] = (uint8_t)(((time->min/10)<<4) | (time->min%10));
  buf[2] = (uint8_t)(((time->hour/10)<<4) | (time->hour%10));
  if (time->mode==RTC1_TTIME_MODE_12H) {
    buf[2] |= (time->am_pm)?0x60:0x40;
  }
  if (RTC1_Write(RTC1_MEM_TIME_STRUCT_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  GetRTCTime (component RTC_Maxim)
**
**     Description :
**         Returns the time using the RTC low level information.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * time            - Pointer to time
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_GetRTCTime(RTC1_TTIME *time)
{
  uint8_t buf[RTC1_MEM_TIME_STRUCT_SIZE];

  if (RTC1_Read(RTC1_MEM_TIME_STRUCT_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  time->sec = (uint8_t)(((buf[0]&0x70)>>4)*10 + (buf[0]&0x0F));
  time->min = (uint8_t)((buf[1]>>4)*10 + (buf[1]&0x0F));
  if (buf[2]&0x40) {
    time->hour =(uint8_t)(buf[2]&0x1F);
    time->mode = RTC1_TTIME_MODE_12H;
    time->am_pm = (uint8_t)((buf[2]&0x20)>>5);
  } else {
    time->hour = (uint8_t)(buf[2]&0x3F);
    time->mode = RTC1_TTIME_MODE_24H;
  }
  time->hour = (uint8_t)((time->hour>>4)*10 + (buf[2]&0x0F));
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  GetRTCDate (component RTC_Maxim)
**
**     Description :
**         Returns the date from the device using the RTC low level
**         information.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * date            - Pointer to date
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_GetRTCDate(RTC1_TDATE *date)
{
  uint8_t buf[RTC1_MEM_DATE_STRUCT_SIZE];

  if (RTC1_Read(RTC1_MEM_DATE_STRUCT_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  date->dayOfWeek =(uint8_t)(buf[0]-1);
  date->day = (uint8_t)((buf[1]>>4)*10 + (buf[1]&0x0F));
  date->month = (uint8_t)((buf[2]>>4)*10 + (buf[2]&0x0F));
  date->year = (uint8_t)((buf[3]>>4)*10 + (buf[3]&0x0F));
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SetRTCDate (component RTC_Maxim)
**
**     Description :
**         Sets the date using the RTC low level information.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * date            - Pointer to date to be set
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_SetRTCDate(RTC1_TDATE *date)
{
  uint8_t buf[RTC1_MEM_DATE_STRUCT_SIZE];

  if (   (date->year>99)
      || (date->month>12)||(date->month==0)
      || (date->day>31)||(date->day==0)
      || (date->dayOfWeek>6)
     )
  {
    return ERR_RANGE;
  }
  buf[0] = (uint8_t)(date->dayOfWeek + 1);
  buf[1] = (uint8_t)(((date->day/10)<<4) | (date->day%10));
  buf[2] = (uint8_t)(((date->month/10)<<4) | (date->month%10));
  buf[3] = (uint8_t)(((date->year/10)<<4) | (date->year%10));
  if (RTC1_Write(RTC1_MEM_DATE_STRUCT_ADDR, buf, sizeof(buf))!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Init (component RTC_Maxim)
**
**     Description :
**         Initializes the driver.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RTC1_Init(void)
{
  /* nothing to do */
}

/*
** ===================================================================
**     Method      :  Deinit (component RTC_Maxim)
**
**     Description :
**         Deinitializes the driver.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void RTC1_Deinit(void)
{
  /* nothing to do */
}

/*
** ===================================================================
**     Method      :  ParseCommand (component RTC_Maxim)
**
**     Description :
**         Shell Command Line parser
**     Parameters  :
**         NAME            - DESCRIPTION
**       * cmd             - Pointer to command line
**       * handled         - Pointer to variable which tells if
**                           the command has been handled or not
**       * io              - Pointer to I/O structure
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io)
{
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "RTC1 help")==0) {
    CLS1_SendHelpStr((unsigned char*)"RTC1", (const unsigned char*)"Group of RTC1 commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  time [hh:mm:ss[,z]]", (const unsigned char*)"Set the current time. Prints the current time if no argument\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  date [dd.mm.yyyy]", (const unsigned char*)"Set the current date. Prints the current date if no argument\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "RTC1 status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "RTC1 date", sizeof("RTC1 date")-1)==0) {
    *handled = TRUE;
    return DateCmd(cmd, io);
  } else if (UTIL1_strncmp((char*)cmd, "RTC1 time", sizeof("RTC1 time")-1)==0) {
    *handled = TRUE;
    return TimeCmd(cmd, io);
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  GetTime (component RTC_Maxim)
**
**     Description :
**         Returns the time.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * time            - Pointer to time
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_GetTime(TIMEREC *time)
{
  RTC1_TTIME ttime;

  if (RTC1_GetRTCTime(&ttime)!=ERR_OK) {
    return ERR_FAILED;
  }
  time->Hour = ttime.hour;
  time->Min = ttime.min;
  time->Sec = ttime.sec;
  time->Sec100 = 0;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SetTime (component RTC_Maxim)
**
**     Description :
**         Sets the time.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Hour            - Hours (0 - 23)
**         Min             - Minutes (0 - 59)
**         Sec             - Seconds (0 - 59)
**         Sec100          - Hundredths of seconds (0 - 99)
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_SetTime(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100)
{
  RTC1_TTIME ttime;

  ttime.hour = Hour;
  ttime.min = Min;
  ttime.sec = Sec;
  (void)Sec100; /* ignored, as cannot be stored on device */
  ttime.mode = RTC1_TTIME_MODE_24H;
  ttime.am_pm = RTC1_TTIME_AMPM_AM;
  return RTC1_SetRTCTime(&ttime);
}

/*
** ===================================================================
**     Method      :  GetDate (component RTC_Maxim)
**
**     Description :
**         Returns the time and date from the device.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * date            - Pointer to date
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_GetDate(DATEREC *date)
{
  RTC1_TDATE tdate;

  if (RTC1_GetRTCDate(&tdate)!=ERR_OK) {
    return ERR_FAILED;
  }
  date->Year = (uint16_t)(tdate.year+2000);
  date->Month = tdate.month;
  date->Day = tdate.day;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SetDate (component RTC_Maxim)
**
**     Description :
**         Sets the date.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Year            - Year in 2000 format
**         Month           - Month number (1..12)
**         Day             - Day number (1..31)
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t RTC1_SetDate(uint16_t Year, uint8_t Month, uint8_t Day)
{
  RTC1_TDATE tdate;

  tdate.year = (uint8_t)(Year-2000);
  tdate.month = Month;
  tdate.day = Day;
  tdate.dayOfWeek = UTIL1_WeekDay(Year, Month, Day);
  return RTC1_SetRTCDate(&tdate);
}

/* END RTC1. */

/*!
** @}
*/
