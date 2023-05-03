#/bin/bash
cd build
cmake ..
make -j4
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program serialScratch.elf verify reset exit"
