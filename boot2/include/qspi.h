#ifndef QSPI_H
#define QSPI_H
void qspi_init(void);
void qspi_nonv_cfg(unsigned int data);
void qspi_enter_xip(void);
#endif
