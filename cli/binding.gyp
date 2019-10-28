{
    "targets": [{
        "target_name": "dscliaddon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/main.cc"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "include"
        ],
        'libraries': [
            "-Wl,--whole-archive",
            "<(module_root_dir)/libstaticlab1.a",
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}