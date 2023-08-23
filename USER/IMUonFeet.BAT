SET PATH=E:\software\keil5\ARM\ARMCC\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;E:\software\vmware\bin\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\Bandizip\;E:\software\Git\cmd;C:\Program Files\dotnet\;E:\software\go1.20\bin;E:\software\matlab2020a\runtime\win64;E:\software\matlab2020a\bin;E:\software\matlab2020a\polyspace\bin;E:\software\wechatdeveloper\dll;E:\software\nodejs\;E:\software\python\Scripts\;E:\software\python\;C:\Users\wkk\AppData\Local\Microsoft\WindowsApps;E:\software\Microsoft VS Code\bin;C:\Users\wkk\.dotnet\tools;C:\Users\wkk\go\bin;E:\software\go1.20\bin;E:\software\modelsim\win64;E:\software\qt5.9\5.9.9\mingw53_32\bin;E:\software\PyCharm\bin;;E:\software\android_sdk\platform-tools;E:\software\android_sdk\tools;C:\Users\wkk\AppData\Roaming\npm;E:\software\java\bin\;
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=IMUonFeet
SET CPU_CLOCK=0x00B71B00
"E:\software\keil5\ARM\ARMCC\Bin\ArmAsm" --Via ".\output\startup_stm32f10x_hd._ia"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\main.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_it.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_gpio.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_rcc.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\misc.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\core_cm3.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\system_stm32f10x.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\led.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\delay.__i"
"E:\software\keil5\ARM\ARMCC\Bin\ArmLink" --Via ".\Output\IMUonFeet.lnp"
"E:\software\keil5\ARM\ARMCC\Bin\fromelf.exe" ".\Output\IMUonFeet.axf" --i32combined --output ".\Output\IMUonFeet.hex"
