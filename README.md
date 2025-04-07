# LWPrint XCFramework

## Installation

### Swift Package Manager

To integrate LWPrint into your Xcode project using Swift Package Manager, add it to the dependencies value of your `Package.swift`:

```swift
dependencies: [
    .package(url: "<repository-url>", from: "1.0.0")
]
```

Alternatively in Xcode:
1. File > Add Packages...
2. Enter the repository URL
3. Select "LWPrint" from the list of available packages

## Requirements

- iOS 11.0+ / macOS 10.13+
- Xcode 12.0+
- Swift 5.3+


## Introduction

This document describes the process of converting the Brother LWPrint static library (`libLWPrintLib.a`) into an XCFramework with support for both device (arm64) and simulator (x86_64, arm64) architectures.

## Original Library Source

Download the latest version of the Brother LWPrint SDK from the [Brother Developer website](https://support.epson.biz/lw/download.html). At the time of writing, the latest version is `1.5.1`, released some time in 2019.

The package should contain the following files:

- `libLWPrintLib.a`
- `libLWPrintLib-arm64.a` (in a most recent releases, but not in current)
- `LWPrint.h`
- `LWPrintDataProvider.h`
- `LWPrintDiscoverPrinter.h`

### Challenge

The challenge with original package structure is that it contains two .a files, an universal one containing following architectures:

```
> lipo -info libLWPrintLib.a
Architectures in the fat file: libLWPrintLib.a are: armv7 armv7s i386 x86_64 arm64
```

and one for arm64 simulators, containing:

```
> lipo -info libLWPrintLib-arm64.a
Architectures in the fat file: libLWPrintLib-arm64.a are: arm64
```

The reason for two files is that a single .a file cannot contain two implementations for the same architecture, whereas arm64 for real devices and arm64 for simulators are built differently.

## Converting to XCFramework

The solution is to use an XCFramework, which can contain both device and simulator arm64 architectures.

### Getting Simulator Binary

Current version (1.5.1) does not include `arm64` simulator binary and the one included in the recent packages (`libLWPrintLib-arm64.a` - tested with 1.6.5) is not properly compiled and cannot be included in XCFramework.

We can instead make a dummy implementation for simulator ourselves. Please refer to the `dummy_simulator_implementation` directory.

The compiled dummy file is referenced in the build script (`create_xcframework.sh`) as `SIMULATOR_ARM64="dummy_simulator_implementation/libDummy-sim.a"`

### Creating XCFramework

Run the following script:

```
./create_xcframework.sh "/Path/To/LWPrint/Lib"
```
