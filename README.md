Use to compile a bootrom.bin and package the boot2.bin together.
The final generated image can run in qspi as a bootrom on NANHU fpga.
It copies the boot2.bin into ddr, and jump to run boot2.
Boot2 copy kernel to ddr then run kernel.

bootrom/: Core for bootrom which can run on NANHU FPGA

usage:
	make  (make bootrom && make boot2.bin and pack boot2.bin to bootrom)
	make pack -- Package bin/uefi.fd and bootrom.bin together. The generated image is in the out directory.
	make clean -- Clean all


