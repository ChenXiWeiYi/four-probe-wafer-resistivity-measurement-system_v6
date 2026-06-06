#ifndef ErrorNumber_H
#define ErrorNumber_H

typedef enum{
    Error_None                      = 0x00,
    Error_UnknownOperation          = 0x01,
    Error_UnknownMeasureDirection   = 0x02,
    Error_VoltageRangeError         = 0x03,
    Error_CRCError                  = 0x04,
    Error_UnknownCurrentPosition    = 0x05,
    Error_NoSuitMeasPos             = 0x06,
    Error_UnderRange                = 0x07,
    Error_UpRange                   = 0x08,
    Error_CurrentOutOfRange         = 0x09,
    Error_PIDConfigLengthError      = 0x0A,
    Error_InvalidPayloadLength      = 0x0B,
    Error_InvalidParameter          = 0x0C,
    Error_DeviceBusy                = 0x0D
}ErrorNumber_TypeDef;

#endif
