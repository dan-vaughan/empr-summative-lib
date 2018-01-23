#include "lpc17xx_pinsel.h"

class I2C
{
	protected:
		void init(void);
	public:
		I2C(PINSEL_CFG_Type sda, PINSEL_CFG_Type scl);
		int write(uint32_t addr, uint8_t * data, uint32_t length);
		int read(uint32_t addr, uint8_t * data, uint32_t length);
};

