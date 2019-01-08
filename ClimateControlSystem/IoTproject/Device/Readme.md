# RemoteMonitoringV2

## Steps to start

1. Setup development environment by following [Get Started](https://microsoft.github.io/azure-iot-developer-kit/docs/get-started/)
2. Open VS Code
3. Press **F1** or **Ctrl + Shift + P** - `IoT Workbench: Examples` and select RemoteMonitoringV2.

## Create an Azure IoT Suite

1. Go to [Azure IoT Suite site](https://www.azureiotsuite.com/) and click Create a new solution.
2. Select **Remote monitoring preview**.
3. Enter a solution name, select a subscription and a region, and then click **Create solution**. The solution may take a while to be provisioned.
4. After the provision is completed, click **Launch**. Some simulated devices are created for the solution during the provision process. Click DEVICES to check them out.
5. Create a new physical device in the solution. Please take a note of the device connection string.


## Configure IoT Hub Device Connection String in DevKit

1. Connect your DevKit to your machine.
2. Press **F1** or **Ctrl + Shift + P** in Visual Studio Code - **IoT Workbench: Device** and click **config-device-connection**.
3. Select **Input IoT Hub Device Connection String** and input the value from the previous step.
3. Hold button A on DevKit, then press rest button, and then release button A to enter config mode.
4. Wait for connection string configuration to complete.

## Upload Arduino Code to DevKit

1. Connect your DevKit to your machine.
2. Press **F1** or **Ctrl + Shift + P** in Visual Studio Code - **IoT Workbench:Device** and click **Device Upload**.
3. Wait for arduino code uploading.

## Test the project

When the sample app runs, DevKit sends sensor data over Wi-Fi to your Azure IoT Suite. To see the result, follow these steps:

1. Go to your Azure IoT Suite, and click DASHBOARD.
2. On the Azure IoT Suite solution console, you will see your DevKit sensor status.

