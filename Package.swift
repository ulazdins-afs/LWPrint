// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "LWPrint",
    platforms: [
        .iOS(.v11),
        .macOS(.v10_13)
    ],
    products: [
        .library(
            name: "LWPrint",
            targets: ["LWPrint"]
        )
    ],
    targets: [
        .binaryTarget(
            name: "LWPrint",
            path: "LWPrint.xcframework"
        )
    ]
)
