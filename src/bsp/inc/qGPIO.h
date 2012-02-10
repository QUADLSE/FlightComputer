/***********************************************************************//**
 * @file		qGPIO.h
 * @brief		Contains all macro definitions and function prototypes
 * 				for the GPIO driver.
 * @version
 * @date
 * @author
 *************************************************************************/
/** @ingroup BSP */
/** @addtogroup qGPIO */
/*@{*/

#ifndef QGPIO_H_
#define QGPIO_H_
#include <stdint.h>

#include "base.h"
#include "BSP_Config.h"

//===========================================================
// Types
//===========================================================

/** Enum type for GPIO direction */
typedef enum{
	qGPIO_OUTPUT,	/**< Pin as output */
	qGPIO_INPUT		/**< Pin as input */
}qGPIO_Direction;

/** Enum type for GPIO Value */
typedef enum{
	qGPIO_HIGH,		/**< Pin output in HIGH = 1 */
	qGPIO_LOW		/**< Pin output in LOW = 0 */
}qGPIO_Value;

#if 0
/** Struct type for GPIO Value */
typedef struct{
	qGPIO_Direction dir;
	qGPIO_Value value;
}qGPIO_Pin;
#endif
//===========================================================
// Externs
//===========================================================
#if 0
extern qGPIO_Pin qGPIO[qGPIO_TOTAL];
#endif
//===========================================================
// Prototypes
//===========================================================

/********************************************************************//**
 * @brief		Configurates pin for operation
 * @param[in]	pin Pin Number
 * @param[in]	dir Sets GPIO direction
 * @return 		RET_OK
 * @return 		RET_ERROR
 *********************************************************************/
ret_t qGPIO_Init(int pin, qGPIO_Direction dir);

/********************************************************************//**
 * @brief		Deinit the pin. Set to HI-Z (not implemented yet)
 * @param[in]	pin Pin Number
 * @return 		RET_OK
 * @return 		RET_ERROR
 *********************************************************************/
ret_t qGPIO_DeInit(int pin);

/********************************************************************//**
 * @brief		Set a new value to the pin
 * @param[in]	pin Pin Number
 * @param[in]	val Pin value
 * @return 		RET_OK
 * @return 		RET_ERROR
 *********************************************************************/
ret_t qGPIO_Set(int pin, qGPIO_Value val);

/********************************************************************//**
 * @brief		Reads the pin value from the hardware. Must be set as input to make sense
 * @param[in]	pin Pin Number
 * @return 		RET_OK
 * @return 		RET_ERROR
 *********************************************************************/
qGPIO_Value qGPIO_Read(int pin);

#endif /* QGPIO_H_ */
