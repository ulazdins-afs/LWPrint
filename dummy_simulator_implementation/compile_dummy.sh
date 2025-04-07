echo "Compiling dummy"

xcrun -sdk iphonesimulator clang -arch arm64 -fembed-bitcode -fobjc-arc -fmodules -c DummyLWPrint.m -o DummyLWPrint.o -fvisibility=default

echo "Archive created"

ar rcs libDummy-sim.a DummyLWPrint.o

rm DummyLWPrint.o