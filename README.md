Use to compile a bootrom.bin and package the uefi together.
The final generated image can run in qspi as a bootrom on NANHU fpga.
It copies the uefi into ram, and jump to ram (0x80000000).

bootrom/: Core for bootrom which can run on NANHU FPGA
qemu_test/: Core for test which can run on qemu

usage:
	make all (make bootrom && make qemu) -- Compile both bootrom and qemu_test (compile bootrom && compile qemu_test)
	make pack -- Package bin/uefi.fd and bootrom.bin together. The generated image is in the out directory.
	make clean -- Clean all
	make run -- Run qemu_test.bin on qemu.
	make run-debug -- Debug qemu_test.bin on qemu.


