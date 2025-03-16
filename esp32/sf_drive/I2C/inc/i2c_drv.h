#ifndef _I2C_DRV_H_
#define _I2C_DRV_H_

#include "stdint.h"

typedef uint8_t Std_ReturnType;

typedef struct sf_i2c_bus_config{
    uint8_t     sda_io_num;
    uint8_t     scl_io_num;
    uint8_t     clk_source;
    uint8_t     i2c_port;
    uint8_t     glitch_ignore_cnt;
} sf_i2c_bus_config_t;

typedef struct sf_i2c_device_config{
    uint8_t     dev_addr_length;
    uint8_t     device_address;
    uint8_t     scl_speed_hz;
} sf_i2c_device_config;

typedef struct sf_i2c_config{
    sf_i2c_bus_config_t     bus_config;
    sf_i2c_device_config    device_config;
} sf_i2c_config_t;


/* This type of external data structure shall contain the initialization data for the I2C Driver. */
typedef sf_i2c_config_t I2C_ConfigType;

/* I2C Address Data. */
typedef uint16_t I2C_AddressType;

typedef uint16_t I2C_DataType;
typedef uint8_t* I2C_DataPtrType;
typedef uint8_t* I2C_DataConstPtrType;

/* This type defines a range of specific Sequences status for the I2C Driver. */
typedef enum {
    I2C_SEQ_OK,             /* The last transmission of the Sequence has been finished successfully */
    I2C_SEQ_PENDING,        /* The I2C Driver is performing an I2C Sequence. The meaning of this status is equal to I2C_BUSY. */
    I2C_SEQ_QUEUE,          /* An I2C Sequence is queued and waiting to be transmitted. */
    I2C_SEQ_NACK,           /* An I2C Sequence encountered a NACK signal. */
    I2C_SEQ_FALED           /* The last transmission of the Sequence has failed. */
}I2C_SequenceResultType;

/* Specifies the identification (ID) for a I2C Hardware microcontroller peripheral (unit). */
typedef uint8_t I2C_HwUnitType;

/* This is the type for a Job identifier. */
typedef uint8_t I2C_JobType;

/* This is the type for a Sequence identifier. */
typedef uint8_t I2C_SequenceType;

/* Type to define the number of data elements to be sent and / or received during a transmission. */
typedef uint16_t I2C_NumberOfDataType;

/*
 * This service initializes the I2C Driver.
 */
void I2C_Init(const I2C_ConfigType* ConfigPtr);

/*
 * This service de-initializes the I2C Driver.
 */
void I2C_DeInit(void);

/*
 * This service initializes the I2C Driver.
 * param: JobId: Job to be used in the transmission.
 * param: NodeAddress: Any other value then zero will override the statically configured node address.
 * param: TxDataBufferPtr: Pointer to the TX transmission data location.
 * param: RxDataBufferPtr: Pointer to the RX transmission data location.
 * param: Length: Length (number of data elements) of the data to be transmitted from TxDataBufferPtr and/or received from RxDataBufferPtr.
 */
Std_ReturnType I2C_SetupEB(I2C_JobType JobId,
                           I2C_AddressType NodeAddress,
                           I2C_DataConstPtrType* TxDataBufferPtr,
                           I2C_DataPtrType* RxDataBufferPtr,
                           I2C_NumberOfDataType Length);

/*
 * The service conducts an asynchronous data transmission according to the parameters 
 * provided to the I2c_SetupEB() service. The callback I2c_SeqEndNotification() is
 * called, when the asynchronous operation has finished.
 */
Std_ReturnType I2C_AsyncTransmit(I2C_SequenceType SequenceId);

/*
 * This service sends or receives data using a blocking mechanism according to the 
 * parameters provided to the I2c_SetupEB() service.
 */
Std_ReturnType I2C_SyncTransmit(I2C_SequenceType SequenceId);

/* 
 * This service returns the current status of the given SequenceId. 
 *
 */
I2C_SequenceResultType I2C_GetSequenceResult(I2C_SequenceType SequenceId);

/*
 * Makes a target channel available for processing requests (addressing). When called, 
 * the target channel becomes available for starting incoming or outgoing transfers.
 */
Std_ReturnType I2C_StartListening(I2C_SequenceType SequenceId);

#endif
