{
    "targets": [
    {
        "include_dirs": [
            "<!(node -e \"require('nan')\")"
        ],
        "target_name": "png",
        "sources": [
            "src/main.cpp",
            "lodepng/lodepng.cpp"
        ],
        "cflags": [
          "-std=c++11",
          '-O3'
        ]
    }
    ]
}
