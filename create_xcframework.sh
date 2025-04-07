#!/bin/bash

set -e # Exit on error

# Check if source path is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 /path/to/LWPrint/library/directory"
    exit 1
fi

SOURCE_DIR="$1"
LIBRARY_PATH="$SOURCE_DIR/libLWPrintLib.a"
SIMULATOR_ARM64="dummy_simulator_implementation/libDummy-sim.a"

# TODO: Use original arm64 simulator library, when it's properly compiled
# SIMULATOR_ARM64="$SOURCE_DIR/libLWPrintLib-arm64.a"

# Verify source files exist
if [ ! -f "$LIBRARY_PATH" ]; then
    echo "Error: Library not found at $LIBRARY_PATH"
    exit 1
fi

if [ ! -f "$SIMULATOR_ARM64" ]; then
    echo "Error: Simulator library not found at $SIMULATOR_ARM64"
    exit 1
fi

echo ""
echo "=== Source Library Information ==="
lipo -info "$LIBRARY_PATH"

echo ""
echo "=== Simulator Library Information ==="
lipo -info "$SIMULATOR_ARM64"

# Create working directory
WORK_DIR="temp_framework"
rm -rf "$WORK_DIR" LWPrint.xcframework
mkdir -p "$WORK_DIR"

# Create device framework
mkdir -p "$WORK_DIR/ios-device/LWPrint.framework/Modules"
mkdir -p "$WORK_DIR/ios-device/LWPrint.framework/Headers"

# Create simulator framework
mkdir -p "$WORK_DIR/ios-simulator/LWPrint.framework/Modules"
mkdir -p "$WORK_DIR/ios-simulator/LWPrint.framework/Headers"

# Copy header files
echo ""
echo "=== Copying Headers ==="
for header in "$SOURCE_DIR"/*.h; do
    if [ -f "$header" ]; then
        echo "Copying $header"
        cp "$header" "$WORK_DIR/ios-device/LWPrint.framework/Headers/"
        cp "$header" "$WORK_DIR/ios-simulator/LWPrint.framework/Headers/"
    fi
done

# Copy umbrella header
cp "template/Umbrella.h" "$WORK_DIR/ios-device/LWPrint.framework/Headers/Umbrella.h"
cp "template/Umbrella.h" "$WORK_DIR/ios-simulator/LWPrint.framework/Headers/Umbrella.h"

# Create module map
echo ""
echo "=== Creating Module Map ==="
cp "template/module.modulemap" "$WORK_DIR/ios-device/LWPrint.framework/Modules/module.modulemap"
cp "template/module.modulemap" "$WORK_DIR/ios-simulator/LWPrint.framework/Modules/module.modulemap"

# Create Info.plist
echo ""
echo "=== Creating Info.plist ==="
cp "template/Info.plist" "$WORK_DIR/ios-device/LWPrint.framework/Info.plist"
cp "template/Info.plist" "$WORK_DIR/ios-simulator/LWPrint.framework/Info.plist"

# Extract and combine device architectures
echo ""
echo "=== Processing Device Architectures ==="
lipo "$LIBRARY_PATH" -extract arm64 -extract armv7 -extract armv7s -output "$WORK_DIR/ios-device/LWPrint.framework/LWPrint"

echo "Device binary architectures:"
lipo -info "$WORK_DIR/ios-device/LWPrint.framework/LWPrint"

# Process simulator architectures
echo ""
echo "=== Processing Simulator Architectures ==="

# Extract x86_64 from main library
echo "Extracting x86_64 simulator slice"
lipo "$LIBRARY_PATH" -extract x86_64 -output "$WORK_DIR/ios-simulator/LWPrint.framework/LWPrint"

lipo -create "$WORK_DIR/ios-simulator/LWPrint.framework/LWPrint" "$SIMULATOR_ARM64" -output "$WORK_DIR/ios-simulator/LWPrint.framework/LWPrint"

# Create XCFramework
echo ""
echo "=== Creating XCFramework ==="
xcodebuild -create-xcframework \
-framework "$WORK_DIR/ios-device/LWPrint.framework" \
-framework "$WORK_DIR/ios-simulator/LWPrint.framework" \
-output "LWPrint.xcframework"

# Cleanup
rm -rf "$WORK_DIR"

echo ""
echo "=== Done ==="
echo "XCFramework created at: $(pwd)/LWPrint.xcframework"
