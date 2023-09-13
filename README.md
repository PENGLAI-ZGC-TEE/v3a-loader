bootrom/: Core for bootrom which can run on NANHU FPGA
mysbi/: Core which can run on qemu

usage:
	make all (make bootrom && make qemu) -- Compile both bootrom and mysbi (compile bootrom && compile mysbi)
	make pack -- Package bin/uefi.fd and bootrom.bin together. The generated image is in the out directory.
	make clean -- Clean all
	make run -- Run mysbi on qemu.
	make debug -- Debug mysbi on qemu.


