#ifndef ADC_SPI_H
#define ADC_SPI_H

void ADC_init(void);
void ADC_cleanup(void);
int  ADC_readChannel(int ch);

#endif
