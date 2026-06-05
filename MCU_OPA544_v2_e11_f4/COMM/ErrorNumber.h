#ifndef ErrorNumber_H
#define ErrorNumber_H

typedef enum{
    Error_UnknownOperation          = 0x00,
    Error_UnknownMeasureDirection   = 0x01,
    Error_VoltageRangeError         = 0x02,
    Error_CRCError                  = 0x03,
    Error_UnknownCurrentPosition    = 0x04,
    Error_NoSuitMeasPos             = 0x05,
    Error_UnderRange                = 0x06,
    Error_UpRange                   = 0x07,
    Error_CurrentOutOfRange         = 0x08,
    Error_PIDConfigLengthError      = 0x09
}ErrorNumber_TypeDef;

#endif
