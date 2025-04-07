# Dummy simulator library

## Adding ARM64 Simulator Support

For Apple Silicon Macs, we need to provide an arm64 simulator binary. Since the original library doesn't include this, we create a dummy implementation:

3. Compile the dummy library:

```bash
xcrun -sdk iphonesimulator clang -arch arm64 -fembed-bitcode -fobjc-arc -fmodules -c DummyLWPrint.m -o DummyLWPrint.o -fvisibility=default && \
ar rcs libDummy-sim.a DummyLWPrint.o && \
rm DummyLWPrint.o
```

4. Update the XCFramework with the dummy library:

```bash
lipo -extract x86_64 LWPrint.xcframework/ios-simulator/LWPrint.framework/LWPrint -output temp_x86_64 && \
lipo -create temp_x86_64 libDummy-sim.a -output LWPrint.xcframework/ios-simulator/LWPrint.framework/LWPrint.new && \
mv LWPrint.xcframework/ios-simulator/LWPrint.framework/LWPrint.new LWPrint.xcframework/ios-simulator/LWPrint.framework/LWPrint && \
rm temp_x86_64
```
