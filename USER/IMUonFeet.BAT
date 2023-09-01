SET PATH=D:\software\keilMDKcore\ARM\ARMCC\Bin;D:\software\cuda10.2\bin;D:\software\cuda10.2\libnvvp;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\dotnet\;D:\software\Git\cmd;D:\software\ffmpeg\bin;D:\Program Files\MATLAB\R2017a\runtime\win64;D:\Program Files\MATLAB\R2017a\bin;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;D:\Lua;D:\Lua\clibs;D:\software\WeChatDeveloperTools\dll;D:\software\nodejs\;D:\software\golang\bin;C:\Program Files\NVIDIA Corporation\Nsight Compute 2019.5.0\;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;D:\software\mingw64_v8\bin;C:\Users\29620\AppData\Local\Programs\Python\Python37;C:\Users\29620\AppData\Local\Programs\Python\Python37\Scripts;D:\software\python37\Scripts\;D:\software\python37\;D:\software\opencv\build\x64\vc15\bin;D:\software\mysql8026\bin;D:\software\curl\bin;D:\software\JLinkARM_V415e;D:\software\tesseract-OCR;D:\software\Java\jdk1.8.0_131\bin;D:\software\python37\Lib\site-packages\django;D:\software\python37\Scripts;D:\software\DevEco Studio 3.0.0.601\bin;;D:\software\cmake_3.22.1\bin;D:\software\kendryte-toolchain\kendryte-toolchain\bin;D:\software\SQLite3;D:\software\JDK\bin;D:\software\Espressif\tools\idf-exe\1.0.3;D:\software\IntelliJ_IDEA\bin;;E:\Flutter\src\flutter\bin;C:\Users\29620\.dotnet\tools;C:\Users\29620\AppData\Roaming\npm;D:\software\ClockBuilder Pro\Bin;C:\Users\29620\go\bin;D:\software\cuda10.2\bin;D:\software\cuda10.2\include;D:\software\cuda10.2\lib;D:\software\cuda10.2\libnvvp;D:\software\PyCharm Community Edition 2023.1.2\bin;;D:\software\anaconda\Library\bin;D:\software\anaconda\Scripts;C:\Users\29620\AppData\Local\Android\Sdk\platform-tools;C:\Users\29620\AppData\Local\Android\Sdk\tools\bin;
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=IMUonFeet
SET CPU_CLOCK=0x00B71B00
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmAsm" --Via ".\output\startup_stm32f10x_hd._ia"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\main.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_it.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_gpio.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_rcc.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\misc.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_exti.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_usart.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_spi.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\core_cm3.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\system_stm32f10x.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\led.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\delay.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\sonar_tx.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\sonar_rx.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\usart3.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\spi2.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\nrf24g.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\iic.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\oled.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmCC" --Via ".\output\font.__i"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\ArmLink" --Via ".\Output\IMUonFeet.lnp"
"D:\software\keilMDKcore\ARM\ARMCC\Bin\fromelf.exe" ".\Output\IMUonFeet.axf" --i32combined --output ".\Output\IMUonFeet.hex"
