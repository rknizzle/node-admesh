{
    "targets": [{
        "target_name": "admesh",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "addon/main.cpp",
            "addon/Wrapper.cpp",
            "addon/OpenFileAsyncWorker.cpp",
            "addon/WriteFileAsyncWorker.cpp",
            "addon/RepairFileAsyncWorker.cpp",
            "src/connect.c",
            "src/normals.c",
            "src/shared.c",
            "src/stl_io.c",
            "src/stlinit.c",
            "src/util.c"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}
